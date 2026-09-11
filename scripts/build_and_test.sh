#!/bin/sh

echo "building the flight logic unit tests and running them"
echo "pass argument 1 to skip the build and just run test"

set -e 
cd ~/dev/scads/flight_software || exit 1
if [[ $1 -ne 1 ]]; then
    rm -rf build_flight_logic_tests
    cmake -B build_flight_logic_tests -DBUILD_TESTS=ON
    cmake --build build_flight_logic_tests
fi
cd build_flight_logic_tests && ctest
