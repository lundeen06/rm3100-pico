cmake_minimum_required(VERSION 3.13)

# Set the SDK path - replace with your actual path to the pico-sdk
set(PICO_SDK_PATH "~/pico-sdk")

# Initialize the SDK
include(pico_sdk_import.cmake)

# Set the project name and language
project(blink_test C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# Add your executable
add_executable(blink_test
    blink.cpp
)

# Add the required libraries
target_link_libraries(blink_test
    pico_stdlib
)

# Enable USB output, disable UART output
pico_enable_stdio_usb(blink_test 1)
pico_enable_stdio_uart(blink_test 0)  # Fixed this line

# Create map/bin/hex/uf2 files
pico_add_extra_outputs(blink_test)