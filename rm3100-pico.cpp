#include <stdio.h>
#include <cstring>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/gpio.h"
#include "pico/binary_info.h"
#include <cmath>

// Pin definitions 
#define I2C_SDA 0  // GPIO 0 (Physical pin 1)
#define I2C_SCL 1  // GPIO 1 (Physical pin 2)
#define LED_PIN 25 // Built-in LED on Pico

#define I2C_PORT i2c0
#define LED_BLINK_COUNT 2
#define LED_BLINK_DURATION 100
#define WAIT_DURATION 2000

// RM3100 Constants - IMPORTANT: Using direct address now
#define RM3100_ADDR 0x23  // Direct address, no shifting needed

// Add binary info for picotool
bi_decl(bi_2pins_with_func(I2C_SDA, I2C_SCL, GPIO_FUNC_I2C));
bi_decl(bi_program_description("RM3100 Magnetometer Reader"));

// Register Map:
#define RM3100_REG_POLL   0x00  // Single Measurement Trigger
#define RM3100_REG_CMM    0x01  // Continuous Measurement Mode Config
#define RM3100_REG_CCX    0x04  // Cycle Count X Register
#define RM3100_REG_CCY    0x06  // Cycle Count Y Register
#define RM3100_REG_CCZ    0x08  // Cycle Count Z Register
#define RM3100_REG_TMRC   0x0B  // Continuous Mode Data Rate
#define RM3100_REG_MX     0x24  // Measurement Results X
#define RM3100_REG_MY     0x27  // Measurement Results Y
#define RM3100_REG_MZ     0x2A  // Measurement Results Z
#define RM3100_REG_STATUS 0x34  // Status Register
#define RM3100_REG_REVID  0x36  // Hardware Revision ID

// Additional Constants:
#define RM3100_REVID 0x22

// TMRC settings 
#define RM3100_CMM_RATE_600_0_HZ 0x02
#define RM3100_CMM_RATE_75_0_HZ  0x05
#define RM3100_CMM_RATE_MSB      0x90

#define RM3100_DRDM_ANY_AXES 0x01
#define RM3100_DRDM_ALL_AXES 0x02

// Reading Rate
#define SAMPLE_DELAY_MS 10  // Delay between readings (10ms = 100Hz output rate)

// Serial monitor settings
#define TIMESTAMP_WIDTH 10   // Fixed width for timestamp in characters

bool sensor_connected = false;

// Helper functions for I2C communication - Note the use of RM3100_ADDR directly
bool i2c_write_reg(uint8_t reg, const uint8_t* data, size_t len) {
    uint8_t buffer[len + 1];
    buffer[0] = reg;
    memcpy(buffer + 1, data, len);
    
    int ret = i2c_write_blocking(I2C_PORT, RM3100_ADDR, buffer, len + 1, false);
    return ret == len + 1;
}

bool i2c_read_reg(uint8_t reg, uint8_t* data, size_t len) {
    int ret = i2c_write_blocking(I2C_PORT, RM3100_ADDR, &reg, 1, true);
    if (ret != 1) return false;
    
    ret = i2c_read_blocking(I2C_PORT, RM3100_ADDR, data, len, false);
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
    if (!i2c_read_reg(RM3100_REG_REVID, &rev, 1)) {
        // printf("Failed to read revision ID\n");
        return false;
    }
    
    // printf("Read revision ID: 0x%02X (expected 0x%02X)\n", rev, RM3100_REVID);
    
    if (rev != RM3100_REVID) {
        // printf("Unexpected revision ID\n");
        return false;
    }
    
    // Set cycle counts (200 for all axes)
    uint8_t cc_buffer[6] = {0, 200, 0, 200, 0, 200};  // MSB, LSB format
    if (!i2c_write_reg(RM3100_REG_CCX, cc_buffer, 6)) {
        // printf("Failed to set cycle counts\n");
        return false;
    }
    
    // Set update rate (75 Hz)
    uint8_t rate = RM3100_CMM_RATE_75_0_HZ | RM3100_CMM_RATE_MSB;
    if (!i2c_write_reg(RM3100_REG_TMRC, &rate, 1)) {
        // printf("Failed to set update rate\n");
        return false;
    }
    
    // Enable continuous measurement mode
    uint8_t cmm = (1 << 0) | (RM3100_DRDM_ALL_AXES << 2) | (1 << 4) | (1 << 5) | (1 << 6);
    if (!i2c_write_reg(RM3100_REG_CMM, &cmm, 1)) {
        // printf("Failed to enable continuous measurement mode\n");
        return false;
    }
    
    return true;
}


bool read_sample(float* x, float* y, float* z, float* magnitude) {
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
    
    // Convert to microTesla
    // With CC=200, gain is 75 LSB/μT (RM3100 datasheet!)
    // CC=100, 38 LSB/μT; CC=50, 20LSB/μT
    // Therefore scale factor is 1/75 = 0.013333... μT/LSB
    const float scale = 1.0f / 75.0f;  // approximately 0.013333... μT/LSB
    *x = raw_x * scale;
    *y = raw_y * scale;
    *z = raw_z * scale;
    
    // Calculate magnitude using Pythagorean theorem
    *magnitude = std::sqrt((*x * *x) + (*y * *y) + (*z * *z));
    
    return true;
}

int main() {
    // Initialize Pico
    stdio_init_all();
    
    // Wait for USB CDC to be ready
    while (!stdio_usb_connected()) {
        sleep_ms(100);
    }
    sleep_ms(1000);
    
    // Print CSV header
    printf("Timestamp(ms),M_x(µT),M_y(µT),M_z(µT),M(µT)\n");
    stdio_flush();
    
    // Initialize LED
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    
    // Initialize I2C with specific pins and slower speed
    i2c_init(I2C_PORT, 100 * 1000);  // 100 kHz
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);
    
    while (true) {
        if (!sensor_connected) {
            if (init_sensor()) {
                sensor_connected = true;
                gpio_put(LED_PIN, 0);
            } else {
                // printf("# Failed to initialize RM3100\n");
                blink_led();
            }
        } else {
            float x, y, z, magnitude;
            if (read_sample(&x, &y, &z, &magnitude)) {
                printf("%llu,%.3f,%.3f,%.3f,%.3f\n", 
                    time_us_64() / 1000,
                    x, y, z, magnitude);
                fflush(stdout);
            } else {
                sensor_connected = false;
            }
        }
        
        sleep_ms(SAMPLE_DELAY_MS);  // Control the update rate
    }
    
    return 0;
}