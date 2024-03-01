cmake_minimum_required(VERSION 3.13)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)
set(PICO_BOARD "pico_w")

project(boardtest)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# rest of your project
add_executable(boardtest
    main.cpp
    hardware.cpp
    hardware.h
    config.h
)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(boardtest pico_stdlib hardware_adc )

# enable uart output, disable usb output in wokwi simulator
pico_enable_stdio_usb(boardtest 0)
pico_enable_stdio_uart(boardtest 1)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(boardtest)
