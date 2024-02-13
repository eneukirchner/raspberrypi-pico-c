cmake_minimum_required(VERSION 3.13)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)
set(PICO_BOARD "pico_w")

project(blink)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# rest of your project
add_executable(blink
    blink.c
)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(blink pico_stdlib hardware_adc hardware_pwm)

# enable usb output, disable uart output
pico_enable_stdio_usb(blink 1)
pico_enable_stdio_uart(blink 0)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(blink)
