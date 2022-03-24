cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 14)

file(
    GLOB_RECURSE sources
    ./*.cpp
)

add_library(GroundControl ${sources})

target_include_directories(
    GroundControl PUBLIC 
    .
    ../Common
    ../Satelite
)