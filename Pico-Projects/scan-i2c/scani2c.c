#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#define I2C_PORT i2c0
#define SDA_PIN 16
#define SCL_PIN 17

void scan_i2c() {
    printf("Scanning I2C Bus...\n");

    for (uint8_t addr = 0x03; addr <= 0x77; addr++) {
        uint8_t dummy = 0;
        int res = i2c_write_blocking(I2C_PORT, addr, &dummy, 1, true);

        if (res >= 0) {
            printf("Device found at 0x%02X\n", addr);
        }
    }
    printf("Scan Complete.\n");
}

int main() {
    stdio_init_all();
    i2c_init(I2C_PORT, 100 * 1000);
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);

    sleep_ms(3000);  // Tunggu agar serial siap

    while (1) {
    scan_i2c();
        sleep_ms(5000);
    }
}
