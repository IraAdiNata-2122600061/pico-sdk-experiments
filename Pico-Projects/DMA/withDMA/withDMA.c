#include "pico/stdlib.h"
#include "hardware/dma.h"
#include <stdio.h>

#define BUFFER_SIZE 1024

uint8_t src[BUFFER_SIZE];
uint8_t dst[BUFFER_SIZE];

int main() {
    stdio_init_all();

    for (int i = 0; i < BUFFER_SIZE; i++) {
        src[i] = i % 256;
    }

    int dma_chan = dma_claim_unused_channel(true);
    dma_channel_config c = dma_channel_get_default_config(dma_chan);
    channel_config_set_transfer_data_size(&c, DMA_SIZE_8);
    channel_config_set_read_increment(&c, true);
    channel_config_set_write_increment(&c, true);
    channel_config_set_dreq(&c, DREQ_FORCE); // Perbaikan: Gunakan DREQ_FORCE

    dma_channel_configure(dma_chan, &c,
        dst,    
        src,    
        BUFFER_SIZE,  
        false  // Jangan mulai dulu
    );

    uint64_t start_time = time_us_64();  // Catat waktu sebelum transfer

    dma_start_channel_mask(1u << dma_chan); // Mulai transfer

    while (dma_channel_is_busy(dma_chan));  // Tunggu selesai

    uint64_t end_time = time_us_64();  // Catat waktu setelah selesai

    dma_channel_unclaim(dma_chan);  // Bebaskan channel

    while(1){
        printf("Waktu eksekusi dengan DMA (optimized): %llu us\n", end_time - start_time);
        sleep_ms(1000);
    }
}
