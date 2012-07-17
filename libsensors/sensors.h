/*
 * Copyright (C) 2008 The Android Open Source Project
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

#ifndef ANDROID_SENSORS_H
#define ANDROID_SENSORS_H

#include <stdint.h>
#include <errno.h>
#include <sys/cdefs.h>
#include <sys/types.h>

#include <linux/input.h>

#include <hardware/hardware.h>
#include <hardware/sensors.h>

__BEGIN_DECLS

/*****************************************************************************/

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

#ifndef SENSOR_TYPE_AMBIENT_TEMPERATURE
#define SENSOR_TYPE_AMBIENT_TEMPERATURE SENSOR_TYPE_TEMPERATURE
#endif

#define ID_L  (SENSOR_TYPE_LIGHT)
#define ID_P  (SENSOR_TYPE_PROXIMITY)
#define ID_A  (SENSOR_TYPE_ACCELEROMETER)
#define ID_M  (SENSOR_TYPE_MAGNETIC_FIELD)
#define ID_O  (SENSOR_TYPE_ORIENTATION)
#define ID_GY (SENSOR_TYPE_GYROSCOPE)
#define ID_T  (SENSOR_TYPE_AMBIENT_TEMPERATURE)

#if 0
#define ID_A  (0)
#define ID_M  (1)
#define ID_O  (2)
#define ID_L  (3)
#define ID_P  (4)
#define ID_GY (5)
#endif

/*****************************************************************************/

/*
 * The SENSORS Module
 */

/* the CM3663 is a binary proximity sensor that triggers around 6 cm on
 * this hardware */
#define PROXIMITY_THRESHOLD_CM  6.0f

/*****************************************************************************/

#define AKM_DEVICE_NAME     "/dev/akm8975"
#define CM_DEVICE_NAME      "/dev/i2c11" // FIXME Proximity
#define LS_DEVICE_NAME      "/dev/i2c11" // FIXME Lig

/*
    E/Sensors ( 2656): AkmSensor: processing event (type=0, code=0)
    E/Sensors ( 2656): AkmSensor: processing event (type=2, code=8)
    E/Sensors ( 2656): AkmSensor: processing event (type=2, code=3)
    E/Sensors ( 2656): AkmSensor: processing event (type=2, code=4)
    E/Sensors ( 2656): AkmSensor: processing event (type=2, code=5)
    E/Sensors ( 2656): AkmSensor: processing event (type=2, code=0)
    E/Sensors ( 2656): AkmSensor: processing event (type=2, code=1)
    E/Sensors ( 2656): AkmSensor: processing event (type=2, code=2)
    E/Sensors ( 2656): AkmSensor: processing event (type=2, code=6)
    E/Sensors ( 2656): AkmSensor: processing event (type=2, code=7)
    E/Sensors ( 2656): AkmSensor: processing event (type=2, code=9)
    E/Sensors ( 2656): AkmSensor: processing event (type=0, code=0)
    E/Sensors ( 2656): AkmSensor: processing event (type=2, code=8)
    E/Sensors ( 2656): AkmSensor: processing event (type=2, code=3)
    E/Sensors ( 2656): AkmSensor: processing event (type=2, code=4)
    E/Sensors ( 2656): AkmSensor: processing event (type=2, code=5)
    E/Sensors ( 2656): AkmSensor: processing event (type=2, code=0)
    E/Sensors ( 2656): AkmSensor: processing event (type=2, code=1)
    E/Sensors ( 2656): AkmSensor: processing event (type=2, code=2)
    E/Sensors ( 2656): AkmSensor: processing event (type=2, code=6)
    E/Sensors ( 2656): AkmSensor: processing event (type=2, code=7)
    E/Sensors ( 2656): AkmSensor: processing event (type=2, code=9)
*/

// for akm8975
#define EVENT_TYPE_ACCEL_X          ABS_Y  //1
#define EVENT_TYPE_ACCEL_Y          ABS_X  //0
#define EVENT_TYPE_ACCEL_Z          ABS_Z  //2
//#define EVENT_TYPE_ACCEL_STATUS     ABS_WHEEL //8

#define EVENT_TYPE_YAW              ABS_RX  //3
#define EVENT_TYPE_PITCH            ABS_RY  //4
#define EVENT_TYPE_ROLL             ABS_RZ  //5
#define EVENT_TYPE_ORIENT_STATUS    ABS_WHEEL //8

