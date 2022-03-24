README

* Instalcion Build / Boost
	> sudo apt install build-essential libboost-system-dev libboost-thread-dev libboost-program-options-dev
	> sudo apt install libpthread-stubs0-dev (No estoy seguro)


* Instalacion CMake
	> sudo apt install cmake


* Intalacion Gtest/Gmock

	> sudo apt install libgtest-dev
	> sudo apt install google-mock

  Compilacion y link libreria

	> cd /usr/src/gtest
	> sudo cmake CMakeLists.txt
	> sudo make
	> sudo cp *.a /usr/lib
