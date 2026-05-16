#!/bin/sh
set -e 
cd ~/dev/scads/flight_software || exit 1
rm -rf build
cmake -B build -DCMAKE_TOOLCHAIN_FILE=cmake/arm-none-eabi.cmake
cmake --build build
