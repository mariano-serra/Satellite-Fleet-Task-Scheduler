README

* Os: Ubuntu 20.04
* Gcc -- version: 9.4.0

* Instalcion Build / Boost
```shell
sudo apt install build-essential libboost-system-dev libboost-thread-dev libboost-program-options-dev
sudo apt install libpthread-stubs0-dev
```

* Instalacion CMake
```shell
sudo apt install cmake
```

* Intalacion Gtest
```shell
sudo apt install libgtest-dev
cd /usr/src/gtest
sudo cmake CMakeLists.txt
sudo make
sudo cp lib/*.a /usr/lib/
sudo cp -r include/* /usr/include/
```

* Intalacion GMock
```shell
sudo apt install google-mock
cd /usr/src/gmock
sudo cmake CMakeLists.txt
sudo make
sudo cp lib/*.a /usr/lib/
sudo cp -r include/* /usr/include/
```

* Build:
```shell
chmod +x ./build.sh
./build.sh 2> build.log
```

* UnitTest (Gtest / GMock):
```shell
chmod +x ./unitTest.sh
./unitTest.sh
```

* Run (GrounControl / Satelite1 / Satelite 2):
```shell
chmod +x ./main.sh
./main.sh
```