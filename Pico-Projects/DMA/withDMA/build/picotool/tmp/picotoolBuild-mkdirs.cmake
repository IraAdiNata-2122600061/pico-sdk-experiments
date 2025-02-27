# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/adinata26/Downloads/pico-sdk-experiments/Pico-Projects/DMA/withDMA/build/_deps/picotool-src"
  "/home/adinata26/Downloads/pico-sdk-experiments/Pico-Projects/DMA/withDMA/build/_deps/picotool-build"
  "/home/adinata26/Downloads/pico-sdk-experiments/Pico-Projects/DMA/withDMA/build/_deps"
  "/home/adinata26/Downloads/pico-sdk-experiments/Pico-Projects/DMA/withDMA/build/picotool/tmp"
  "/home/adinata26/Downloads/pico-sdk-experiments/Pico-Projects/DMA/withDMA/build/picotool/src/picotoolBuild-stamp"
  "/home/adinata26/Downloads/pico-sdk-experiments/Pico-Projects/DMA/withDMA/build/picotool/src"
  "/home/adinata26/Downloads/pico-sdk-experiments/Pico-Projects/DMA/withDMA/build/picotool/src/picotoolBuild-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/adinata26/Downloads/pico-sdk-experiments/Pico-Projects/DMA/withDMA/build/picotool/src/picotoolBuild-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/adinata26/Downloads/pico-sdk-experiments/Pico-Projects/DMA/withDMA/build/picotool/src/picotoolBuild-stamp${cfgdir}") # cfgdir has leading slash
endif()
