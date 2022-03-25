cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 14)

file(
    GLOB_RECURSE sources
    ./*.cpp
)

add_executable(mainSatelite ${sources})

add_dependencies(
    mainSatelite
    Satelite
    Common
)

target_include_directories(
    mainSatelite PUBLIC 
    ${CMAKE_SOURCE_DIR}/Common
    ${CMAKE_SOURCE_DIR}/Satelite
)

target_link_libraries(
    mainSatelite PUBLIC
    Satelite
    Common
)
