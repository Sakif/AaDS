project("bol")

set(BUILD_SHARED_LIBS OFF)

# add_directory("../rl_engine")

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS # Automatically reconfigure if source files are added/removed.
  ${PROJECT_SOURCE_DIR}/*.cpp)
add_executable(${PROJECT_NAME} ${SRC_FILES})
target_compile_options(${PROJECT_NAME} PUBLIC -Wall -Wextra -Wpedantic -Werror -m64 -march=native -mtune=native -Oz -g0)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
set_property(TARGET ${PROJECT_NAME} PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
target_link_libraries(${PROJECT_NAME} "RL_Engine")
