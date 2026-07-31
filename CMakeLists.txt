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
FetchContent_Declare(SFML
    GIT_REPOSITORY "https://github.com/SFML/SFML.git"
    GIT_TAG "3.1.0" GIT_SHALLOW ON EXCLUDE_FROM_ALL SYSTEM)
set(SDL_STATIC ON)
set(SDL_SHARED OFF)
FetchContent_Declare(SDL
    GIT_REPOSITORY "https://github.com/libsdl-org/SDL.git"
    GIT_TAG "release-3.4.10" GIT_SHALLOW ON EXCLUDE_FROM_ALL SYSTEM)
set(SDLIMAGE_ANI OFF)
set(SDLIMAGE_AVIF OFF)
set(SDLIMAGE_BMP OFF)
set(SDLIMAGE_GIF OFF)
set(SDLIMAGE_LBM OFF)
set(SDLIMAGE_PCX OFF)
set(SDLIMAGE_PNM OFF)
set(SDLIMAGE_QOI OFF)
set(SDLIMAGE_TGA OFF)
set(SDLIMAGE_TIF OFF)
set(SDLIMAGE_XCF OFF)
set(SDLIMAGE_XPM OFF)
set(SDLIMAGE_XV OFF)
FetchContent_Declare(SDL_IMAGE
    GIT_REPOSITORY "https://github.com/libsdl-org/SDL_image.git"
    GIT_TAG "release-3.4.4" GIT_SHALLOW ON EXCLUDE_FROM_ALL SYSTEM)
FetchContent_Declare(SDL_TTF
    GIT_REPOSITORY "https://github.com/libsdl-org/SDL_ttf.git"
    GIT_TAG "release-3.2.2" GIT_SHALLOW ON EXCLUDE_FROM_ALL SYSTEM)
set(flecs_STATIC ON)
FetchContent_Declare(FLECS
    GIT_REPOSITORY "https://github.com/SanderMertens/flecs.git"
    GIT_TAG "v4.1.5" GIT_SHALLOW ON EXCLUDE_FROM_ALL SYSTEM)
FetchContent_Declare(GODOT_CPP
    GIT_REPOSITORY "https://github.com/godotengine/godot-cpp.git"
    GIT_TAG "10.0.0-rc1" GIT_SHALLOW ON EXCLUDE_FROM_ALL SYSTEM)

project(wee)

# include_directories("aads")
add_subdirectory("bol_nc")
