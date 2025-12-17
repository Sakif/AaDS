project("bol")

set(BUILD_SHARED_LIBS OFF)
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY "https://github.com/SFML/SFML.git"
    GIT_TAG "3.0.2"
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS # Automatically reconfigure if source files are added/removed.
  ${PROJECT_SOURCE_DIR}/*.cpp)
add_executable(${PROJECT_NAME} ${SRC_FILES})
target_link_libraries(${PROJECT_NAME} PRIVATE SFML::Graphics)

IF (WIN32)
  target_compile_options(${PROJECT_NAME} PUBLIC -Weverything -Wno-c++98-compat -Wpedantic -Werror -m64 -march=native -mtune=native -g0)
ELSE()
  target_compile_options(${PROJECT_NAME} PUBLIC -Wall -Wextra -Wpedantic -Werror -m64 -march=native -mtune=native -g0)
ENDIF()
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)
set_property(TARGET ${PROJECT_NAME} PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
