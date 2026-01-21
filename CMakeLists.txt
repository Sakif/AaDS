cmake_minimum_required(VERSION 3.30 FATAL_ERROR)

set(CMAKE_BUILD_TYPE MinSizeRel)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
find_program(MOLD_PROGRAM mold)
if(MOLD_PROGRAM)
    set(CMAKE_LINKER_TYPE MOLD)
else()
    message(STATUS "mold not found")
endif()

include(FetchContent)
set(SFML_STATIC_LIBRARIES ON)
FetchContent_Declare(SFML GIT_REPOSITORY "https://github.com/SFML/SFML.git" GIT_TAG "3.0.2" GIT_SHALLOW ON EXCLUDE_FROM_ALL SYSTEM)
set(SDL_STATIC ON)
set(SDL_SHARED OFF)
FetchContent_Declare(SDL GIT_REPOSITORY "https://github.com/libsdl-org/SDL.git" GIT_TAG "release-3.4.0" GIT_SHALLOW ON EXCLUDE_FROM_ALL SYSTEM)
set(flecs_STATIC ON)
FetchContent_Declare(FLECS GIT_REPOSITORY "https://github.com/SanderMertens/flecs.git" GIT_TAG "v4.1.4" GIT_SHALLOW ON EXCLUDE_FROM_ALL SYSTEM)

project(wee)

# include_directories("aads")
add_subdirectory("bol_sfml")
