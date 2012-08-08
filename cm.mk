# Specify phone tech before including full_phone
$(call inherit-product, vendor/cm/config/gsm.mk)

# Release name
PRODUCT_RELEASE_NAME := i9103

# Boot animation
TARGET_BOOTANIMATION_NAME := vertical-480x800

# Inherit some common CM stuff.
$(call inherit-product, vendor/cm/config/common_full_phone.mk)

# Inherit device configuration
$(call inherit-product, device/samsung/i9103/full_i9103.mk)

# Device identifier. This must come after all inclusions
PRODUCT_DEVICE := i9103
PRODUCT_NAME := cm_i9103
PRODUCT_BRAND := samsung
PRODUCT_MODEL := GT-I903
PRODUCT_MANUFACTURER := samsung

# Set build fingerprint / ID / Product Name ect.
PRODUCT_BUILD_PROP_OVERRIDES += PRODUCT_NAME=Galaxy-R TARGET_DEVICE=n1 BUILD_FINGERPRINT="samsung/m0xx/m0:4.0.4/IMM76D/I9300XXALE8:user/release-keys" PRIVATE_BUILD_DESC="n1-user 4.0.4 IMM76D I9103XXALE8 release-keys"
