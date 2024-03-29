cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 14)

enable_testing()
find_package(GTest REQUIRED)
# find_package(GMock REQUIRED)
find_package(Threads REQUIRED)

file(
    GLOB_RECURSE sources
    ../../Common/*test.cpp
    ../../GroundControl/*test.cpp
    ../../GroundControl/GroundControl.cpp
    ./*.cpp
)

add_executable(UnitTestGroundControl ${sources})

target_compile_definitions(UnitTestGroundControl PUBLIC UNIT_TESTS)

add_dependencies(
    UnitTestGroundControl
    GroundControl
    Common
)

target_include_directories(
    UnitTestGroundControl PUBLIC 
    ${GTEST_INCLUDE_DIRS}
    ${GMOCK_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/GroundControl
    ${CMAKE_SOURCE_DIR}/Common
)

target_link_libraries(
    UnitTestGroundControl PUBLIC
    gtest
    gmock
    pthread
    ${GTEST_BOTH_LIBRARIES}
    ${GMOCK_BOTH_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
    GroundControl
    Common
)

add_test(AllTestsInUnitTest UnitTestGroundControl)