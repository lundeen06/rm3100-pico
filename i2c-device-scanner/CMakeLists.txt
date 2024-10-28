cmake_minimum_required(VERSION 3.13)

# Set the SDK path - replace with your actual path to the pico-sdk
set(PICO_SDK_PATH "~/pico-sdk")

# Initialize the SDK
include(pico_sdk_import.cmake)

project(i2c_scanner C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(i2c_scanner
    main.cpp
)

target_link_libraries(i2c_scanner 
    pico_stdlib
    hardware_i2c
)

pico_enable_stdio_usb(i2c_scanner 1)
pico_enable_stdio_uart(i2c_scanner 0)

pico_add_extra_outputs(i2c_scanner)