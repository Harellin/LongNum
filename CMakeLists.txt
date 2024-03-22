cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(LongNum VERSION 0.1.0 LANGUAGES C CXX)

include_directories("includes/")


add_library(LongNum INTERFACE scr/LongNum.cpp scr/PiCalc.cpp includes/LongNum.h)

add_executable(main main.cpp)
target_link_libraries(main LongNum)
target_include_directories(main PUBLIC "includes" "scr")
enable_testing()

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(tests test/test.cpp)
target_link_libraries(tests LongNum GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(tests)