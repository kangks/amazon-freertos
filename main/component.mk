#
# "main" pseudo-component makefile.
#
# (Uses default behaviour of compiling all source files in directory, adding 'include' to include path.)

AMAZON_FREERTOS_LIB_DIR := ../lib
ESPRESSIF_DIR := ../espressif_code

COMPONENT_ADD_INCLUDEDIRS := \
	include \
	$(AMAZON_FREERTOS_LIB_DIR)/FreeRTOS-Plus-TCP/include \
	$(ESPRESSIF_DIR)/tcpip_adapter/include

COMPONENT_SRCDIRS := \
	. \
	$(AMAZON_FREERTOS_LIB_DIR)/FreeRTOS-Plus-TCP/source \
	$(AMAZON_FREERTOS_LIB_DIR)/FreeRTOS-Plus-TCP/source/portable/NetworkInterface/esp32 \
	$(ESPRESSIF_DIR)/tcpip_adapter/ 

COMPONENT_PRIV_INCLUDEDIRS := \
	$(AMAZON_FREERTOS_LIB_DIR)/include/private

COMPONENT_DEPENDS := \
	esp32Wifi \
	ssd1306 \
	oledDisplay \
	ttgo-tcamera-esp32 \
	awsIoTMqtt 


# COMPONENT_ADD_LDFLAGS += -Wl,--undefined=uxTopUsedPriority
