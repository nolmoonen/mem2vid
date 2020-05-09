cmake_minimum_required(VERSION 3.16)

project(mem2vid C)

set(CMAKE_C_STANDARD 99)

# build library
add_subdirectory(src)

# build examples
add_subdirectory(examples)