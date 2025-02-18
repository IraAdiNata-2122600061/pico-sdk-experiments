#include "pico/stdlib.h"

int main() {
    // Inisialisasi GPIO pin untuk LED (pin 25 adalah pin onboard LED pada Pico)
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
