cmake_minimum_required(VERSION 3.10)
project(CharacterCode)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Fetch JSON
include(FetchContent)
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3
)
FetchContent_MakeAvailable(nlohmann_json)

# Add sources
file(GLOB_RECURSE SRC_FILES "Game/*.cpp")
add_executable(${PROJECT_NAME} ${SRC_FILES})

# Include directories
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/Game)

# Find libraries
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
# TODO: Ensure SOIL is available or add manually

target_link_libraries(${PROJECT_NAME} PRIVATE
    OpenGL::GL
    GLUT::GLUT
    SOIL  # or path to SOIL lib
    nlohmann_json::nlohmann_json
    gdi32
)
