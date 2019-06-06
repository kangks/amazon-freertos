AMAZON_FREERTOS_LIB_DIR := ../../lib

COMPONENT_ADD_INCLUDEDIRS := \
	include \
	../../config_files \
	$(AMAZON_FREERTOS_LIB_DIR)/include \
	$(AMAZON_FREERTOS_LIB_DIR)/include/private \
	$(AMAZON_FREERTOS_LIB_DIR)/FreeRTOS-Plus-TCP/include \
	$(AMAZON_FREERTOS_LIB_DIR)/FreeRTOS-Plus-TCP/source/portable/Compiler/GCC

COMPONENT_SRCDIRS := \
	source 
	
# COMPONENT_ADD_LDFLAGS += -Wl,--undefined=uxTopUsedPriority
