cmake_minimum_required(VERSION 3.16)
project(mem2vid C)

set(CMAKE_C_STANDARD 99)

add_library(mem2vid library.c library.h)