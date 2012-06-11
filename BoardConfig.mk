
TARGET_BOOTLOADER_BOARD_NAME := GT-I9103
TARGET_OTA_ASSERT_DEVICE := i9103,n1,GT-I9103

TARGET_NO_BOOTLOADER := true
TARGET_BOARD_PLATFORM := tegra
TARGET_CPU_ABI := armeabi-v7a
TARGET_CPU_ABI2 := armeabi
TARGET_ARCH_VARIANT := armv7-a
TARGET_ARCH_VARIANT_CPU := cortex-a9
TARGET_ARCH_VARIANT_FPU := vfpv3-d16
TARGET_HAVE_TEGRA_ERRATA_657451 := true
#TARGET_CPU_SMP := true

BOARD_KERNEL_BASE := 0x10000000
BOARD_PAGE_SIZE := 0x00000800
TARGET_PREBUILT_KERNEL := device/samsung/i9103/kernel
TARGET_KERNEL_MODULES_EXT := device/samsung/i9103/modules
TARGET_KERNEL_UTSRELEASE  := 2.6.36.3
KERNEL_SRC_DIR := $(ANDROID_BUILD_TOP)/kernel/samsung/i9103

# do not update the device tree...
DO_NO_REBUILT_THE_KERNEL := 1

#TARGET_NO_BOOT := false

# use a prebuilt init.rc for the first roms
TARGET_PROVIDES_INIT_RC := true
TARGET_NO_RECOVERY := false
TARGET_RECOVERY_INITRC := ./device/samsung/i9103/recovery/init.rc
TARGET_RECOVERY_PIXEL_FORMAT := "RGB_565"
BOARD_HAS_SMALL_RECOVERY := true
#BOARD_CUSTOM_RECOVERY_KEYMAPPING:= ../../device/samsung/i9103/recovery/recovery_ui.c

BOARD_BOOTIMAGE_PARTITION_SIZE := 8388608
#BOARD_RECOVERYIMAGE_PARTITION_SIZE := 8388608
#BOARD_SYSTEMIMAGE_PARTITION_SIZE := 629145600
#BOARD_USERDATAIMAGE_PARTITION_SIZE := 2147483648
BOARD_SYSTEMIMAGE_PARTITION_SIZE   := 209715200 # let them small, we use a zip... 200M
BOARD_USERDATAIMAGE_PARTITION_SIZE := 104857600 # must be a multiple of the block size
BOARD_FLASH_BLOCK_SIZE := 4096
BOARD_HAS_LARGE_FILESYSTEM := true
BOARD_USES_MMCUTILS := true

BOARD_VOLD_EMMC_SHARES_DEV_MAJOR := true
BOARD_SDEXT_DEVICE := /dev/block/mmcblk1p2

TARGET_USERIMAGES_USE_EXT4 := true

# Wifi
BOARD_WPA_SUPPLICANT_DRIVER := WEXT
WPA_SUPPLICANT_VERSION      := VER_0_6_X
#BOARD_WLAN_DEVICE           := broadcom
BOARD_WLAN_DEVICE           := bcm4330
WIFI_DRIVER_MODULE_NAME     := "dhd"
DRIVER_MODULE_TAG           := "dhd"
WIFI_DRIVER_MODULE_PATH     := "/system/lib/modules/dhd.ko"
WIFI_DRIVER_MODULE_ARG      := "nvram_path=/system/etc/wifi/nvram_net.txt firmware_path=/system/etc/wifi/bcm4330_sta.bin"
WIFI_DRIVER_FW_STA_PATH     := "/system/etc/wifi/bcm4330_sta.bin"
WIFI_DRIVER_FW_AP_PATH      := "/system/etc/wifi/bcm4330_aps.bin"

# Bluetooth
BOARD_HAVE_BLUETOOTH := true
BOARD_HAVE_BLUETOOTH_BCM := true

# Camera
USE_CAMERA_STUB := false
BOARD_CAMERA_LIBRARIES := libcamera
BOARD_SECOND_CAMERA_DEVICE := true

# Audio
BOARD_USES_GENERIC_AUDIO := false
TARGET_PROVIDES_LIBAUDIO := false # build them

# Usb
BOARD_USE_USB_MASS_STORAGE_SWITCH := true
BOARD_UMS_LUNFILE := "/sys/devices/platform/usb_mass_storage/lun0/file"

# EGL
BOARD_EGL_CFG := device/samsung/i9103/etc/egl.cfg

# Custom squisher, final step script
TARGET_CUSTOM_RELEASETOOL := ./device/samsung/i9103/releasetools/squisher

