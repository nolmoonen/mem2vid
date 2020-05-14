#include <mem2vid/mem2vid.h>

int main(void)
{
    const uint32_t FRAMES_PER_SECOND = 30;
    const uint32_t WIDTH = 1280;
    const uint32_t HEIGHT = 720;

    video_param_t params = {.size_x=WIDTH, .size_y=HEIGHT, .frames_per_second=FRAMES_PER_SECOND, .bitrate=20};
    int ret = video_start("example", params); // initialize video with chosen parameters
    if (ret != EXIT_SUCCESS) {
        fprintf(stderr, "failed to initialize video\n");

        return EXIT_FAILURE;
    }

    uint8_t *rgb = malloc(WIDTH * HEIGHT * 3);  // holds the data for a single frame
    for (uint32_t i = 0; i < FRAMES_PER_SECOND * 10; i++) {
        uint32_t p = 0;
        for (uint32_t h = 0; h < HEIGHT; h++) {
            for (uint32_t w = 0; w < WIDTH; w++) {
                // fill the buffer with some testing data
                rgb[p++] = w + i; // r
                rgb[p++] = h + i; // g
                rgb[p++] = h + w; // b
            }
        }

        video_submit(rgb); // push the frame to the video
    }

    video_finish(); // finalize the video creation, perform cleanup
    free(rgb);

    return EXIT_SUCCESS;
}
