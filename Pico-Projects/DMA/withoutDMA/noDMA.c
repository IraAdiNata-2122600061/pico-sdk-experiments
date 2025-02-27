#include "pico/stdlib.h"
#include <stdio.h>

#define BUFFER_SIZE 1024

uint8_t src[BUFFER_SIZE];
uint8_t dst[BUFFER_SIZE];

int main() {
    stdio_init_all();
    
    // Isi buffer dengan data
    for (int i = 0; i < BUFFER_SIZE; i++) {
        src[i] = i % 256;
    }

    uint64_t start_time = time_us_64(); // Catat waktu mulai

    // Copy data menggunakan CPU
    for (int i = 0; i < BUFFER_SIZE; i++) {
        dst[i] = src[i];
    }

    uint64_t end_time = time_us_64(); // Catat waktu selesai


    while(1){
        printf("Waktu eksekusi tanpa DMA: %llu us\n", end_time - start_time);
        sleep_ms(1000);
    }
}
