cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 14)

enable_testing()
find_package(GTest REQUIRED)
# find_package(GMock REQUIRED)
find_package(Threads REQUIRED)

file(
    GLOB_RECURSE sources
    ../../Common/*test.cpp
    ../../Satelite/*test.cpp
    ../../Satelite/Satelite.cpp
    ./*.cpp
)

add_executable(UnitTestSatelite ${sources})

target_compile_definitions(UnitTestSatelite PUBLIC UNIT_TESTS)

add_dependencies(
    UnitTestSatelite
    Satelite
    Common
)

target_include_directories(
    UnitTestSatelite PUBLIC 
    ${GTEST_INCLUDE_DIRS}
    ${GMOCK_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/Satelite
    ${CMAKE_SOURCE_DIR}/Common
)

target_link_libraries(
    UnitTestSatelite PUBLIC
    gtest
    gmock
    pthread
    ${GTEST_BOTH_LIBRARIES}
    ${GMOCK_BOTH_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
    Satelite
    Common
)

add_test(AllTestsInUnitTest UnitTestSatelite)