#
# "main" pseudo-component makefile.
#
# (Uses default behaviour of compiling all source files in directory, adding 'include' to include path.)

# AMAZON_FREERTOS_LIB_DIR := ../lib

COMPONENT_ADD_INCLUDEDIRS := \
	include \
	../common/include \
	../lib/include \
	../lib/FreeRTOS-Plus-TCP/include \
	../espressif_code/tcpip_adapter/include

COMPONENT_SRCDIRS := \
	. \
	../common/logging \
	../lib/FreeRTOS-Plus-TCP/source \
	../lib/utils \
	../lib/bufferpool \
	../lib/FreeRTOS-Plus-TCP/source/portable/NetworkInterface/esp32 \
	../espressif_code/tcpip_adapter/

COMPONENT_PRIV_INCLUDEDIRS := \
	../lib/include/private

COMPONENT_DEPENDS := \
	esp32Wifi \
	ssd1306 \
	oledDisplay


# COMPONENT_ADD_LDFLAGS += -Wl,--undefined=uxTopUsedPriority
