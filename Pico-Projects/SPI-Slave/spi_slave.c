#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "hardware/spi.h"

// Pin definitions for Slave
#define SLAVE_SPI     spi1
#define SPI_BAUDRATE  50000  // 50 kHz
#define SLAVE_CS      9       // CS pin (GP9)
#define SLAVE_CLK     10      // Clock pin (GP10)
#define SLAVE_MISO    11      // MISO pin (GP11)
#define SLAVE_MOSI    8       // MOSI pin (GP8)

volatile uint8_t received_data = 0;

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
            
            printf("Received data: %d, Sent data: %d\n", received_data, data_to_send);
        }
    }
}

int main() {
    stdio_init_all();

    multicore_launch_core1(core1_entry);

    const uint LED_PIN = 25;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    while (true) {
        if (received_data == 0xAA) {
            gpio_put(LED_PIN, 1);
            // sleep_ms(500);
            // gpio_put(LED_PIN, 0);
            // sleep_ms(500);
        }else{
            gpio_put(LED_PIN, 0);
        }
    }
}
