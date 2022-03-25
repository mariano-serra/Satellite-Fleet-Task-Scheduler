#!/bin/sh
set -o errexit

rm -rf build
mkdir build
cd build
cmake ../.
cmake --build .  --target mainSatelite
cmake --build .  --target UnitTestSatelite
cmake --build .  --target mainGroundControl
cmake --build .  --target UnitTestGroundControl
./main/main

set +o errexit