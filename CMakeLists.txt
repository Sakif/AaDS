cmake_minimum_required(VERSION 3.30 FATAL_ERROR)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
find_program(MOLD_PROGRAM mold)
if(MOLD_PROGRAM)
    set(CMAKE_LINKER_TYPE MOLD)
else()
    message(STATUS "mold not found")
endif()

project(wee)

# include_directories("aads")
add_subdirectory("rl_engine")
add_subdirectory("bol_sfml")
