cmake_minimum_required(VERSION 3.13)

# Tentukan lokasi SDK Pico
set(PICO_SDK_PATH "/home/adinata26/PICO/pico-sdk")
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(pwm_spi_slave)

# Inisialisasi SDK
pico_sdk_init()

# Tambahkan file sumber
add_executable(pwm_spi_slave pwm_spi_slave.c)

# Link dengan pustaka standar Pico dan hardware multicore
target_link_libraries(pwm_spi_slave pico_stdlib pico_multicore hardware_spi hardware_pwm)

# Hasilkan file .bin/.hex/.uf2
pico_add_extra_outputs(pwm_spi_slave)
