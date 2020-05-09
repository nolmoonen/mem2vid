This project provides an interface to [FFmpeg](https://www.ffmpeg.org/), in order to easily create videos from memory.

### Using
The following steps describe how to use this project with the MinGW-w64 compiler.
- Download and extract a release build.
- Link the import library `libmem2vid.dll.a` to your executable (with CMake, this is done with 
 `target_link_libraries`).
- Place all `.dll` files in the same directory as your built executable.

### Building
The following steps describe how to build this project with the MinGW-w64 compiler.
- Download development binaries [here](https://ffmpeg.zeranoe.com/builds/). Choose version 4.2.2, 
 linking type development (`dev`).
- Extract and place contents into `external/ffmpeg-4.2.2`.
- Build the library with CMake.
