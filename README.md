README

* Os: Ubuntu 20.04
* Gcc -- version: 9.4.0

* Instalcion Build / Boost
	> sudo apt install build-essential libboost-system-dev libboost-thread-dev libboost-program-options-dev
	> sudo apt install libpthread-stubs0-dev (No estoy seguro)


* Instalacion CMake
	> sudo apt install cmake


* Intalacion Gtest
	> sudo apt install libgtest-dev
	> cd /usr/src/gtest
	> sudo cmake CMakeLists.txt
	> sudo make
	> sudo cp lib/*.a /usr/lib/
	> sudo cp -r include/* /usr/include/


* Compilacion y link libreria
	> sudo apt install google-mock
	> cd /usr/src/gmock
	> sudo cmake CMakeLists.txt
	> sudo make
	> sudo cp lib/*.a /usr/lib/
	> sudo cp -r include/* /usr/include/

* Build:
	> chmod +x ./build.sh
	> ./build.sh 2> build.log

* UnitTest (Gtest / GMock):
	> chmod +x ./unitTest.sh
	> ./unitTest.sh

* Run (GrounControl / Satelite1 / Satelite 2):
	> chmod +x ./main.sh
	> ./main.sh