#define EVENT_TYPE_MAGV_X           ABS_RUDDER  // 6
#define EVENT_TYPE_MAGV_Y           ABS_THROTTLE  // 7
#define EVENT_TYPE_MAGV_Z           ABS_GAS  // 9

#define EVENT_TYPE_TEMPERATURE      ABS_THROTTLE
#define EVENT_TYPE_STEP_COUNT       ABS_GAS
#define EVENT_TYPE_PROXIMITY        ABS_DISTANCE
#define EVENT_TYPE_LIGHT            ABS_MISC

#define EVENT_TYPE_GYRO_X           REL_RY
#define EVENT_TYPE_GYRO_Y           REL_RX
#define EVENT_TYPE_GYRO_Z           REL_RZ

// 90 LSB = 1G for KR3DM
#define LSB                         (90.0f)
#define NUMOFACCDATA                (8.0f)

// conversion of acceleration data to SI units (m/s^2)
#define RANGE_A                     (2*GRAVITY_EARTH)
#define CONVERT_A                   (GRAVITY_EARTH / LSB / NUMOFACCDATA)
#define CONVERT_A_X                 (CONVERT_A)
#define CONVERT_A_Y                 (-CONVERT_A)
#define CONVERT_A_Z                 (-CONVERT_A)

// factory kxtf9 (not mpu)
#define KXTF9_LSG                   (1000.0f)
#define KXTF9_CONVERT_A             (GRAVITY_EARTH / KXTF9_LSG)
#define KXTF9_CONVERT_A_X           (KXTF9_CONVERT_A)
#define KXTF9_CONVERT_A_Y           (-KXTF9_CONVERT_A)
#define KXTF9_CONVERT_A_Z           (-KXTF9_CONVERT_A)

// factory ak8975
#define AK8975_DEFAULT_DELAY               (200 * 1000000)

#define AK8975_LSG                         (1000.0f)
#define AK8975_CONVERT_A                   (GRAVITY_EARTH / AK8975_LSG)
#define AK8975_CONVERT_A_X                 (-AK8975_CONVERT_A)
#define AK8975_CONVERT_A_Y                 (AK8975_CONVERT_A)
#define AK8975_CONVERT_A_Z                 (-AK8975_CONVERT_A)

#define AK8975_CONVERT_M                   (1.0f/16.0f)
#define AK8975_CONVERT_M_X                 (AK8975_CONVERT_M)
#define AK8975_CONVERT_M_Y                 (-AK8975_CONVERT_M)
#define AK8975_CONVERT_M_Z                 (-AK8975_CONVERT_M)

#define AK8975_CONVERT_O                   (1.0f/64.0f)
#define AK8975_CONVERT_O_A                 (AK8975_CONVERT_O)
#define AK8975_CONVERT_O_P                 (AK8975_CONVERT_O)
#define AK8975_CONVERT_O_R                 (-AK8975_CONVERT_O)

#define AK8975_SENSOR_STATE_MASK           (0x3)

// conversion of magnetic data to uT units
#define CONVERT_M                   (1.0f/16.0f)
#define CONVERT_M_X                 (CONVERT_M)
#define CONVERT_M_Y                 (CONVERT_M)
#define CONVERT_M_Z                 (-CONVERT_M)

/* conversion of orientation data to degree units */
#define CONVERT_O                   (1.0f/64.0f)
#define CONVERT_O_A                 (CONVERT_O)
#define CONVERT_O_P                 (CONVERT_O)
#define CONVERT_O_R                 (-CONVERT_O)

// conversion of gyro data to SI units (radian/sec)
#define RANGE_GYRO                  (2000.0f*(float)M_PI/180.0f)
#define CONVERT_GYRO                ((70.0f / 1000.0f) * ((float)M_PI / 180.0f))
#define CONVERT_GYRO_X              (CONVERT_GYRO)
#define CONVERT_GYRO_Y              (-CONVERT_GYRO)
#define CONVERT_GYRO_Z              (CONVERT_GYRO)

#define SENSOR_STATE_MASK           (0x7FFF)

/*****************************************************************************/

__END_DECLS

#endif  // ANDROID_SENSORS_H
