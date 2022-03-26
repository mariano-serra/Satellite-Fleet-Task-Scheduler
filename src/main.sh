#!/bin/sh
set -o errexit

gnome-terminal -e "bash -c \"../build/Satelite/main/mainSatelite 1; exec bash\""
gnome-terminal -e "bash -c \"../build/Satelite/main/mainSatelite 2; exec bash\""
gnome-terminal -e "bash -c \"./build/GroundControl/main/mainGroundControl; exec bash\""



set +o errexit