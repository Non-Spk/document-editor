cmake_minimum_required(VERSION 3.10)
project(document_editor LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_include_directories(${CMAKE_SOURCE_DIR}/include)
add_executable(document-editor src/main.cpp)
# Add headers (they are header-only / inline implementations)

