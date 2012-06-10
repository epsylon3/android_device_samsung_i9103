# The gps config appropriate for this device
$(call inherit-product, device/common/gps/gps_eu_supl.mk)

$(call inherit-product-if-exists, vendor/samsung/i9103/i9103-vendor.mk)

DEVICE_PACKAGE_OVERLAYS += device/samsung/i9103/overlay

PRODUCT_PACKAGES += hcitool hciconfig

ifeq ($(TARGET_PREBUILT_KERNEL),)
        LOCAL_KERNEL := device/samsung/i9103/kernel
else
        LOCAL_KERNEL := $(TARGET_PREBUILT_KERNEL)
endif

PRODUCT_COPY_FILES += $(LOCAL_KERNEL):kernel
$(call inherit-product, device/samsung/i9103/blobs_i9103.mk)

$(call inherit-product, build/target/product/full_base.mk)

# Should be after the full_base include, which loads languages_full
PRODUCT_LOCALES += hdpi

PRODUCT_NAME := full_i9103
PRODUCT_DEVICE := i9103
