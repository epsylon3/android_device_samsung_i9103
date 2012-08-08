android_device_samsung_i9103
============================

This is my initial contribution for the Galaxy R, it's a preliminary setup which
allow to build the kernel, modules and a basic cm7 rom.

PLEASE NOTE I DON'T HAVE THE DEVICE YET (will have it soon) SO DONT FLASH THIS :p

Add these 3 projects in your .repo/manifest.xml ( or .repo/local_manifest.xml ) and repo sync

	<project path="device/samsung/i9103" name="epsylon3/android_device_samsung_i9103" remote="github" />
	<project path="vendor/samsung/i9103" name="epsylon3/android_vendor_samsung_i9103" remote="github" />
	<project path="kernel/samsung/i9103" name="epsylon3/android_kernel_samsung_i9103" remote="github" />

Also, you need to edit cyanogen vendor repo and change "CyanogenMod" to "epsylon3"

	<project path="vendor/cyanogen" name="epsylon3/android_vendor_cyanogen" />

you can also cherry pick (or merge) the initial commit present in this repo (which adds the device)

Then type for a "full" build :

	. build/envsetup.sh
	brunch i9103
