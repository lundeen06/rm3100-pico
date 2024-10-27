#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

// Using I2C0's alternative pins
const uint SDA_PIN = 0;  // GPIO 0 (Physical pin 1)
const uint SCL_PIN = 1;  // GP1 (Physical pin 2)

bool check_device_present(i2c_inst_t *i2c, uint8_t addr) {
    uint8_t rx_data;
    // Return true if device responds with ACK
    return i2c_read_blocking(i2c, addr, &rx_data, 1, false) >= 0;
}

int main() {
    stdio_init_all();

    while (!stdio_usb_connected()) {
        sleep_ms(100);
    }
    sleep_ms(1000);
    
    printf("\n- - - - - - - - - - -\n");
    printf("main.cpp running!...\n");
    printf("- - - - - - - - - - -\n");
    stdio_flush();
    
    // Initialize I2C
    i2c_init(i2c0, 100 * 1000);  // 100kHz
    
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    
    // Enable internal pull-ups for testing
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);
    
    sleep_ms(100);

    printf("\nI2C Scanner starting...\n");
    printf("   0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F\n");
    stdio_flush();

    int devices_found = 0;
    
    // Skip address 0x00 (general call address) and 0x01 (CBUS address)
    for (int addr = 0x08; addr < 0x78; addr++) {
        if (addr % 16 == 0) {
            printf("\n%02x:", addr);
            stdio_flush();
        }

        // Add small delay between checks
        sleep_ms(10);

        if (check_device_present(i2c0, addr)) {
            printf(" %02x", addr);
            devices_found++;
        } else {
            printf(" --");
        }
        stdio_flush();
    }

    printf("\n\nScan finished!\n");
    printf("Found %d device(s)\n", devices_found);
    stdio_flush();

    while(true) {
        sleep_ms(1000);
        printf(".");
        stdio_flush();
    }

    return 0;
}