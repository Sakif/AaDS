cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_FLAGS "-Ofast -Wall -Wextra -Werror")

project(AADS)

include_directories(header)

add_executable(list listTest.cpp)
add_executable(deque dequeTest.cpp)