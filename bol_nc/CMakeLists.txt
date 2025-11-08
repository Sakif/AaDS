project(bol_nc)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS # Automatically reconfigure if source files are added/removed.
    ${PROJECT_SOURCE_DIR}/*.cpp)
add_executable(${PROJECT_NAME} ${SRC_FILES})