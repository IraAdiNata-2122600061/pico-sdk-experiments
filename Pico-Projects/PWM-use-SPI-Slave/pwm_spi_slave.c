#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "hardware/spi.h"
#include "hardware/pwm.h"

// Pin definitions for SPI Slave
#define SLAVE_SPI     spi1
#define SPI_BAUDRATE  50000  // 50 kHz
#define SLAVE_CS      9       // CS pin (GP9)
#define SLAVE_CLK     10      // Clock pin (GP10)
#define SLAVE_MISO    11      // MISO pin (GP11)
#define SLAVE_MOSI    8       // MOSI pin (GP8)

// LED PWM pin
#define LED_PIN 25  

volatile uint8_t received_data = 0;

// Konfigurasi PWM untuk LED
void setup_pwm(uint gpio) {
    gpio_set_function(gpio, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(gpio);

    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, 4.0); // Prescaler untuk frekuensi PWM
    pwm_config_set_wrap(&config, 255);  // Maksimum nilai duty cycle (0-255)
    
    pwm_init(slice_num, &config, true); // Inisialisasi PWM
    pwm_set_gpio_level(gpio, 0);        // Mulai dengan LED mati
}

// Fungsi SPI Slave di Core1
void core1_entry() {
    stdio_init_all(); // Inisialisasi printf untuk debugging

    spi_init(SLAVE_SPI, SPI_BAUDRATE);
    gpio_set_function(SLAVE_MISO, GPIO_FUNC_SPI);
    gpio_set_function(SLAVE_MOSI, GPIO_FUNC_SPI);
    
    gpio_init(SLAVE_CLK);
    gpio_set_dir(SLAVE_CLK, GPIO_IN);
    
    gpio_init(SLAVE_CS);
    gpio_set_dir(SLAVE_CS, GPIO_IN);

    uint8_t data_to_send = 0xAA;  

    while (1) {
        if (!gpio_get(SLAVE_CS)) {  
            spi_write_read_blocking(SLAVE_SPI, &data_to_send, (uint8_t*)&received_data, 1); 
            
            printf("Received data: %d\n", received_data);
        }
    }
}

int main() {
    stdio_init_all();
    multicore_launch_core1(core1_entry);

    setup_pwm(LED_PIN); // Inisialisasi PWM untuk LED

    while (true) {
        pwm_set_gpio_level(LED_PIN, received_data); // Atur kecerahan LED sesuai data SPI
    }
}
