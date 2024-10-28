cmake_minimum_required(VERSION 3.13)

# Set the SDK path - replace with your actual path to the pico-sdk
set(PICO_SDK_PATH "~/pico-sdk")

# Initialize the SDK
include(pico_sdk_import.cmake)

# Set project name and language
project(rm3100_magnetometer C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize the SDK
pico_sdk_init()

# Create the main executable
add_executable(rm3100_magnetometer
    rm3100-pico.cpp
)

# Enable USB, disable UART
pico_enable_stdio_usb(rm3100_magnetometer 1)
pico_enable_stdio_uart(rm3100_magnetometer 0)

# Add required libraries
target_link_libraries(rm3100_magnetometer 
    pico_stdlib
    hardware_i2c
    pico_multicore  # Add multicore support
)

# Create map/bin/hex file etc.
pico_add_extra_outputs(rm3100_magnetometer)

# Add USB configurations
target_compile_definitions(rm3100_magnetometer PRIVATE
    PICO_DEFAULT_UART_TX_PIN=0
    PICO_DEFAULT_UART_RX_PIN=1
    PICO_USB_VENDOR_ID=0x2E8A
    PICO_USB_PRODUCT_ID=0x000A
    PICO_USB_MANUFACTURER="Pico"
    PICO_USB_PRODUCT="RM3100 Magnetometer"
    # Make sure stdin / stdout / stderr are enabled
    LIB_PICO_STDIO=1
    LIB_PICO_STDIO_USB=1
)