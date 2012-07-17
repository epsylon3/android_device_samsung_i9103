/*
 * Copyright (C) 2012 The Android Open Source Project
 *
 * InputReader based sensor interface for KXTF9 I2C sensor
 * Tanguy Pruvot, July 2012 <tpruvot@github>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

//#define LOG_NDEBUG 0

#include <fcntl.h>
#include <errno.h>
#include <math.h>
#include <poll.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/select.h>
#include <cutils/log.h>

#include "sensors.h"

#include "KXTFSensor.h"

#define FETCH_FULL_EVENT_BEFORE_RETURN 1
#define IGNORE_EVENT_TIME 350000000

/*****************************************************************************/

KXTFSensor::KXTFSensor()
    : SensorBase(NULL, "accelerometer_sensor"),
      mEnabled(0),
      mInputReader(4),
      mHasPendingEvent(false),
      mEnabledTime(0)
{
    mPendingEvent.version = sizeof(sensors_event_t);
    mPendingEvent.sensor = ID_A;
    mPendingEvent.type = SENSOR_TYPE_ACCELEROMETER;
    memset(mPendingEvent.data, 0, sizeof(mPendingEvent.data));

    if (data_fd) {
        strcpy(input_sysfs_path, "/sys/class/input/");
        strcat(input_sysfs_path, input_name);
        strcat(input_sysfs_path, "/device/");
        input_sysfs_path_len = strlen(input_sysfs_path);
        enable(0, 1);
    }
}

KXTFSensor::~KXTFSensor()
{
    LOGV(LOG_TAG "[KXTF9] " __FUNCTION__);
    if (mEnabled) {
        enable(0, 0);
    }
}

int KXTFSensor::setInitialState()
{
    struct input_absinfo absinfo_x;
    struct input_absinfo absinfo_y;
    struct input_absinfo absinfo_z;
    float value;

    /* Sample raw data :
     *   12, -298, -979
     */
    FILE *fd = fopen("/sys/devices/virtual/sec/sec_kxtf9/kxtf9_rawdata", "r");
    if (fd != NULL) {
        char buf[24] = "";

        fgets(&buf[0], sizeof(buf), fd);
        fclose(fd);

        int nr = sscanf(buf, "%d, %d, %d", 
            &absinfo_x.value, &absinfo_y.value, &absinfo_z.value);

        if (nr >= 0) {
            value = absinfo_x.value;
            mPendingEvent.data[1] = value * CONVERT_A_Y;
            value = absinfo_y.value;
            mPendingEvent.data[0] = value * CONVERT_A_X;
            value = absinfo_z.value;
            mPendingEvent.data[2] = value * CONVERT_A_Z;
            mHasPendingEvent = true;
        }
    }

    if (mHasPendingEvent) {
        LOGD(LOG_TAG "[KXTF9] %s: %d %d %d -> %f %f %f", __FUNCTION__,
                absinfo_x.value, absinfo_y.value, absinfo_z.value,
                mPendingEvent.data[0], mPendingEvent.data[1], mPendingEvent.data[2]);
    }

    return 0;
}

int KXTFSensor::enable(int32_t, int en)
{
    int flags = en ? 1 : 0;
    if (flags != mEnabled) {
        int fd;
        strcpy(&input_sysfs_path[input_sysfs_path_len], "enable");

        LOGI(LOG_TAG "[KXTF9] %s(%d) %s", __FUNCTION__, en, input_sysfs_path);
        fd = open(input_sysfs_path, O_RDWR);
        if (fd >= 0) {
            char buf[2];
            int err;
            buf[1] = 0;
            if (flags) {
                buf[0] = '1';
                mEnabledTime = getTimestamp() + IGNORE_EVENT_TIME;
            } else {
                buf[0] = '0';
            }
            err = write(fd, buf, sizeof(buf));
            close(fd);
            mEnabled = flags;
            setInitialState();
            return 0;
        }
        LOGE(LOG_TAG "[KXTF9] %s(%d) failed, err %d", __FUNCTION__, en, errno);
        return -1;
    }
    return 0;
}

bool KXTFSensor::hasPendingEvents() const {
    return mHasPendingEvent;
}

int KXTFSensor::setDelay(int32_t handle, int64_t delay_ns)
{
    int fd;
    strcpy(&input_sysfs_path[input_sysfs_path_len], "poll_delay");
    fd = open(input_sysfs_path, O_RDWR);
    if (fd >= 0) {
        char buf[80];
        sprintf(buf, "%lld", delay_ns);
        write(fd, buf, strlen(buf)+1);
        close(fd);
        return 0;
    }
    return -1;
}

int KXTFSensor::readEvents(sensors_event_t* data, int count)
{
    if (count < 1)
        return -EINVAL;

    if (mHasPendingEvent) {
        mHasPendingEvent = false;
        mPendingEvent.timestamp = getTimestamp();
        *data = mPendingEvent;
        return mEnabled ? 1 : 0;
    }

    ssize_t n = mInputReader.fill(data_fd);
    if (n < 0)
        return n;

    int numEventReceived = 0;
    input_event const* event;

    int timeout = 128;
#if FETCH_FULL_EVENT_BEFORE_RETURN
again:
#endif
    while (count && mInputReader.readEvent(&event)) {
        int type = event->type;
        if (type == EV_REL) {
            float value = event->value;
            if (event->code == EVENT_TYPE_ACCEL_X) {
                mPendingEvent.data[1] = value * KXTF9_CONVERT_A_Y; /* X/Y inversed */
            } else if (event->code == EVENT_TYPE_ACCEL_Y) {
                mPendingEvent.data[0] = value * KXTF9_CONVERT_A_X;
            } else if (event->code == EVENT_TYPE_ACCEL_Z) {
                mPendingEvent.data[2] = value * KXTF9_CONVERT_A_Z;
            }
        } else if (type == EV_SYN) {
            mPendingEvent.timestamp = timevalToNano(event->time);
            if (mEnabled) {
                if (mPendingEvent.timestamp >= mEnabledTime) {
                    *data++ = mPendingEvent;
                    numEventReceived++;
                }
                count--;
            }
        } else {
            LOGE(LOG_TAG "[KXTF9] %s: unknown event (type=%d, code=%d)",
                    __FUNCTION__, type, event->code);
        }
        mInputReader.next();
    }

#if FETCH_FULL_EVENT_BEFORE_RETURN
    /* if we didn't read a complete event, see if we can fill and
       try again instead of returning with nothing and redoing poll. */
    if (numEventReceived == 0 && mEnabled == 1 && --timeout) {
        n = mInputReader.fill(data_fd);
        if (n)
            goto again;
    }
#endif

    if (mHasPendingEvent) {
        LOGV(LOG_TAG "[KXTF9] %s: %d %d %d -> %f %f %f", __FUNCTION__,
                absinfo_x.value, absinfo_y.value, absinfo_z.value,
                mPendingEvent.data[0], mPendingEvent.data[1], mPendingEvent.data[2]);
    }

    return numEventReceived;
}

