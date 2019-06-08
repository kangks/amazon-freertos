AMAZON_FREERTOS_LIB_DIR := ../../lib

COMPONENT_SRCDIRS := $(AMAZON_FREERTOS_LIB_DIR)/mqtt \
        $(AMAZON_FREERTOS_LIB_DIR)/shadow \
        $(AMAZON_FREERTOS_LIB_DIR)/greengrass \
        $(AMAZON_FREERTOS_LIB_DIR)/utils \
        $(AMAZON_FREERTOS_LIB_DIR)/bufferpool \
        $(AMAZON_FREERTOS_LIB_DIR)/tls \
        $(AMAZON_FREERTOS_LIB_DIR)/ota \
        $(AMAZON_FREERTOS_LIB_DIR)/crypto \
        $(AMAZON_FREERTOS_LIB_DIR)/wifi/portable/espressif/esp32_devkitc_esp_wrover_kit \
        $(AMAZON_FREERTOS_LIB_DIR)/ota/portable/espressif/esp32_devkitc_esp_wrover_kit \
        $(AMAZON_FREERTOS_LIB_DIR)/secure_sockets/portable/freertos_plus_tcp \
        $(AMAZON_FREERTOS_LIB_DIR)/pkcs11/portable/espressif/esp32_devkitc_esp_wrover_kit \
        $(AMAZON_FREERTOS_LIB_DIR)/pkcs11/mbedtls \
        $(AMAZON_FREERTOS_LIB_DIR)/FreeRTOS-Plus-TCP/source \
        $(AMAZON_FREERTOS_LIB_DIR)/FreeRTOS-Plus-TCP/source/portable/BufferManagement \
        $(AMAZON_FREERTOS_LIB_DIR)/FreeRTOS-Plus-TCP/source/portable/NetworkInterface/esp32 \
        $(AMAZON_FREERTOS_LIB_DIR)/FreeRTOS-Plus-POSIX/source \
        $(AMAZON_FREERTOS_LIB_DIR)/third_party/jsmn \
        $(AMAZON_FREERTOS_LIB_DIR)/third_party/tinycbor

COMPONENT_ADD_INCLUDEDIRS := $(AMAZON_FREERTOS_LIB_DIR)/FreeRTOS-Plus-TCP/include \
                             $(AMAZON_FREERTOS_LIB_DIR)/FreeRTOS-Plus-TCP/source/portable/Compiler/GCC \
                             $(AMAZON_FREERTOS_LIB_DIR)/FreeRTOS-Plus-POSIX/include \
                             $(AMAZON_FREERTOS_LIB_DIR)/FreeRTOS-Plus-POSIX/include/portable/espressif/esp32_devkitc_esp_wrover_kit \
                             $(AMAZON_FREERTOS_LIB_DIR)/third_party/jsmn \
                             $(AMAZON_FREERTOS_LIB_DIR)/third_party/tinycbor

COMPONENT_OBJEXCLUDE := $(AMAZON_FREERTOS_LIB_DIR)/FreeRTOS-Plus-TCP/source/portable/BufferManagement/BufferAllocation_1.o \
                        $(AMAZON_FREERTOS_LIB_DIR)/FreeRTOS-Plus-POSIX/source/FreeRTOS_POSIX_pthread.o \
                        $(AMAZON_FREERTOS_LIB_DIR)/FreeRTOS-Plus-POSIX/source/FreeRTOS_POSIX_pthread_mutex.o \
                        $(AMAZON_FREERTOS_LIB_DIR)/FreeRTOS-Plus-POSIX/source/FreeRTOS_POSIX_pthread_cond.o \
                        $(AMAZON_FREERTOS_LIB_DIR)/FreeRTOS-Plus-POSIX/source/FreeRTOS_POSIX_sched.o


COMPONENT_PRIV_INCLUDEDIRS := $(AMAZON_FREERTOS_LIB_DIR)/third_party/pkcs11 $(AMAZON_FREERTOS_LIB_DIR)/ota/portable/espressif/esp32_devkitc_esp_wrover_kit

lib/greengrass/aws_greengrass_discovery.o: CFLAGS+=-Wno-format
demos/common/logging/aws_logging_task_dynamic_buffers.o: CFLAGS+=-Wno-format -Wno-uninitialized
demos/common/tcp/aws_tcp_echo_client_single_task.o: CFLAGS+=-Wno-format
