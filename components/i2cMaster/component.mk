ROOT := ../..

COMPONENT_ADD_INCLUDEDIRS := \
	./include \
	$(ROOT)/lib/third_party/mcu_vendor/espressif/esp-idf/components/driver/include \
	$(ROOT)/lib/include \
	$(ROOT)/common/include 
	
COMPONENT_SRCDIRS := \
	. \
	$(ROOT)/lib/third_party/mcu_vendor/espressif/esp-idf/components/driver 

COMPONENT_PRIV_INCLUDEDIRS := \
	$(ROOT)/lib/include/private