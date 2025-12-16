cmake_minimum_required(VERSION 3.30 FATAL_ERROR)

set(CMAKE_BUILD_TYPE MinSizeRel)
set(CMAKE_CXX_COMPILER "C:\\Program Files\\Microsoft Visual Studio\\2022\\Professional\\VC\\Tools\\Llvm\\x64\\bin\\clang.exe")
set(CMAKE_C_COMPILER "C:\\Program Files\\Microsoft Visual Studio\\2022\\Professional\\VC\\Tools\\Llvm\\x64\\bin\\clang.exe")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
find_program(MOLD_PROGRAM mold)
if(MOLD_PROGRAM)
    set(CMAKE_LINKER_TYPE MOLD)
else()
    message(STATUS "mold not found")
endif()

project(wee)

# include_directories("aads")
add_subdirectory("bol_sfml")
