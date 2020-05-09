#include <mem2vid/mem2vid.h>
#include <stdio.h>
#include <libavcodec/avcodec.h>

void hello(void)
{
    printf("Hello, World!\n");

    const char *codec_name = "libx264";
    const AVCodec *codec = avcodec_find_encoder_by_name(codec_name);
    if (!codec) {
        fprintf(stderr, "Codec '%s' not found\n", codec_name);
        exit(1);
    } else {
        fprintf(stdout, "Codec '%s' found\n", codec_name);
        exit(0);
    }
}
