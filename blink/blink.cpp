#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

int main() {
    stdio_init_all();    // Initialize stdio
    sleep_ms(2000);    // Give serial time to initialize
    
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    while (true) {
        printf("\n led on \n");
        gpio_put(LED_PIN, 1);
        sleep_ms(500);
        printf("\n led off \n");
        gpio_put(LED_PIN, 0);
        sleep_ms(500);
    }
}