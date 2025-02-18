cmake_minimum_required(VERSION 3.13)

# Import SDK
include(pico_sdk_import.cmake)

project(hello_world)

# Inisialisasi SDK
pico_sdk_init()

# Tambahkan file sumber
add_executable(hello_world hello_world.c)

# Link dengan pustaka standar Pico
target_link_libraries(hello_world pico_stdlib)

# Hasilkan file .bin/.hex/.uf2
pico_add_extra_outputs(hello_world)
