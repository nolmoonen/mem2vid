This library is a wrapper of [FFmpeg](https://www.ffmpeg.org/), in order to easily create MP4-formatted video from RGB 
 data. Start the creation of a video with `video_start`, push frames to it with `video_submit`, and finalize video 
 creation by calling `video_finish`. An example is included in `example/example.c`. Only one video can be created at a 
 time.

### Using
The following steps describe how to use this library with the MinGW-w64 compiler.
- Download and extract a release build.
- Link the import library `libmem2vid.dll.a` to your executable (with CMake, this is done with 
 `target_link_libraries`).
- Include header `include/mem2vid/mem2vid.h` to your executable (with CMake, this is done with
 `target_include_directories`).
- Place all `.dll` files in the same directory as your built executable.

### Building
The following steps describe how to build this project with the MinGW-w64 compiler.
- Download FFmpeg import libraries and headers [here](https://ffmpeg.zeranoe.com/builds/). Choose version 4.2.2, 
 linking type development (`dev`).
- Extract and place contents into `external/ffmpeg-4.2.2-dev`.
- Download FFmpeg shared libraries [here](https://ffmpeg.zeranoe.com/builds/). Choose version 4.2.2, 
 linking type shared (`shared`).
- Extract and place contents into `external/ffmpeg-4.2.2-shared`.
- Build the library and example with CMake.

### 
See [here](https://ffmpeg.org/doxygen/4.1/examples.html) for the examples followed in creating the library.
