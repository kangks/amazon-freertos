ROOT := ../..

COMPONENT_ADD_INCLUDEDIRS := \
	./include \
	$(ROOT)/lib/include \
	$(ROOT)/common/include \
	$(ROOT)/lib/FreeRTOS-Plus-TCP\include \
	$(ROOT)/lib/include \
	$(ROOT)/lib/third_party/pkcs11 

# COMPONENT_SRCDIRS := \
# 	. \
# 	$(ROOT)/common/devmode_key_provisioning \
# 	$(ROOT)/lib/FreeRTOS-Plus-TCP/source \
# 	$(ROOT)/lib/utils \
# 	$(ROOT)/lib/wifi/portable/espressif/esp32_devkitc_esp_wrover_kit 

COMPONENT_PRIV_INCLUDEDIRS := \
	$(ROOT)/lib/include/private