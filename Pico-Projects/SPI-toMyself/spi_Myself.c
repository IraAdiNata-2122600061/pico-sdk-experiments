#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "hardware/spi.h"

// Pin definitions for Master
#define MASTER_SPI    spi0
#define SPI_BAUDRATE  50000  // 500 kHz
#define SPI_CS        1       // CS pin (GP1)
#define SPI_CLK       2       // Clock pin (GP2)
#define SPI_MISO      0       // MISO pin (GP0)
#define SPI_MOSI      3       // MOSI pin (GP3)

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

    // Initialize SPI Master
    spi_init(MASTER_SPI, SPI_BAUDRATE);
    gpio_set_function(SPI_CLK, GPIO_FUNC_SPI);
    gpio_set_function(SPI_MISO, GPIO_FUNC_SPI);
    gpio_set_function(SPI_MOSI, GPIO_FUNC_SPI);
    gpio_set_function(SPI_CS, GPIO_FUNC_SPI);

    // Set the CS pin to be active low
    gpio_put(SPI_CS, 1);  // CS = 1 (inactive)

    uint8_t data_to_send = 10;
    uint8_t received_data;

    // Continuous loop for sending and receiving data
    while (1) {
        gpio_put(SPI_CS, 0);  // CS = 0 (active)
        spi_write_blocking(MASTER_SPI, &data_to_send, 1);  // Write 1 byte
        spi_read_blocking(MASTER_SPI, 0, &received_data, 1);  // Read 1 byte
        gpio_put(SPI_CS, 1);  // CS = 1 (inactive)

        printf("Sent data: %d, Received data: %d\n", data_to_send, received_data);

        // Update data to send for next iteration (for example, incrementing)
        // data_to_send++;

        sleep_ms(100);  // Sleep to avoid flooding the terminal with data
    }

    return 0;
}

