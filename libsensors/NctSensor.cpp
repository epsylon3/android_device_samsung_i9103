/*
 * Copyright (C) 2012 The Android Open Source Project
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

#include <fcntl.h>
#include <errno.h>
#include <math.h>
#include <poll.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/select.h>

//#define LOG_NDEBUG 0

#include <cutils/log.h>

#include "NctSensor.h"

#define TAG "[NCT] "

/*****************************************************************************/

NctSensor::NctSensor()
    : SensorBase(NCT_DEVICE_NAME, NULL),
      mEnabled(0),
      mInputReader(4),
      mHasPendingEvent(false)
{
    mPendingEvent.version = sizeof(sensors_event_t);
    mPendingEvent.sensor = ID_T;
    mPendingEvent.type = SENSOR_TYPE_TEMPERATURE;
    memset(mPendingEvent.data, 0, sizeof(mPendingEvent.data));

    if (getFd()) {
        enable(0, 1);
    }
}

NctSensor::~NctSensor() {
    if (mEnabled) {
        enable(0, 0);
    }
}

int NctSensor::readSysFsValue(void) {
    struct input_absinfo absinfo;
    int fd = getFd();

    if (!mEnabled) {
        return 0;
    }

    if (fd > 0) {
        close_device();
        open_device();
    }

    fd = getFd();
    if (fd > 0) {
        char buf[8] = "";
        read(fd, &buf[0], sizeof(buf));

        int nr = sscanf(buf, "%d", &absinfo.value);
        if (nr >= 0) {
            LOGV(TAG "%s read=%d", __FUNCTION__, absinfo.value);
            mPendingEvent.timestamp = getTimestamp();
            mPendingEvent.data[0] = convertTemperature(absinfo.value);
            mHasPendingEvent = true;
        }
    }

    return 0;
}

int NctSensor::enable(int32_t, int en) {
    int flags = en ? 1 : 0;

    LOGV(TAG "%s(%d)", __FUNCTION__, en);

    if (!mEnabled) {
        open_device();
    } else {
        close_device();
    }

    if (flags != mEnabled) {
        mEnabled = flags;
        if (mEnabled) {
            if (getFd() > 0)
                readSysFsValue();
            else {
                mEnabled = false;
                LOGW(TAG "unable to enable the sensor");
                return -EIO;
            }
        }
    }
    return 0;
}

bool NctSensor::hasPendingEvents() const {
    return mHasPendingEvent;
}

int NctSensor::readEvents(sensors_event_t* data, int count)
{
    if (count < 1)
        return -EINVAL;

    int numRecords = 0;

    readSysFsValue();

    while (count) {
        LOGV(TAG "%s has pending data", __FUNCTION__);
        if (mEnabled) {
                *data++ = mPendingEvent;
                numRecords++;
        }
        count--;
    }
    return mEnabled ? numRecords : 0;
}

float NctSensor::convertTemperature(int value) const
{
    return (value * 1.0);
}
