project(bol_nc)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS # Automatically reconfigure if source files are added/removed.
    ${PROJECT_SOURCE_DIR}/*.cpp)
add_executable(${PROJECT_NAME} ${SRC_FILES})

target_compile_options(${PROJECT_NAME} PUBLIC
  -Wall -Wextra -Wpedantic -Werror -m64 -g0 -march=native -mtune=generic)
set_target_properties(${PROJECT_NAME} PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED YES
  CXX_EXTENSIONS YES
  INTERPROCEDURAL_OPTIMIZATION TRUE)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND
  ${CMAKE_STRIP} --strip-all $<TARGET_FILE:${PROJECT_NAME}>)
