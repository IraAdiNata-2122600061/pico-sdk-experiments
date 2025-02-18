#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "hardware/spi.h"

// Pin definitions for Slave
#define SLAVE_SPI     spi1
#define SPI_BAUDRATE  50000  // 500 kHz
#define SLAVE_CS      9       // CS pin (GP9)
#define SLAVE_CLK     10      // Clock pin (GP10)
#define SLAVE_MISO    11      // MISO pin (GP11)
#define SLAVE_MOSI    8       // MOSI pin (GP8)

void core1_entry() {
    // Initialize SPI Slave
    spi_init(SLAVE_SPI, SPI_BAUDRATE);
    gpio_set_function(SLAVE_CLK, GPIO_FUNC_SPI);
    gpio_set_function(SLAVE_MISO, GPIO_FUNC_SPI);
    gpio_set_function(SLAVE_MOSI, GPIO_FUNC_SPI);
    gpio_set_function(SLAVE_CS, GPIO_FUNC_SPI);

    // Set CS pin as input (active low for SPI slave)
    gpio_init(SLAVE_CS);
    gpio_set_dir(SLAVE_CS, GPIO_IN);

    uint8_t received_data;
    uint8_t data_to_send = 20;  // Slave will send 20

    // Continuous loop for receiving and sending data
    while (1) {
        if (!gpio_get(SLAVE_CS)) {  // Check if CS is active (low)
            // Data is being transmitted
            spi_read_blocking(SLAVE_SPI, 0, &received_data, 1);  // Read 1 byte from Master

            // After receiving, send the response (20)
            spi_write_blocking(SLAVE_SPI, &data_to_send, 1);  // Send 1 byte to Master

            printf("Received data: %d, Sent data: %d\n", received_data, data_to_send);
        }
    }
}

int main() {
    // Initialize UART for debugging
    stdio_init_all();

    // Launch core 1 for SPI slave functionality
    multicore_launch_core1(core1_entry);

   const uint LED_PIN = 25;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    while (true) {
        // LED menyala
        gpio_put(LED_PIN, 1);
        sleep_ms(500); // Delay 500ms

        // LED mati
        gpio_put(LED_PIN, 0);
        sleep_ms(500); // Delay 500ms
    }
}

