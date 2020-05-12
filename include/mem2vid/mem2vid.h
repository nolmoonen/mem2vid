#ifndef MEM2VID_MEM2VID_H
#define MEM2VID_MEM2VID_H

#include <stdio.h>

#include <libavcodec/avcodec.h>
#include <libavutil/opt.h>
#include <libavformat/avformat.h>

typedef struct {
    /** Output format, is always MP4. */
    AVOutputFormat *format;
    AVFormatContext *output_context;

    /** Output stream */
    AVStream *stream;
    AVCodecContext *enc;
    AVFrame *frame;

    AVCodec *codec;
    /** index of the next frame */
    uint32_t frame_index;
} video_t;

typedef struct {
    uint32_t width;
    uint32_t height;
    uint32_t frames_per_second;
} video_param_t;

/**
 * {name} is the name of the file, not including extension
 * if EXIT_SUCCESS is returned, a call to {video_finish} is required */
int video_start(video_t *video, const char *name, video_param_t param);

/** finalizes the video creation */
void video_finish(video_t *video);

/** data format is YCbCr */
int video_submit(video_t *video, const uint8_t *Y, const uint8_t *Cb, const uint8_t *Cr);

#endif //MEM2VID_MEM2VID_H
