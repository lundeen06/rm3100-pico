cmake_minimum_required(VERSION 3.13)

# Include the Pico SDK cmake build system
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# Set project name and configuration
project(rm3100_magnetometer C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize the Pico SDK
pico_sdk_init()

# Create the main executable
add_executable(rm3100_magnetometer
    rm3100-pico.cpp
)

# Enable USB output, disable UART output
pico_enable_stdio_usb(rm3100_magnetometer 1)
pico_enable_stdio_usb(rm3100_magnetometer 0)

# Add required libraries
target_link_libraries(rm3100_magnetometer 
    pico_stdlib
    hardware_i2c
)

# Create additional targets to generate UF2 file and enable debugging
pico_add_extra_outputs(rm3100_magnetometer)

# Set some build information
target_compile_definitions(rm3100_magnetometer PRIVATE
    PICO_DEFAULT_UART_TX_PIN=0
    PICO_DEFAULT_UART_RX_PIN=1
)