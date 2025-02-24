cmake_minimum_required(VERSION 3.13)

# Tentukan lokasi SDK Pico
set(PICO_SDK_PATH "/home/adinata26/PICO/pico-sdk")
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(lm75)

# Inisialisasi SDK
pico_sdk_init()

# Tambahkan file sumber
add_executable(lm75 lm75.c)

# Link dengan pustaka standar Pico dan hardware multicore
target_link_libraries(lm75 pico_stdlib pico_multicore hardware_i2c)

# Hasilkan file .bin/.hex/.uf2
pico_add_extra_outputs(lm75)
pico_enable_stdio_usb(lm75 1)  # AKTIFKAN USB Serial
pico_enable_stdio_uart(lm75 0) # MATIKAN UART (opsional)
