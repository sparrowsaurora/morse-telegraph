cmake_minimum_required(VERSION 3.13)
include($ENV{PICO_SDK_PATH}/pico_sdk_init.cmake)

project(morse-telegraph C CXX ASM)

# Initialize the Pico SDK
pico_sdk_init()

# Add all source files in src/
add_executable(morse-telegraph
    src/main.cpp
    src/morse.cpp
)

# Enable USB output (optional, useful for debugging)
pico_enable_stdio_usb(morse-telegraph 1)
pico_enable_stdio_uart(morse-telegraph 0)

# Link the Pico standard libraries
target_link_libraries(morse-telegraph 
    pico_stdlib 
    hardware_adc
)

# Create UF2 file for flashing
pico_add_extra_outputs(morse-telegraph)
