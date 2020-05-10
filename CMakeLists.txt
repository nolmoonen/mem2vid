cmake_minimum_required(VERSION 3.16)

project(mem2vid C)

set(CMAKE_C_STANDARD 99)

# put the built library and examples in same directory
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# build library
add_subdirectory(src)

# build examples
add_subdirectory(examples)