project("bol")

set(BUILD_SHARED_LIBS OFF)
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY "https://github.com/SFML/SFML.git"
    GIT_TAG "3.0.2"
    GIT_SHALLOW ON EXCLUDE_FROM_ALL SYSTEM)
FetchContent_Declare(FLECS
    GIT_REPOSITORY "https://github.com/SanderMertens/flecs.git"
    GIT_TAG "v4.1.4"
    GIT_SHALLOW ON EXCLUDE_FROM_ALL SYSTEM)
FetchContent_MakeAvailable(SFML FLECS)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    # Automatically reconfigure if source files are added/removed.
    ${PROJECT_SOURCE_DIR}/*.cpp)
add_executable(${PROJECT_NAME} ${SRC_FILES})
target_compile_options(${PROJECT_NAME} PUBLIC -Wall -Wextra -Wpedantic -Werror -m64 -g0
    -march=native -mtune=native)
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS YES
    INTERPROCEDURAL_OPTIMIZATION TRUE)
target_link_libraries(${PROJECT_NAME} PRIVATE SFML::Graphics flecs::flecs_static)
