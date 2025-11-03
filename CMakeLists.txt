# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Set the project name
project(CharacterCode)
# initialize clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


link_directories(
    "lib"
)

# --- Define Output Directories ---
# This line tells CMake to put all executables (.exe) into a "bin" folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# These lines are for libraries (.dll, .a). It's good practice to set them now.
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Tell CMake to use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# --- Corrected Order ---

# 1. Find all your .cpp files in the "src" directory
file(GLOB_RECURSE SRC_FILES "src/*.cpp")

# 2. Add the executable target.
#    This line CREATES the target.
add_executable(
    ${PROJECT_NAME} # The name of your final executable
    ${SRC_FILES}    # All your other .cpp files
)
target_compile_definitions(${PROJECT_NAME} PRIVATE 
    "PROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\""
)

target_link_libraries(CharacterCode
    SOIL
    freeglut
    gdi32
    opengl32
    glu32
    ${OPENGL_LIBRARIES}
    ${GLUT_LIBRARY}
)
# 3. Add your "include" directory to the target.
#    This line MODIFIES the target.
target_include_directories(${PROJECT_NAME} PUBLIC include)

target_compile_definitions(${PROJECT_NAME} PRIVATE "PROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\"")