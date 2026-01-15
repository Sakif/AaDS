project("bol"
  VERSION "1"
  DESCRIPTION "A simple roguelike made with SFML 3 and FLECS 4"
  HOMEPAGE_URL ""
  LANGUAGES CXX)

FetchContent_MakeAvailable(SFML FLECS)
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
  # Automatically reconfigure if source files are added/removed.
  ${PROJECT_SOURCE_DIR}/*.cpp)
add_executable(${PROJECT_NAME} ${SRC_FILES})

target_compile_definitions(${PROJECT_NAME} PRIVATE flecs_STATIC=1)
target_compile_options(${PROJECT_NAME} PUBLIC
  -Wall -Wextra -Wpedantic -Werror
  -m64 -g0 -march=x86-64-v3 -mtune=native)
set_target_properties(${PROJECT_NAME} PROPERTIES
  CXX_STANDARD 17 CXX_STANDARD_REQUIRED YES CXX_EXTENSIONS YES
  INTERPROCEDURAL_OPTIMIZATION TRUE)
target_link_libraries(${PROJECT_NAME} PRIVATE
  SFML::Graphics flecs::flecs_static)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_STRIP} --strip-all $<TARGET_FILE:${PROJECT_NAME}>)
