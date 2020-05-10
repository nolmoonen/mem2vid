#include <mem2vid/mem2vid.h>

const uint32_t FRAMES_PER_SECOND = 25; // todo put in configuration parameters

/** encode a single frame */
// todo decompose the functionality of this method?
static int encode(video_t *p_video)
{
    int ret;

    // send the frame to the encoder
    if (p_video->frame) {
        printf("Send frame %3"PRId64"\n", p_video->frame->pts);
    }

    ret = avcodec_send_frame(p_video->enc_ctx, p_video->frame);
    if (ret < 0) {
        fprintf(stderr, "Error sending a frame for encoding\n");
        return EXIT_FAILURE;
    }

    while (ret >= 0) {
        ret = avcodec_receive_packet(p_video->enc_ctx, p_video->pkt);
        if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
            return EXIT_SUCCESS;
        else if (ret < 0) {
            fprintf(stderr, "Error during encoding\n");
            return EXIT_FAILURE;
        }

        printf("Write packet %3"PRId64" (size=%5d)\n", p_video->pkt->pts, p_video->pkt->size);
        fwrite(p_video->pkt->data, 1, p_video->pkt->size, p_video->outfile);
        av_packet_unref(p_video->pkt);
    }

    return EXIT_SUCCESS;
}

int video_start(video_t *p_video, const char *p_filename)
{
    const AVCodec *codec;

    /** perform initialization */
    // find the mpeg1video encoder
    codec = avcodec_find_encoder(AV_CODEC_ID_MPEG1VIDEO);
    if (!codec) {
        fprintf(stderr, "mpeg1video encoder not found\n");
        goto cleanup_none;
    }

    // allocate video codec context
    p_video->enc_ctx = avcodec_alloc_context3(codec);
    if (!p_video->enc_ctx) {
        fprintf(stderr, "Could not allocate video codec context\n");
        goto cleanup_none;
    }

    // allocate packet
    p_video->pkt = av_packet_alloc();
    if (!p_video->pkt) {
        fprintf(stderr, "Could not allocate packet\n");
        goto cleanup_context;
    }

    // todo these options should go in some type of parameters
    // put sample parameters
    p_video->enc_ctx->bit_rate = 400000;
    // resolution must be a multiple of two
    p_video->enc_ctx->width = 352;
    p_video->enc_ctx->height = 288;
    // frames per second
    p_video->enc_ctx->time_base = (AVRational) {1, FRAMES_PER_SECOND};
    p_video->enc_ctx->framerate = (AVRational) {FRAMES_PER_SECOND, 1};
    /* emit one intra frame every ten frames
     * check frame pict_type before passing frame
     * to encoder, if frame->pict_type is AV_PICTURE_TYPE_I
     * then gop_size is ignored and the output of encoder
     * will always be I frame irrespective to gop_size
     */
    p_video->enc_ctx->gop_size = 10;
    p_video->enc_ctx->max_b_frames = 1;
    p_video->enc_ctx->pix_fmt = AV_PIX_FMT_YUV420P;

    if (codec->id == AV_CODEC_ID_H264) {
        av_opt_set(p_video->enc_ctx->priv_data, "preset", "slow", 0);
    }

    // open it
    int ret = avcodec_open2(p_video->enc_ctx, codec, NULL);
    if (ret < 0) {
        fprintf(stderr, "Could not open codec: %s\n", av_err2str(ret));
        goto cleanup_context_packet;
    }

    // open file
    p_video->outfile = fopen(p_filename, "wb");
    if (!p_video->outfile) {
        fprintf(stderr, "Could not open %s\n", p_filename);
        goto cleanup_context_packet;
    }

    // allocate video frame
    p_video->frame = av_frame_alloc();
    if (!p_video->frame) {
        fprintf(stderr, "Could not allocate video frame\n");
        goto cleanup_context_packet_file;
    }

    p_video->frame->format = p_video->enc_ctx->pix_fmt;
    p_video->frame->width = p_video->enc_ctx->width;
    p_video->frame->height = p_video->enc_ctx->height;

    ret = av_frame_get_buffer(p_video->frame, 32);
    if (ret < 0) {
        fprintf(stderr, "Could not allocate the video frame data\n");
        goto cleanup_all;
    }

    p_video->frame_index = 0;

    return EXIT_SUCCESS;

    /** cleanup in case initialization fails */
    // NB: duplicate tail as {video_finish}
    cleanup_all:
    // free frame
    av_frame_free(&p_video->frame);

    cleanup_context_packet_file:
    // close file
    fclose(p_video->outfile);

    cleanup_context_packet:
    // free packet
    av_packet_free(&p_video->pkt);

    cleanup_context:
    // free context
    avcodec_free_context(&p_video->enc_ctx);

    cleanup_none:
    return EXIT_SUCCESS;
}

void video_finish(video_t *p_video)
{
    // MPEG file sequence end code
    // todo how is this handled in the case of other codecs?
    const uint8_t endcode[] = {0, 0, 1, 0xb7};

    // flush the encoder
    p_video->frame = NULL;
    encode(p_video);

    // add sequence end code to have a real MPEG file
    fwrite(endcode, 1, sizeof(endcode), p_video->outfile);

    // NB: duplicate tail as {video_start}
    // free frame
    av_frame_free(&p_video->frame);

    // close file
    fclose(p_video->outfile);

    // free packet
    av_packet_free(&p_video->pkt);

    // free context
    avcodec_free_context(&p_video->enc_ctx);
}

int video_submit(video_t *p_video, const uint8_t *Y, const uint8_t *Cb, const uint8_t *Cr)
{
    int ret;

    /** prepare the frame */
    fflush(stdout);

    // make sure the frame data is writable
    ret = av_frame_make_writable(p_video->frame);
    if (ret < 0) {
        return EXIT_FAILURE;
    }

    // todo figure out the format and size of this data
    // copy data: first all Y, then all Cb, then all Cr
    memcpy(p_video->frame->data[0], Y, p_video->frame->linesize[0] * p_video->enc_ctx->height);
    memcpy(p_video->frame->data[1], Cb, p_video->frame->linesize[1] * (p_video->enc_ctx->height / 2));
    memcpy(p_video->frame->data[2], Cr, p_video->frame->linesize[2] * (p_video->enc_ctx->height / 2));

    p_video->frame->pts = p_video->frame_index++;

    /** encode the image */
    return encode(p_video);
}