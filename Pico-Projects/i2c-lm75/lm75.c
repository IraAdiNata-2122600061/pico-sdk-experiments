#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#define I2C_PORT i2c0
#define SDA_PIN 16
#define SCL_PIN 17
#define LM75_ADDR 0x48

float read_temperature() {
    uint8_t reg = 0x00;
    uint8_t buffer[2];


    if (i2c_write_blocking(I2C_PORT, LM75_ADDR, &reg, 1, true) < 0) {
        printf("Gagal menulis ke sensor!\n");
        return -999;
    }

    
    if (i2c_read_blocking(I2C_PORT, LM75_ADDR, buffer, 2, false) < 0) {
        printf("Gagal membaca dari sensor!\n");
        return -999;
    }

    int16_t raw_temp = (buffer[0] << 8) | buffer[1];
    raw_temp >>= 5;
    
    if (raw_temp & (1 << 10)) {
        raw_temp -= (1 << 11);
    }

    return raw_temp * 0.125;
}


int main() {
    stdio_init_all();
    i2c_init(I2C_PORT, 100000);
    
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);

    printf("LM75 Temperature Sensor Readings:\n");

    while (1) {
        float temperature = read_temperature();
        printf("Temperature: %.2f C\n", temperature);
        sleep_ms(1000);
    }

    return 0;
}
