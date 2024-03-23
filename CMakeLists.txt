cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(Main VERSION 0.1.0 LANGUAGES C CXX)

add_library(LongNum STATIC includes/LongNum.h scr/LongNum.cpp)

add_executable(Main main.cpp)
target_link_libraries(Main LongNum)

add_executable(Test test/test.cpp)
target_link_libraries(Test LongNum gtest_main)

enable_testing()
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

#include(GoogleTest)
#gtest_discover_tests(tests)