# manual operations made after the ota zip and before the squished final zip
# This script is included in squisher
# It is the final build step (after OTA package)

# set in squisher
# DEVICE_OUT=$ANDROID_BUILD_TOP/out/target/product/i9103
# DEVICE_TOP=$ANDROID_BUILD_TOP/device/samsung/i9103
# VENDOR_TOP=$ANDROID_BUILD_TOP/vendor/samsung/i9103

# Delete unwanted apps
rm -f $REPACK/ota/system/app/RomManager.apk
rm -f $REPACK/ota/system/app/FOTAKill.apk
rm -f $REPACK/ota/system/xbin/irssi

# these scripts are not required
rm $REPACK/ota/system/etc/init.d/03firstboot
rm $REPACK/ota/system/etc/init.d/04modules

# 
