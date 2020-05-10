#ifndef MEM2VID_MEM2VID_H
#define MEM2VID_MEM2VID_H

#include <libavcodec/avcodec.h>
#include <libavutil/opt.h>

#include <stdio.h>

typedef struct {
    AVCodecContext *enc_ctx;
    AVFrame *frame;
    AVPacket *pkt;
    FILE *outfile;
    /** index of the next frame */
    uint32_t frame_index;
} video_t;

/** if EXIT_SUCCESS is returned, a call to {video_finish} is required */
// todo associate file extensions with codec
int video_start(video_t *p_video, const char *p_filename);

/** finalizes the video creation */
void video_finish(video_t *p_video);

/** data format is YCbCr*/
int video_submit(video_t *p_video, const uint8_t *Y, const uint8_t *Cb, const uint8_t *Cr);

#endif //MEM2VID_MEM2VID_H
