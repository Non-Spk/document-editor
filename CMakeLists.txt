cmake_minimum_required(VERSION 3.10)
project(document_editor LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(document-editor src/main.cpp)
# Ensure the include directory is visible to the target
target_include_directories(document-editor PRIVATE ${CMAKE_SOURCE_DIR}/include)
# Add headers (they are header-only / inline implementations)
