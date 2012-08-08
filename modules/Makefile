# Makefile for Android.mk based kernel tree
# "make device_modules" in repo root (not here)


# list of modules to build :
obj-m += j4fs/
obj-m += symsearch/
obj-m += klogger/

PWD := $(shell pwd)

.PHONY: clean
#######################################################################################
clean:
	@find $(PWD) | grep "\\.o$$" | xargs rm -f
	@find $(PWD) | grep "\\.ko$$" | xargs rm -f
	@find $(PWD) | grep "\\.cmd$$" | xargs rm -f
	@find $(PWD) | grep "\\.mod.c$$" | xargs rm -f
	@find $(PWD) | grep "\\.order$$" | xargs rm -f
	@find $(PWD) | grep "\\.tmp_versions$$" | xargs rm -rf
	@cd $(PWD) && git checkout *.ko


EXTRA_CFLAGS += -I$(KERNEL_DIR)

ifneq ($(TARGET_KERNEL_UTSRELEASE),)
	EXTRA_CFLAGS += -DUTS_RELEASE=\\\"$(TARGET_KERNEL_UTSRELEASE)\\\"
endif

.PHONY: all
#######################################################################################
# Build the modules
#######################################################################################
all: modules
modules:
	pwd
	@echo $@ EXTRA_CFLAGS = $(EXTRA_CFLAGS)
	$(MAKE) CROSS_COMPILE=$(CROSS_COMPILE) EXTRA_CFLAGS="$(EXTRA_CFLAGS)" ARCH=$(ARCH) -C $(KERNEL_DIR) M=$(PWD) modules
	@find $(PWD) | grep "\\.o$$" | xargs rm -f
	@find $(PWD) | grep "\\.cmd$$" | xargs rm -f
	@find $(PWD) | grep "\\.mod.c$$" | xargs rm -f
	@find $(PWD) | grep "\\.order$$" | xargs rm -f
	@find $(PWD) | grep "\\.tmp_versions$$" | xargs rm -rf

device_modules:
	@echo YOU ARE NOT AT THE GOOD PLACE TO DO THAT ! go to repo root and copy/paste that :
	@echo
	@echo . build/envsetup.sh
	@echo bib jordan
	@echo make device_modules
