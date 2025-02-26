cmake_minimum_required(VERSION 3.30)

set(CMAKE_C_COMPILER "/usr/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

add_compile_options(-Wall -Wextra -Werror
  -pedantic -pedantic-errors
  -m64 -march=native -mtune=native
  -Os -g0 -fstrict-aliasing)

add_link_options(-flto -fstrict-aliasing -lnotcurses)

project(aads VERSION 0.1.1
    LANGUAGES C CXX)

file(GLOB_RECURSE SRC_FILES
    CONFIGURE_DEPENDS # Automatically reconfigure if source files are added/removed.
    ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_executable(${PROJECT_NAME} ${SRC_FILES})

file(GLOB_RECURSE BOL_FILES
    CONFIGURE_DEPENDS # Automatically reconfigure if source files are added/removed.
    ${PROJECT_SOURCE_DIR}/bol/*.cpp)

add_executable(bol ${BOL_FILES})
target_link_libraries(bol -lncurses)
