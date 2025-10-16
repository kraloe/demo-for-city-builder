cmake_minimum_required(VERSION 3.16)
project(opengl_port LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# ------------------------------------------------------------------------------
# GLFW 자동 다운로드 (third_party/glfw 경로로)
# ------------------------------------------------------------------------------
set(GLFW_VERSION 3.3.9)
set(GLFW_SOURCE_DIR ${CMAKE_SOURCE_DIR}/third_party/glfw)

if(NOT EXISTS "${GLFW_SOURCE_DIR}/CMakeLists.txt")
    message(STATUS "GLFW not found in third_party — fetching from GitHub...")
    FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG ${GLFW_VERSION}
        SOURCE_DIR ${GLFW_SOURCE_DIR}
    )
    FetchContent_MakeAvailable(glfw)
else()
    add_subdirectory(${GLFW_SOURCE_DIR})
endif()

# ------------------------------------------------------------------------------
# GLAD (필요하면 주석 해제)
# ------------------------------------------------------------------------------
set(GLAD_SOURCES
    # ${CMAKE_SOURCE_DIR}/third_party/glad/src/glad.c
)

# ------------------------------------------------------------------------------
# 프로젝트 소스
# ------------------------------------------------------------------------------
file(GLOB SRC_FILES
    ${CMAKE_SOURCE_DIR}/src/*.cpp
)

add_executable(opengl_port
    ${SRC_FILES}
    ${GLAD_SOURCES}
)

# ------------------------------------------------------------------------------
# 링크 및 인클루드 설정
# ------------------------------------------------------------------------------
target_link_libraries(opengl_port PRIVATE glfw)

# stb 헤더 추가
target_include_directories(opengl_port PRIVATE ${CMAKE_SOURCE_DIR}/third_party/stb)

# 리눅스 호환성 (pthread, dl)
if(UNIX AND NOT APPLE)
    target_link_libraries(opengl_port PRIVATE dl pthread)
endif()

message(STATUS "GLFW integration complete.")
