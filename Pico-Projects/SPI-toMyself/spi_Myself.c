#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "hardware/spi.h"

// Pin definitions for Master
#define MASTER_SPI    spi0
#define SPI_BAUDRATE  50000  // 50 kHz
#define SPI_CS        1      // CS pin (GP1)
#define SPI_CLK       2      // Clock pin (GP2)
#define SPI_MISO      0      // MISO pin (GP0)
#define SPI_MOSI      3      // MOSI pin (GP3)

// Pin definitions for Slave
#define SLAVE_SPI     spi1
#define SLAVE_CS      9      // CS pin (GP9)
#define SLAVE_CLK     10     // Clock pin (GP10)
#define SLAVE_MISO    11     // MISO pin (GP11)
#define SLAVE_MOSI    8      // MOSI pin (GP8)

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
    uint8_t data_to_send = 241;  // Data yang dikirim oleh Slave

    while (1) {
        if (!gpio_get(SLAVE_CS)) {  // CS aktif (low)
            spi_write_read_blocking(SLAVE_SPI, &data_to_send, &received_data, 1); // Full duplex 8 byte
            printf("Slave received: ");
            // for (int i = 0; i < 8; i++) {
            //     printf("%d ", received_data[i]);
            // }
            printf("\n");
        }
    }
}

int main() {
    // Initialize UART for debugging
    stdio_init_all();
    const uint LED_PIN = 25;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    // Launch core 1 for SPI slave functionality
    multicore_launch_core1(core1_entry);

    // Initialize SPI Master
    spi_init(MASTER_SPI, SPI_BAUDRATE);
    gpio_set_function(SPI_CLK, GPIO_FUNC_SPI);
    gpio_set_function(SPI_MISO, GPIO_FUNC_SPI);
    gpio_set_function(SPI_MOSI, GPIO_FUNC_SPI);
    gpio_set_function(SPI_CS, GPIO_FUNC_SPI);

    // Set the CS pin to be active low
    gpio_init(SPI_CS);
    gpio_set_dir(SPI_CS, GPIO_OUT);
    gpio_put(SPI_CS, 1);  // CS = 1 (inactive)

    uint8_t data_to_send = 17;
    uint8_t received_data;

    while (1) {
        gpio_put(SPI_CS, 0);  // CS = 0 (active)
        
        spi_write_read_blocking(MASTER_SPI, &data_to_send, &received_data, 1); // Full duplex 8 byte

        gpio_put(SPI_CS, 1);  // CS = 1 (inactive)

        printf("Master Sent: ");
        // for (int i = 0; i < 8; i++) {
        //     printf("%d ", data_to_send[i]);
        // }
        // printf("\nMaster Received: ");
        // for (int i = 0; i < 8; i++) {
        //     printf("%d ", received_data[i]);
        // }
        printf("\n");

        if (received_data == 241) {
            gpio_put(LED_PIN, 1);
        } else {
            gpio_put(LED_PIN, 0);
        }

        sleep_ms(500);  // Delay agar output lebih mudah dibaca
    }

    return 0;
}
