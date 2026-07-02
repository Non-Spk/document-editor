cmake_minimum_required(VERSION 3.10)

# Set the project name
project(DocumentEditorFramework)

# Set C++ standard to 17 or higher for modern features
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the include directory
include_directories(include)

# Find all source files in the src directory
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Add the executable
add_executable(DocumentEditor ${SOURCES})

# Optional: Enable warnings
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()
