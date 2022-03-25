#!/bin/sh
set -o errexit

./build/GroundControl/UnitTest/UnitTestGroundControl
./build/Satelite/UnitTest/UnitTestSatelite


set +o errexit