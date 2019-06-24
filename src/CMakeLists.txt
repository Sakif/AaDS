cmake_minimum_required(VERSION 3.13)

<<<<<<< HEAD
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_FLAGS "-O2 -Wall -Wextra -march=skylake -mtune=skylake")

project(AADS)

include_directories(header)
=======
project(AADS)

>>>>>>> 9b67e840676b8ddf65f4b4d29870720a462a61d5
add_executable(list listTest.cpp)
