#include "pico/stdlib.h"
#include "pico/multicore.h"

// Pin LED di Raspberry Pi Pico (GP25)
#define LED_PIN 25

// Fungsi yang dijalankan di core 1 (Blinky)
void core1_entry() {
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    while (true) {
        // LED berkedip setiap 500 ms
        gpio_put(LED_PIN, true);
        sleep_ms(500);
        gpio_put(LED_PIN, false);
        sleep_ms(500);
    }
}

// Fungsi utama yang dijalankan di core 0 (Print Hello World)
int main() {
    stdio_init_all();  // Inisialisasi standar input/output untuk serial

    // Mulai core 1 dengan fungsi core1_entry()
    multicore_launch_core1(core1_entry);

    while (true) {
        // Mencetak "Hello, World!" di core 0
        printf("Hello, World!\n");
        sleep_ms(1000);  // Tunggu 1 detik
    }
}
