###### generic audio, copied from aries common #####

ifneq ($(TARGET_PROVIDES_LIBAUDIO),true)

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= aplay.c alsa_pcm.c alsa_mixer.c
LOCAL_MODULE := aplay
LOCAL_SHARED_LIBRARIES:= libc libcutils
LOCAL_MODULE_TAGS := optional
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= arec.c alsa_pcm.c
LOCAL_MODULE := arec
LOCAL_SHARED_LIBRARIES:= libc libcutils
LOCAL_MODULE_TAGS := optional
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= amix.c alsa_mixer.c
LOCAL_MODULE := amix
LOCAL_SHARED_LIBRARIES := libc libcutils
LOCAL_MODULE_TAGS := optional
include $(BUILD_EXECUTABLE)


include $(CLEAR_VARS)
LOCAL_SRC_FILES := AudioHardware.cpp alsa_mixer.c alsa_pcm.c
LOCAL_MODULE := libaudio
LOCAL_MODULE_TAGS := optional
LOCAL_STATIC_LIBRARIES := libaudiointerface
LOCAL_SHARED_LIBRARIES := libc libcutils libutils
LOCAL_SHARED_LIBRARIES += libmedia libhardware_legacy

ifeq ($(BOARD_HAVE_BLUETOOTH),true)
    LOCAL_CFLAGS += -DWITH_A2DP
    LOCAL_SHARED_LIBRARIES += liba2dp
endif
ifeq ($(BOARD_HAVE_FM_RADIO),true)
    LOCAL_CFLAGS += -DHAVE_FM_RADIO
endif

ifeq ($(TARGET_SIMULATOR),true)
    LOCAL_LDLIBS += -ldl
else
    LOCAL_SHARED_LIBRARIES += libdl
endif

include $(BUILD_SHARED_LIBRARY)


include $(CLEAR_VARS)
LOCAL_SRC_FILES := AudioPolicyManager.cpp
LOCAL_MODULE := libaudiopolicy
LOCAL_MODULE_TAGS := optional
LOCAL_STATIC_LIBRARIES:= libaudiopolicybase
LOCAL_SHARED_LIBRARIES:= libc libcutils libutils libmedia

ifeq ($(BOARD_HAVE_BLUETOOTH),true)
    LOCAL_CFLAGS += -DWITH_A2DP
endif
ifeq ($(BOARD_HAVE_FM_RADIO),true)
    LOCAL_CFLAGS += -DHAVE_FM_RADIO
endif

include $(BUILD_SHARED_LIBRARY)


endif # TARGET_PROVIDES_LIBAUDIO
