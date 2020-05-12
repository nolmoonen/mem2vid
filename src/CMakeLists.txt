add_library(mem2vid SHARED ${CMAKE_CURRENT_SOURCE_DIR}/mem2vid.c ${CMAKE_SOURCE_DIR}/include/mem2vid/mem2vid.h)
target_include_directories(mem2vid PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(mem2vid PRIVATE ${CMAKE_SOURCE_DIR}/external/ffmpeg-4.2.2/lib/libavcodec.dll.a)
target_link_libraries(mem2vid PRIVATE ${CMAKE_SOURCE_DIR}/external/ffmpeg-4.2.2/lib/libavutil.dll.a)
target_link_libraries(mem2vid PRIVATE ${CMAKE_SOURCE_DIR}/external/ffmpeg-4.2.2/lib/libavformat.dll.a)
target_include_directories(mem2vid PUBLIC ${CMAKE_SOURCE_DIR}/external/ffmpeg-4.2.2/include)