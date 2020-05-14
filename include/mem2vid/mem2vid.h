#ifndef MEM2VID_MEM2VID_H
#define MEM2VID_MEM2VID_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    /** size of the video in pixels */
    uint32_t size_x;  // horizontal dimension
    uint32_t size_y;  // vertical dimension
    uint32_t frames_per_second;
    /**
     * bitrate of the video in Mbps
     * see https://support.google.com/youtube/answer/1722171 for recommended bitrates */
    uint32_t bitrate;
} video_param_t;

/**
 * {name} is the name of the file, not including extension (will always be .mp4)
 * if EXIT_SUCCESS is returned, a call to {video_finish} is required */
int video_start(const char *name, video_param_t param);

/** finalizes the video creation */
void video_finish();

/** data format is rgbrgbrgbrgbrgb */
int video_submit(const uint8_t *rgb);

#endif //MEM2VID_MEM2VID_H
