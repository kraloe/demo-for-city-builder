cmake_minimum_required(VERSION 3.16)
project(opengl_port LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# If you have GLAD as a single C source file (glad.c), add it to the sources below.
# Alternatively, link with an installed glad target.
set(GLAD_SOURCES
    # ${CMAKE_SOURCE_DIR}/third_party/glad/src/glad.c
)

file(GLOB SRC_FILES
    ${CMAKE_SOURCE_DIR}/src/*.cpp
)

add_executable(opengl_port
    ${SRC_FILES}
    ${GLAD_SOURCES}
)

# If you install glfw via package manager or vcpkg, this should work:
find_package(glfw3 CONFIG QUIET)
if(NOT glfw3_FOUND)
    find_package(glfw3 REQUIRED)
endif()
target_link_libraries(opengl_port PRIVATE glfw)

# GLAD include path (if using the bundled headers). Update as needed.
# target_include_directories(opengl_port PRIVATE ${CMAKE_SOURCE_DIR}/third_party/glad/include)

# stb headers (header-only)
target_include_directories(opengl_port PRIVATE ${CMAKE_SOURCE_DIR}/third_party/stb)

# On macOS, link Cocoa/OpenGL frameworks automatically by glfw. On Linux, link dl, pthread if needed.
if(UNIX AND NOT APPLE)
    target_link_libraries(opengl_port PRIVATE dl pthread)
endif()

# Windows: ensure /MT or /MD consistency with glfw build (handled by your toolchain).
