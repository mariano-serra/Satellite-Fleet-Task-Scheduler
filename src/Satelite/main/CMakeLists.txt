cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 14)

file(
    GLOB_RECURSE sources
    ./*.cpp
)

add_executable(main ${sources})

add_dependencies(
    main
    Satelite
    Common
)

target_include_directories(
    main PUBLIC 
    ${CMAKE_SOURCE_DIR}/Common
    ${CMAKE_SOURCE_DIR}/Satelite
)

target_link_libraries(
    main PUBLIC
    Satelite
    Common
)
