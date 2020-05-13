add_library(mem2vid SHARED ${CMAKE_CURRENT_SOURCE_DIR}/mem2vid.c ${CMAKE_SOURCE_DIR}/include/mem2vid/mem2vid.h)
target_include_directories(mem2vid PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(mem2vid PRIVATE ${CMAKE_SOURCE_DIR}/external/ffmpeg-4.2.2-dev/lib/libavcodec.dll.a)
target_link_libraries(mem2vid PRIVATE ${CMAKE_SOURCE_DIR}/external/ffmpeg-4.2.2-dev/lib/libavutil.dll.a)
target_link_libraries(mem2vid PRIVATE ${CMAKE_SOURCE_DIR}/external/ffmpeg-4.2.2-dev/lib/libavformat.dll.a)
target_link_libraries(mem2vid PRIVATE ${CMAKE_SOURCE_DIR}/external/ffmpeg-4.2.2-dev/lib/libswscale.dll.a)
target_include_directories(mem2vid PUBLIC ${CMAKE_SOURCE_DIR}/external/ffmpeg-4.2.2-dev/include)

# copy FFmpeg shared libraries to binary directory
configure_file(${CMAKE_SOURCE_DIR}/external/ffmpeg-4.2.2-shared/bin/avcodec-58.dll
        ${CMAKE_SOURCE_DIR}/bin COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/external/ffmpeg-4.2.2-shared/bin/avutil-56.dll
        ${CMAKE_SOURCE_DIR}/bin COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/external/ffmpeg-4.2.2-shared/bin/avformat-58.dll
        ${CMAKE_SOURCE_DIR}/bin COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/external/ffmpeg-4.2.2-shared/bin/swresample-3.dll
        ${CMAKE_SOURCE_DIR}/bin COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/external/ffmpeg-4.2.2-shared/bin/swscale-5.dll
        ${CMAKE_SOURCE_DIR}/bin COPYONLY)