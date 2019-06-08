#
# This is a project Makefile. It is assumed the directory this Makefile resides in is a
# project subdirectory.
#

# PROJECT_NAME := blink

# include $(IDF_PATH)/make/project.mk


#
# This is a project Makefile. It is assumed the directory this Makefile resides in is a
# project subdirectory.
#

PROJECT_NAME := afr_esp32

# ifndef AMAZON_FREERTOS_PATH
# $(error AMAZON_FREERTOS_PATH is not set)
# endif

# IDF_PATH := $(AMAZON_FREERTOS_PATH)/lib/third_party/mcu_vendor/espressif/esp-idf

IDF_PATH := $(CURDIR)/lib/third_party/mcu_vendor/espressif/esp-idf

EXTRA_COMPONENT_DIRS := \
	$(CURDIR)/espressif_code \
	$(CURDIR)/lib \
	$(CURDIR)/common

include $(IDF_PATH)/make/project.mk

