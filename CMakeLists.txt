cmake_minimum_required(VERSION 3.16)
project(complex_analysis VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(complex_analysis src/complex.cpp)
target_include_directories(complex_analysis PUBLIC include)

if (MSVC)
    target_compile_options(complex_analysis PRIVATE /W4 /WX)
else()
    target_compile_options(complex_analysis PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_executable(complex_demo examples/main.cpp)
target_link_libraries(complex_demo PRIVATE complex_analysis)

enable_testing()
add_executable(complex_tests tests/complex_tests.cpp)
target_link_libraries(complex_tests PRIVATE complex_analysis)
add_test(NAME complex_tests COMMAND complex_tests)
