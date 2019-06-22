afr_module(NAME ttgo STATIC)

set(inc_dir "${CMAKE_CURRENT_LIST_DIR}/include")
set(espressif_code_dir "${AFR_VENDORS_DIR}/espressif/boards/esp32/aws_demos/application_code/espressif_code")
set(AMAZON_FREERTOS_FREERTOS_PLUS_DIR "${AFR_MODULES_FREERTOS_PLUS_DIR}")

set(COMPONENT_SRCS
  app_camera.c
  awsIoTMqtt.cpp
  esp32Wifi.cpp
  fonts.c
  I2CMaster.cpp
  OledDisplay.cpp
  SSD1306.cpp
  )

set(COMPONENT_ADD_INCLUDEDIRS
  include
  )

set(COMPONENT_REQUIRES esp32-camera)
set(COMPONENT_PRIV_REQUIRES freertos)

afr_module_sources(
    ${AFR_CURRENT_MODULE}
    PUBLIC
      "${CMAKE_CURRENT_LIST_DIR}/app_camera.c"
      "${CMAKE_CURRENT_LIST_DIR}/awsIoTMqtt.cpp"
      "${CMAKE_CURRENT_LIST_DIR}/esp32Wifi.cpp"
      "${CMAKE_CURRENT_LIST_DIR}/fonts.c"
      "${CMAKE_CURRENT_LIST_DIR}/I2CMaster.cpp"
      "${CMAKE_CURRENT_LIST_DIR}/OledDisplay.cpp"
      "${CMAKE_CURRENT_LIST_DIR}/SSD1306.cpp"
)

afr_module_include_dirs(
    ${AFR_CURRENT_MODULE}
    PUBLIC
      "${inc_dir}"
      $<TARGET_PROPERTY:AFR::freertos,INTERFACE_INCLUDE_DIRECTORIES>
      "${espressif_code_dir}/esp32-camera/driver/include"
      "${espressif_code_dir}/esp32-camera/conversions/include"
      ${AMAZON_FREERTOS_FREERTOS_PLUS_DIR}/standard/freertos_plus_tcp/include
)


afr_module_dependencies(
    ${AFR_CURRENT_MODULE}
    PUBLIC
      AFR::mqtt
      AFR::utils
      AFR::wifi
      AFR::freertos
      AFR::kernel
    INTERFACE
      AFR::freertos_plus_tcp
      AFR::tls
      AFR::crypto
      AFR::pkcs11
)

#register_component()