cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra -march=skylake -mtune=skylake")

project(AADS)

include_directories(header)

project(AADS)

add_executable(list listTest.cpp)
add_executable(uni unicode.cpp)
