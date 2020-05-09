add_executable(example ${CMAKE_CURRENT_SOURCE_DIR}/main.c)
target_link_libraries(example PRIVATE mem2vid)