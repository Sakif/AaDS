cmake_minimum_required (VERSION 3.25)

set(CMAKE_C_COMPILER "/usr/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

add_compile_options(-Wall -Wextra -Werror
  -pedantic -pedantic-errors
  -m64 -march=native -mtune=native
  -Os -g0 -flto -fstrict-aliasing)

add_link_options(# -static -SDL2
  -flto -fstrict-aliasing)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_C_EXTENSIONS ON)

project(wee VERSION 0.1
    LANGUAGES C CXX)

file(GLOB_RECURSE SOURCE_FILES
    CONFIGURE_DEPENDS # Automatically reconfigure if source files are added/removed.
    ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
