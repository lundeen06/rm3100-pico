#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

// Using I2C0's alternative pins
const uint SDA_PIN = 0;  // GPIO 0 (Physical pin 1)
const uint SCL_PIN = 1;  // GP1 (Physical pin 2)

// Known RM3100 Registers and Constants
struct RM3100Register {
    uint8_t addr;
    const char* name;
    const char* description;
};

const RM3100Register REGISTERS[] = {
    {0x00, "POLL", "Single Measurement Trigger"},
    {0x01, "CMM", "Continuous Measurement Mode Config"},
    {0x04, "CCX", "Cycle Count X Register"},
    {0x06, "CCY", "Cycle Count Y Register"},
    {0x08, "CCZ", "Cycle Count Z Register"},
    {0x0B, "TMRC", "Continuous Mode Data Rate"},
    {0x24, "MX", "Measurement Results X"},
    {0x27, "MY", "Measurement Results Y"},
    {0x2A, "MZ", "Measurement Results Z"},
    {0x34, "STATUS", "Status Register"},
    {0x36, "REVID", "Hardware Revision ID"},
};

const int NUM_REGISTERS = sizeof(REGISTERS) / sizeof(REGISTERS[0]);

bool read_register(i2c_inst_t *i2c, uint8_t dev_addr, uint8_t reg, uint8_t *data, size_t len = 1) {
    int ret;
    ret = i2c_write_blocking(i2c, dev_addr, &reg, 1, true);
    if (ret < 0) return false;
    ret = i2c_read_blocking(i2c, dev_addr, data, len, false);
    return ret == len;
}

void decode_cmm_register(uint8_t cmm) {
    printf("  START: %s\n", (cmm & 0x01) ? "Enabled" : "Disabled");
    printf("  DRDY Mode: %d\n", (cmm >> 2) & 0x03);
    printf("  X-axis: %s\n", (cmm & 0x10) ? "Enabled" : "Disabled");
    printf("  Y-axis: %s\n", (cmm & 0x20) ? "Enabled" : "Disabled");
    printf("  Z-axis: %s\n", (cmm & 0x40) ? "Enabled" : "Disabled");
}

void decode_tmrc_register(uint8_t tmrc) {
    float rates[] = {600.0, 300.0, 150.0, 75.0, 37.0, 18.0, 9.0, 4.5, 2.3, 1.2, 0.6, 0.3, 0.015, 0.075};
    uint8_t rate_index = tmrc & 0x0F;
    if (rate_index < sizeof(rates)/sizeof(rates[0])) {
        printf("  Update Rate: %.3f Hz\n", rates[rate_index]);
    }
}

void scan_rm3100(i2c_inst_t *i2c, uint8_t addr) {
    uint8_t data[3];
    bool is_rm3100 = false;

    printf("\n=== RM3100 Scanner Results ===\n");
    printf("Found device at address 0x%02X\n\n", addr);
    
    // First verify it's an RM3100
    if (read_register(i2c, addr, 0x36, data) && data[0] == 0x22) {
        is_rm3100 = true;
        printf("Confirmed RM3100 (REVID = 0x%02X)\n\n", data[0]);
    } else {
        printf("Warning: Device doesn't appear to be an RM3100 (REVID != 0x22)\n\n");
    }

    printf("// Generated RM3100 Constants:\n");
    printf("#define I2C_SDA %d\n", SDA_PIN);
    printf("#define I2C_SCL %d\n", SCL_PIN);
    printf("#define RM3100_ADDR 0x%02X  // 7-bit address\n", addr);
    printf("#define RM3100_FULL_ADDR (RM3100_ADDR << 1)  // 8-bit address\n\n");

    printf("// Register Map:\n");
    for (int i = 0; i < NUM_REGISTERS; i++) {
        printf("#define RM3100_REG_%-6s 0x%02X  // %s\n", 
               REGISTERS[i].name, 
               REGISTERS[i].addr, 
               REGISTERS[i].description);
    }
    
    printf("\n// Current Register Values:\n");
    for (int i = 0; i < NUM_REGISTERS; i++) {
        printf("Register 0x%02X (%s): ", REGISTERS[i].addr, REGISTERS[i].name);
        
        if (read_register(i2c, addr, REGISTERS[i].addr, data)) {
            printf("0x%02X", data[0]);
            
            // Special decoding for certain registers
            if (REGISTERS[i].addr == 0x01) {  // CMM
                printf("\nCMM Configuration:\n");
                decode_cmm_register(data[0]);
            }
            else if (REGISTERS[i].addr == 0x0B) {  // TMRC
                printf("\nTMRC Configuration:\n");
                decode_tmrc_register(data[0]);
            }
            else if (REGISTERS[i].addr == 0x34) {  // STATUS
                printf(" (DRDY: %s)", (data[0] & 0x80) ? "Ready" : "Not Ready");
            }
            
            // For cycle count registers, read full 16-bit value
            if (REGISTERS[i].addr == 0x04 || REGISTERS[i].addr == 0x06 || REGISTERS[i].addr == 0x08) {
                if (read_register(i2c, addr, REGISTERS[i].addr, data, 2)) {
                    uint16_t cc = (data[0] << 8) | data[1];
                    printf(" (%d cycles)", cc);
                }
            }
        } else {
            printf("Read Failed");
        }
        printf("\n");
    }
    
    printf("\n// Additional Constants:\n");
    printf("#define RM3100_REVID 0x22\n");
    
    // Scan TMRC options
    printf("\n// Available TMRC (Update Rate) Settings:\n");
    printf("#define RM3100_CMM_RATE_600_0_HZ 0x02\n");
    printf("#define RM3100_CMM_RATE_300_0_HZ 0x03\n");
    printf("#define RM3100_CMM_RATE_150_0_HZ 0x04\n");
    printf("#define RM3100_CMM_RATE_75_0_HZ  0x05\n");
    printf("#define RM3100_CMM_RATE_37_0_HZ  0x06\n");
    printf("#define RM3100_CMM_RATE_18_0_HZ  0x07\n");
    printf("#define RM3100_CMM_RATE_9_0_HZ   0x08\n");
    printf("#define RM3100_CMM_RATE_4_5_HZ   0x09\n");
    printf("#define RM3100_CMM_RATE_2_3_HZ   0x0A\n");
    printf("#define RM3100_CMM_RATE_1_2_HZ   0x0B\n");
    printf("#define RM3100_CMM_RATE_0_6_HZ   0x0C\n");
    printf("#define RM3100_CMM_RATE_0_3_HZ   0x0D\n");
    printf("#define RM3100_CMM_RATE_0_015_HZ 0x0E\n");
    printf("#define RM3100_CMM_RATE_0_075_HZ 0x0F\n");
    printf("#define RM3100_CMM_RATE_MSB      0x90\n");
    
    printf("\n// DRDY Modes:\n");
    printf("#define RM3100_DRDM_ANY_AXES 0x01\n");
    printf("#define RM3100_DRDM_ALL_AXES 0x02\n");
}

int main() {
    stdio_init_all();

    while (!stdio_usb_connected()) {
        sleep_ms(100);
    }
    sleep_ms(1000);
    
    printf("\nEnhanced RM3100 Scanner\n");
    printf("----------------------\n");
    stdio_flush();
    
    // Initialize I2C
    i2c_init(i2c0, 100 * 1000);  // 100kHz
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);
    
    sleep_ms(100);

    // Scan directly for RM3100 at address 0x23
    scan_rm3100(i2c0, 0x23);
    
    printf("\nScanner finished. Copy the constants above for your RM3100 code.\n");
    
    while(true) {
        sleep_ms(1000);
    }

    return 0;
}