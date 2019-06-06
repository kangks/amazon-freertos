#
# "main" pseudo-component makefile.
#
# (Uses default behaviour of compiling all source files in directory, adding 'include' to include path.)

# AMAZON_FREERTOS_LIB_DIR := ../lib

COMPONENT_ADD_INCLUDEDIRS := \
	include \
	../common/include

COMPONENT_SRCDIRS := \
	. \
	../common/logging
	
# COMPONENT_ADD_LDFLAGS += -Wl,--undefined=uxTopUsedPriority
