#!/bin/sh
set -o errexit

gnome-terminal -e 'bash -c "./build/Satelite/main/mainSatelite 1"'
gnome-terminal -e 'bash -c "./build/Satelite/main/mainSatelite 2"'
gnome-terminal -e 'bash -c "sleep 2;./build/GroundControl/main/mainGroundControl"'

set +o errexit