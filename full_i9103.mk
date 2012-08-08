###############################################################################
# Device Packages
###############################################################################

# The gps config appropriate for this device
$(call inherit-product, device/common/gps/gps_eu_supl.mk)

###############################################################################

$(call inherit-product-if-exists, vendor/samsung/i9103/i9103-vendor.mk)

###############################################################################

# Telephony properties
PRODUCT_PROPERTY_OVERRIDES += \
    ro.ril.enable.3g.prefix=1 \
    ro.ril.enable.a53=1 \
    ro.ril.enable.dtm=1 \
    ro.ril.enable.managed.roaming=1 \
    ro.ril.gprsclass=12 \
    ro.ril.hep=1 \
    ro.ril.hsdpa.category=8 \
    ro.ril.hsupa.category=5 \
    ro.ril.hsxpa=2 \
    ro.kernel.android.ril=yes \
    ro.telephony.ril_class=samsung \
    rild.libpath=/system/lib/libsec-ril.so \
    rild.libargs="-d /dev/ttyS0"

###############################################################################

PRODUCT_PACKAGES += \
    sensors.GT-I9103 \
    lights.GT-I9103 \
    gps.GT-I9103 \
    gralloc.tegra \
    overlay.tegra

# device modules
PRODUCT_PACKAGES += libaudio libaudiopolicy amix aplay arec

# external packages
PRODUCT_PACKAGES += bdaddr_read hcitool hciconfig

# tools for communication (most included in cm7 config, but remember for ics)
PRODUCT_PACKAGES += DroidSSHd dropbear dropbearkey sftp-server scp ssh rsync

###############################################################################

ifeq ($(TARGET_PREBUILT_KERNEL),)
    LOCAL_KERNEL := device/samsung/i9103/kernel
else
    LOCAL_KERNEL := $(TARGET_PREBUILT_KERNEL)
endif

PRODUCT_COPY_FILES += $(LOCAL_KERNEL):kernel

# copy all others kernel modules under the "modules" dir. to system/lib/modules
PRODUCT_COPY_FILES += $(shell test -d device/samsung/i9103/modules && \
        find device/samsung/i9103/modules -name '*.ko' \
        -printf '%p:system/lib/modules/%f ')

###############################################################################

$(call inherit-product, device/samsung/i9103/blobs_i9103.mk)

###############################################################################

DEVICE_PACKAGE_OVERLAYS += device/samsung/i9103/overlay

$(call inherit-product, build/target/product/full_base.mk)

# Should be after the full_base include, which loads languages_full
PRODUCT_LOCALES += hdpi

PRODUCT_NAME := full_i9103
PRODUCT_DEVICE := i9103

