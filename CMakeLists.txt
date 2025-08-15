cmake_minimum_required(VERSION 3.13)

project(my_iot_project C CXX ASM)

include(pico_sdk_import.cmake)

pico_sdk_init()

add_executable(my_iot_project main.cpp)

target_link_libraries(my_iot_project pico_stdlib)

pico_enable_stdio_usb(my_iot_project 1)
pico_enable_stdio_uart(my_iot_project 0)

pico_add_extra_outputs(my_iot_project)
