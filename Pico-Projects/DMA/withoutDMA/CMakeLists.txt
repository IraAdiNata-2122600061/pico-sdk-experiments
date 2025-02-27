cmake_minimum_required(VERSION 3.13)

# Tentukan lokasi SDK Pico
set(PICO_SDK_PATH "/home/adinata26/PICO/pico-sdk")
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(noDMA)

# Inisialisasi SDK
pico_sdk_init()

# Tambahkan file sumber
add_executable(noDMA noDMA.c)

# Link dengan pustaka standar Pico dan hardware multicore
target_link_libraries(noDMA pico_stdlib pico_multicore hardware_dma)

# Hasilkan file .bin/.hex/.uf2
pico_add_extra_outputs(noDMA)
pico_enable_stdio_usb(noDMA 1)  # AKTIFKAN USB Serial
pico_enable_stdio_uart(noDMA 0) # MATIKAN UART (opsional)
