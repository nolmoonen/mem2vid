#include <mem2vid/mem2vid.h>

const uint32_t FRAMES_PER_SECOND = 25; // todo put in configuration parameters

int main(void)
{
    video_t video;
    video_start(&video, "example.mpg");

    uint8_t *Y = malloc(video.frame->linesize[0] * video.enc_ctx->height);
    uint8_t *Cb = malloc(video.frame->linesize[1] * (video.enc_ctx->height / 2));
    uint8_t *Cr = malloc(video.frame->linesize[2] * (video.enc_ctx->height / 2));

    // encode 10 seconds of video
    for (uint32_t i = 0; i < FRAMES_PER_SECOND * 10; i++) {
        // Y component
        for (uint32_t y = 0; y < video.enc_ctx->height; y++) {
            for (uint32_t x = 0; x < video.enc_ctx->width; x++) {
                Y[y * video.frame->linesize[0] + x] = x + y + i * 3;
            }
        }

        // Cb and Cr components
        for (uint32_t y = 0; y < video.enc_ctx->height / 2; y++) {
            for (uint32_t x = 0; x < video.enc_ctx->width / 2; x++) {
                Cb[y * video.frame->linesize[1] + x] = 128 + y + i * 2;
                Cr[y * video.frame->linesize[2] + x] = 64 + x + i * 5;
            }
        }

        video_submit(&video, Y, Cb, Cr);
    }

    video_finish(&video);

    return EXIT_SUCCESS;
}
