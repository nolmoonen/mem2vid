cmake_minimum_required(VERSION 3.16)

project(mem2vid C)

set(CMAKE_C_STANDARD 99)

# put the built library and examples in same directory
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# build library
add_subdirectory(src)

# build example
add_subdirectory(example)