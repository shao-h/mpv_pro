#include "demux.h"

static int try_open_file(struct demuxer *demux, enum demux_check check)
{
    // 打印日志
    MP_INFO(demux, "hl videoforensic demuxer\n");
    return 0;
}

const struct demuxer_desc demuxer_desc_hlvf = {
    .name = "hlvf",
    .desc = "Demuxer for HL VideoForensic",
    .open = try_open_file,
};