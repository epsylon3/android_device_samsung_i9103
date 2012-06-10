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

PRODUCT_COPY_FILES += \
    ${device_top}/recovery/recovery.fstab:system/etc/recovery.fstab \

PRODUCT_COPY_FILES += \
    ${device_top}/root/init.rc:root/init.rc \
    ${device_top}/root/init.n1.rc:root/init.tegra.rc \
    ${device_top}/root/ueventd.rc:root/ueventd.rc
