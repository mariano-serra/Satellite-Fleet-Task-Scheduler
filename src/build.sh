#!/bin/sh
set -o errexit

rm -rf build
mkdir build
cd build
cmake ../.
cmake --build .  --target main
cmake --build .  --target UnitTest
./main/main

set +o errexit