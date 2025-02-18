cmake_minimum_required(VERSION 3.13)

# Import SDK
include(pico_sdk_import.cmake)

project(blinky)

# Inisialisasi SDK
pico_sdk_init()

# Tambahkan file sumber
add_executable(blinky blinky.c)

# Link dengan pustaka standar Pico
target_link_libraries(blinky pico_stdlib)

# Hasilkan file .bin/.hex/.uf2
pico_add_extra_outputs(blinky)
