cmake_minimum_required(VERSION 3.13)

# Tentukan lokasi SDK Pico
set(PICO_SDK_PATH "/home/adinata26/PICO/pico-sdk")
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(scani2c)

# Inisialisasi SDK
pico_sdk_init()

# Tambahkan file sumber
add_executable(scani2c scani2c.c)

# Link dengan pustaka standar Pico dan hardware multicore
target_link_libraries(scani2c pico_stdlib pico_multicore hardware_i2c)

# Hasilkan file .bin/.hex/.uf2
pico_add_extra_outputs(scani2c)
pico_enable_stdio_usb(scani2c 1)  # AKTIFKAN USB Serial
pico_enable_stdio_uart(scani2c 0) # MATIKAN UART (opsional)
