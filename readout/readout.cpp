#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/gpio.h"

// Pin definitions
#define I2C_SDA 0  // GPIO 0 (Pin 1)
#define I2C_SCL 1  // GPIO 1 (Pin 2)
#define LED_PIN 25 // Built-in LED on Pico

#define I2C_PORT i2c0
#define LED_BLINK_COUNT 2
#define LED_BLINK_DURATION 100
#define WAIT_DURATION 2000

// RM3100 Constants
#define RM3100_ADDR (0x20)  // 7-bit base address
#define RM3100_ADDR_SSN 0x01
#define RM3100_FULL_ADDR ((RM3100_ADDR | RM3100_ADDR_SSN) << 1)

// RM3100 Registers
#define RM3100_REG_POLL 0x00
#define RM3100_REG_CMM 0x01
#define RM3100_REG_CCX 0x04
#define RM3100_REG_CCY 0x06
#define RM3100_REG_CCZ 0x08
#define RM3100_REG_TMRC 0x0B
#define RM3100_REG_MX 0x24
#define RM3100_REG_STATUS 0x34
#define RM3100_REG_REVID 0x36

#define RM3100_REVID 0x22
#define RM3100_CMM_RATE_75_0_HZ 0x05
#define RM3100_CMM_RATE_MSB 0x90
#define RM3100_DRDM_ALL_AXES 0x02

bool sensor_connected = false;

// Helper functions for I2C communication
bool i2c_write_reg(uint8_t reg, const uint8_t* data, size_t len) {
    uint8_t buffer[len + 1];
    buffer[0] = reg;
    memcpy(buffer + 1, data, len);
    
    int ret = i2c_write_blocking(I2C_PORT, RM3100_FULL_ADDR, buffer, len + 1, false);
    return ret == len + 1;
}

bool i2c_read_reg(uint8_t reg, uint8_t* data, size_t len) {
    int ret = i2c_write_blocking(I2C_PORT, RM3100_FULL_ADDR, &reg, 1, true);
    if (ret != 1) return false;
    
    ret = i2c_read_blocking(I2C_PORT, RM3100_FULL_ADDR, data, len, false);
    return ret == len;
}

void blink_led() {
    for (int i = 0; i < LED_BLINK_COUNT; i++) {
        gpio_put(LED_PIN, 1);
        sleep_ms(LED_BLINK_DURATION);
        gpio_put(LED_PIN, 0);
        sleep_ms(LED_BLINK_DURATION);
    }
    sleep_ms(WAIT_DURATION);
}

bool init_sensor() {
    // Check hardware revision
    uint8_t rev;
    if (!i2c_read_reg(RM3100_REG_REVID, &rev, 1) || rev != RM3100_REVID) {
        return false;
    }
    
    // Set cycle counts (200 for all axes)
    uint8_t cc_buffer[6] = {0, 200, 0, 200, 0, 200};  // MSB, LSB format
    if (!i2c_write_reg(RM3100_REG_CCX, cc_buffer, 6)) {
        return false;
    }
    
    // Set update rate (75 Hz)
    uint8_t rate = RM3100_CMM_RATE_75_0_HZ | RM3100_CMM_RATE_MSB;
    if (!i2c_write_reg(RM3100_REG_TMRC, &rate, 1)) {
        return false;
    }
    
    // Enable continuous measurement mode
    uint8_t cmm = (1 << 0) | (RM3100_DRDM_ALL_AXES << 2) | (1 << 4) | (1 << 5) | (1 << 6);
    if (!i2c_write_reg(RM3100_REG_CMM, &cmm, 1)) {
        return false;
    }
    
    return true;
}

bool read_sample(float* x, float* y, float* z) {
    uint8_t status;
    if (!i2c_read_reg(RM3100_REG_STATUS, &status, 1)) {
        return false;
    }
    
    if (!(status & 0x80)) {  // Check DRDY bit
        return false;
    }
    
    uint8_t data[9];
    if (!i2c_read_reg(RM3100_REG_MX, data, 9)) {
        return false;
    }
    
    // Convert 24-bit signed values to float
    int32_t raw_x = ((int32_t)data[0] << 16) | ((int32_t)data[1] << 8) | data[2];
    int32_t raw_y = ((int32_t)data[3] << 16) | ((int32_t)data[4] << 8) | data[5];
    int32_t raw_z = ((int32_t)data[6] << 16) | ((int32_t)data[7] << 8) | data[8];
    
    // Sign extend from 24-bit to 32-bit
    if (raw_x & 0x800000) raw_x |= 0xFF000000;
    if (raw_y & 0x800000) raw_y |= 0xFF000000;
    if (raw_z & 0x800000) raw_z |= 0xFF000000;
    
    // Convert to microTesla using scale factor (0.3671 * 200)
    float scale = 73.42f;
    *x = raw_x * scale;
    *y = raw_y * scale;
    *z = raw_z * scale;
    
    return true;
}

int main() {
    // Initialize Pico
    stdio_init_all();
    
    // Initialize LED
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    
    // Initialize I2C
    i2c_init(I2C_PORT, 400000);  // 400 kHz
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);
    
    printf("Initializing RM3100 Magnetometer...\n");
    
    while (true) {
        if (!sensor_connected) {
            printf("Magnetometer not connected!\n");
            blink_led();
            
            if (init_sensor()) {
                printf("RM3100 Magnetometer detected and initialized successfully!\n");
                sensor_connected = true;
                gpio_put(LED_PIN, 0);
            }
        } else {
            float x, y, z;
            if (read_sample(&x, &y, &z)) {
                printf("MAG %llu %.4f %.4f %.4f\n", 
                       time_us_64() / 1000, // Convert to milliseconds
                       x, y, z);
            } else {
                printf("Error: Failed to read sample from RM3100\n");
                sensor_connected = false;
            }
        }
        
        sleep_ms(10);
    }
    
    return 0;
}