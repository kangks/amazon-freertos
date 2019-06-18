ROOT := ../..

COMPONENT_ADD_INCLUDEDIRS := \
	./include \
	$(ROOT)/lib/include \
	$(ROOT)/common/include \
	$(ROOT)/lib/FreeRTOS-Plus-TCP\include 

COMPONENT_SRCDIRS := \
	. \
	$(ROOT)/common/devmode_key_provisioning \
	$(ROOT)/lib/FreeRTOS-Plus-TCP/source \
	$(ROOT)/lib/utils \
	$(ROOT)/lib/mqtt

COMPONENT_PRIV_INCLUDEDIRS := \
	$(ROOT)/lib/include/private