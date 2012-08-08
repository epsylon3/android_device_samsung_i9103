# Copyright (C) 2012 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

device_top := device/samsung/i9103

# key layouts, names must fit the ones in /proc/bus/input/devices, qwerty.kl is the fallback one.
PRODUCT_COPY_FILES += \
    ${device_top}/usr/keylayout/qwerty.kl:system/usr/keylayout/qwerty.kl \
    ${device_top}/usr/keylayout/qwerty.kl:system/usr/keylayout/sec_touchscreen.kl \
    ${device_top}/usr/keylayout/sec_jack.kl:system/usr/keylayout/sec_jack.kl \
    ${device_top}/usr/keylayout/sec_key.kl:system/usr/keylayout/sec_key.kl \

# etc
PRODUCT_COPY_FILES += \
    ${device_top}/etc/busybox.fstab:system/etc/fstab \
    ${device_top}/etc/media_profiles.xml:system/etc/media_profiles.xml \
    ${device_top}/etc/profile:system/etc/profile \
    ${device_top}/etc/sysctl.conf:system/etc/sysctl.conf \
    ${device_top}/etc/sirfgps.conf:system/etc/sirfgps.conf \

# device specs
PRODUCT_COPY_FILES += \
    frameworks/base/data/etc/android.hardware.camera.flash-autofocus.xml:system/etc/permissions/android.hardware.camera.flash-autofocus.xml \
    frameworks/base/data/etc/android.hardware.camera.front.xml:system/etc/permissions/android.hardware.camera.front.xml \
    frameworks/base/data/etc/android.hardware.location.gps.xml:system/etc/permissions/android.hardware.location.gps.xml \
    frameworks/base/data/etc/android.hardware.sensor.light.xml:system/etc/permissions/android.hardware.sensor.light.xml \
    frameworks/base/data/etc/android.hardware.sensor.proximity.xml:system/etc/permissions/android.hardware.sensor.proximity.xml \
    frameworks/base/data/etc/android.hardware.sensor.accelerometer.xml:system/etc/permissions/android.hardware.sensor.accelerometer.xml \
    frameworks/base/data/etc/android.hardware.sensor.compass.xml:system/etc/permissions/android.hardware.sensor.compass.xml \
    frameworks/base/data/etc/android.hardware.telephony.gsm.xml:system/etc/permissions/android.hardware.telephony.gsm.xml \
    frameworks/base/data/etc/android.hardware.touchscreen.multitouch.jazzhand.xml:system/etc/permissions/android.hardware.touchscreen.multitouch..jazzhand.xml \

# recovery
PRODUCT_COPY_FILES += \
    ${device_top}/recovery/recovery.fstab:recovery/root/etc/recovery.fstab \
    ${device_top}/recovery/init.rc:recovery/root/init.rc \
    ${device_top}/root/ueventd.rc:recovery/root/ueventd.rc

# kernel
PRODUCT_COPY_FILES += \
    ${device_top}/root/init.n1.rc:root/init.n1.rc \
    ${device_top}/root/ueventd.n1.rc:root/ueventd.n1.rc \
    ${device_top}/root/init.lpm.rc:root/init.lpm.rc
