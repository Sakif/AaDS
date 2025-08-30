cmake_minimum_required(VERSION 3.30 FATAL_ERROR)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-Wall -Wextra -Wpedantic -Werror
  -m64 -march=native -mtune=native -O2 -g0)
add_link_options(-flto -fuse-ld=mold)

project(aads VERSION 0.1.1 LANGUAGES C CXX)

file(GLOB_RECURSE SRC_FILES
    CONFIGURE_DEPENDS # Automatically reconfigure if source files are added/removed.
    ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_executable(${PROJECT_NAME} ${SRC_FILES})

file(GLOB_RECURSE BOL_FILES
    CONFIGURE_DEPENDS # Automatically reconfigure if source files are added/removed.
    ${PROJECT_SOURCE_DIR}/bol/*.cpp)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(bol ${BOL_FILES})
target_link_libraries(bol ${CURSES_LIBRARIES})
