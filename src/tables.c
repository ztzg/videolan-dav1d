/*
 * Copyright © 2018, VideoLAN and dav1d authors
 * Copyright © 2018, Two Orioles, LLC
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"

#include <stdint.h>

#include "common/attributes.h"

#include "src/levels.h"
#include "src/tables.h"

const uint8_t dav1d_al_part_ctx[2][N_BL_LEVELS][N_PARTITIONS] = {
    {
        // partitions:
        // none,  h,    v, split,  tts,  tbs,  tls,  trs,   h4,   v4
        { 0x00, 0x00, 0x10,   -1, 0x00, 0x10, 0x10, 0x10,   -1,   -1 }, // bl128
        { 0x10, 0x10, 0x18,   -1, 0x10, 0x18, 0x18, 0x18, 0x10, 0x1c }, // bl64
        { 0x18, 0x18, 0x1c,   -1, 0x18, 0x1c, 0x1c, 0x1c, 0x18, 0x1e }, // bl32
        { 0x1c, 0x1c, 0x1e,   -1, 0x1c, 0x1e, 0x1e, 0x1e, 0x1c, 0x1f }, // bl16
        { 0x1e, 0x1e, 0x1f, 0x1f,   -1,   -1,   -1,   -1,   -1,   -1 }, // bl8
    }, {
        { 0x00, 0x10, 0x00,   -1, 0x10, 0x10, 0x00, 0x10,   -1,   -1 }, // bl128
        { 0x10, 0x18, 0x10,   -1, 0x18, 0x18, 0x10, 0x18, 0x1c, 0x10 }, // bl64
        { 0x18, 0x1c, 0x18,   -1, 0x1c, 0x1c, 0x18, 0x1c, 0x1e, 0x18 }, // bl32
        { 0x1c, 0x1e, 0x1c,   -1, 0x1e, 0x1e, 0x1c, 0x1e, 0x1f, 0x1c }, // bl16
        { 0x1e, 0x1f, 0x1e, 0x1f,   -1,   -1,   -1,   -1,   -1,   -1 }, // bl8
    }
};

const uint8_t /* enum BlockSize */
    dav1d_block_sizes[N_BL_LEVELS][N_PARTITIONS][2] =
{
    [BL_128X128] = {
        [PARTITION_NONE]           = { BS_128x128 },
        [PARTITION_H]              = { BS_128x64 },
        [PARTITION_V]              = { BS_64x128 },
        [PARTITION_T_TOP_SPLIT]    = { BS_64x64, BS_128x64 },
        [PARTITION_T_BOTTOM_SPLIT] = { BS_128x64, BS_64x64 },
        [PARTITION_T_LEFT_SPLIT]   = { BS_64x64, BS_64x128 },
        [PARTITION_T_RIGHT_SPLIT]  = { BS_64x128, BS_64x64 },
    }, [BL_64X64] = {
        [PARTITION_NONE]           = { BS_64x64 },
        [PARTITION_H]              = { BS_64x32 },
        [PARTITION_V]              = { BS_32x64 },
        [PARTITION_T_TOP_SPLIT]    = { BS_32x32, BS_64x32 },
        [PARTITION_T_BOTTOM_SPLIT] = { BS_64x32, BS_32x32 },
        [PARTITION_T_LEFT_SPLIT]   = { BS_32x32, BS_32x64 },
        [PARTITION_T_RIGHT_SPLIT]  = { BS_32x64, BS_32x32 },
        [PARTITION_H4]             = { BS_64x16 },
        [PARTITION_V4]             = { BS_16x64 },
    }, [BL_32X32] = {
        [PARTITION_NONE]           = { BS_32x32 },
        [PARTITION_H]              = { BS_32x16 },
        [PARTITION_V]              = { BS_16x32 },
        [PARTITION_T_TOP_SPLIT]    = { BS_16x16, BS_32x16 },
        [PARTITION_T_BOTTOM_SPLIT] = { BS_32x16, BS_16x16 },
        [PARTITION_T_LEFT_SPLIT]   = { BS_16x16, BS_16x32 },
        [PARTITION_T_RIGHT_SPLIT]  = { BS_16x32, BS_16x16 },
        [PARTITION_H4]             = { BS_32x8  },
        [PARTITION_V4]             = { BS_8x32  },
    }, [BL_16X16] = {
        [PARTITION_NONE]           = { BS_16x16 },
        [PARTITION_H]              = { BS_16x8  },
        [PARTITION_V]              = { BS_8x16  },
        [PARTITION_T_TOP_SPLIT]    = { BS_8x8,   BS_16x8  },
        [PARTITION_T_BOTTOM_SPLIT] = { BS_16x8,  BS_8x8   },
        [PARTITION_T_LEFT_SPLIT]   = { BS_8x8,   BS_8x16  },
        [PARTITION_T_RIGHT_SPLIT]  = { BS_8x16,  BS_8x8   },
        [PARTITION_H4]             = { BS_16x4  },
        [PARTITION_V4]             = { BS_4x16  },
    }, [BL_8X8] = {
        [PARTITION_NONE]           = { BS_8x8   },
        [PARTITION_H]              = { BS_8x4   },
        [PARTITION_V]              = { BS_4x8   },
        [PARTITION_SPLIT]          = { BS_4x4   },
    }
};

const uint8_t dav1d_block_dimensions[N_BS_SIZES][4] = {
    [BS_128x128] = { 32, 32, 5, 5 },
    [BS_128x64]  = { 32, 16, 5, 4 },
    [BS_64x128]  = { 16, 32, 4, 5 },
    [BS_64x64]   = { 16, 16, 4, 4 },
    [BS_64x32]   = { 16,  8, 4, 3 },
    [BS_64x16]   = { 16,  4, 4, 2 },
    [BS_32x64]   = {  8, 16, 3, 4 },
    [BS_32x32]   = {  8,  8, 3, 3 },
    [BS_32x16]   = {  8,  4, 3, 2 },
    [BS_32x8]    = {  8,  2, 3, 1 },
    [BS_16x64]   = {  4, 16, 2, 4 },
    [BS_16x32]   = {  4,  8, 2, 3 },
    [BS_16x16]   = {  4,  4, 2, 2 },
    [BS_16x8]    = {  4,  2, 2, 1 },
    [BS_16x4]    = {  4,  1, 2, 0 },
    [BS_8x32]    = {  2,  8, 1, 3 },
    [BS_8x16]    = {  2,  4, 1, 2 },
    [BS_8x8]     = {  2,  2, 1, 1 },
    [BS_8x4]     = {  2,  1, 1, 0 },
    [BS_4x16]    = {  1,  4, 0, 2 },
    [BS_4x8]     = {  1,  2, 0, 1 },
    [BS_4x4]     = {  1,  1, 0, 0 },
};

const TxfmInfo dav1d_txfm_dimensions[N_RECT_TX_SIZES] = {
    [ TX_4X4]   = { .w = 1, .h = 1, .lw = 0, .lh = 0,
                    .min = 0, .max = 0, .ctx = 0 },
    [ TX_8X8]   = { .w = 2, .h = 2, .lw = 1, .lh = 1,
                    .min = 1, .max = 1, .sub = TX_4X4, .ctx = 1 },
    [ TX_16X16] = { .w = 4, .h = 4, .lw = 2, .lh = 2,
                    .min = 2, .max = 2, .sub = TX_8X8, .ctx = 2 },
    [ TX_32X32] = { .w = 8, .h = 8, .lw = 3, .lh = 3,
                    .min = 3, .max = 3, .sub = TX_16X16, .ctx = 3 },
    [ TX_64X64] = { .w = 16, .h = 16, .lw = 4, .lh = 4,
                    .min = 4, .max = 4, .sub = TX_32X32, .ctx = 4 },
    [RTX_4X8]   = { .w = 1, .h = 2, .lw = 0, .lh = 1,
                    .min = 0, .max = 1, .sub = TX_4X4, .ctx = 1 },
    [RTX_8X4]   = { .w = 2, .h = 1, .lw = 1, .lh = 0,
                    .min = 0, .max = 1, .sub = TX_4X4, .ctx = 1 },
    [RTX_8X16]  = { .w = 2, .h = 4, .lw = 1, .lh = 2,
                    .min = 1, .max = 2, .sub = TX_8X8, .ctx = 2 },
    [RTX_16X8]  = { .w = 4, .h = 2, .lw = 2, .lh = 1,
                    .min = 1, .max = 2, .sub = TX_8X8, .ctx = 2 },
    [RTX_16X32] = { .w = 4, .h = 8, .lw = 2, .lh = 3,
                    .min = 2, .max = 3, .sub = TX_16X16, .ctx = 3 },
    [RTX_32X16] = { .w = 8, .h = 4, .lw = 3, .lh = 2,
                    .min = 2, .max = 3, .sub = TX_16X16, .ctx = 3 },
    [RTX_32X64] = { .w = 8, .h = 16, .lw = 3, .lh = 4,
                    .min = 3, .max = 4, .sub = TX_32X32, .ctx = 4 },
    [RTX_64X32] = { .w = 16, .h = 8, .lw = 4, .lh = 3,
                    .min = 3, .max = 4, .sub = TX_32X32, .ctx = 4 },
    [RTX_4X16]  = { .w = 1, .h = 4, .lw = 0, .lh = 2,
                    .min = 0, .max = 2, .sub = RTX_4X8, .ctx = 1 },
    [RTX_16X4]  = { .w = 4, .h = 1, .lw = 2, .lh = 0,
                    .min = 0, .max = 2, .sub = RTX_8X4, .ctx = 1 },
    [RTX_8X32]  = { .w = 2, .h = 8, .lw = 1, .lh = 3,
                    .min = 1, .max = 3, .sub = RTX_8X16, .ctx = 2 },
    [RTX_32X8]  = { .w = 8, .h = 2, .lw = 3, .lh = 1,
                    .min = 1, .max = 3, .sub = RTX_16X8, .ctx = 2 },
    [RTX_16X64] = { .w = 4, .h = 16, .lw = 2, .lh = 4,
                    .min = 2, .max = 4, .sub = RTX_16X32, .ctx = 3 },
    [RTX_64X16] = { .w = 16, .h = 4, .lw = 4, .lh = 2,
                    .min = 2, .max = 4, .sub = RTX_32X16, .ctx = 3 },
};

const uint8_t /* enum (Rect)TxfmSize */
    dav1d_max_txfm_size_for_bs[N_BS_SIZES][4 /* y, 420, 422, 444 */] =
{
    [BS_128x128] = {  TX_64X64,  TX_32X32,  TX_32X32,  TX_32X32 },
    [BS_128x64]  = {  TX_64X64,  TX_32X32,  TX_32X32,  TX_32X32 },
    [BS_64x128]  = {  TX_64X64,  TX_32X32,       0,    TX_32X32 },
    [BS_64x64]   = {  TX_64X64,  TX_32X32,  TX_32X32,  TX_32X32 },
    [BS_64x32]   = { RTX_64X32, RTX_32X16,  TX_32X32,  TX_32X32 },
    [BS_64x16]   = { RTX_64X16, RTX_32X8,  RTX_32X16, RTX_32X16 },
    [BS_32x64]   = { RTX_32X64, RTX_16X32,       0,    TX_32X32 },
    [BS_32x32]   = {  TX_32X32,  TX_16X16, RTX_16X32,  TX_32X32 },
    [BS_32x16]   = { RTX_32X16, RTX_16X8,   TX_16X16, RTX_32X16 },
    [BS_32x8]    = { RTX_32X8,  RTX_16X4,  RTX_16X8,  RTX_32X8  },
    [BS_16x64]   = { RTX_16X64, RTX_8X32,        0,   RTX_16X32 },
    [BS_16x32]   = { RTX_16X32, RTX_8X16,        0,   RTX_16X32 },
    [BS_16x16]   = {  TX_16X16,  TX_8X8,   RTX_8X16,   TX_16X16 },
    [BS_16x8]    = { RTX_16X8,  RTX_8X4,    TX_8X8,   RTX_16X8  },
    [BS_16x4]    = { RTX_16X4,  RTX_8X4,   RTX_8X4,   RTX_16X4  },
    [BS_8x32]    = { RTX_8X32,  RTX_4X16,       0,    RTX_8X32  },
    [BS_8x16]    = { RTX_8X16,  RTX_4X8,        0,    RTX_8X16  },
    [BS_8x8]     = {  TX_8X8,    TX_4X4,   RTX_4X8,    TX_8X8   },
    [BS_8x4]     = { RTX_8X4,    TX_4X4,    TX_4X4,   RTX_8X4   },
    [BS_4x16]    = { RTX_4X16,  RTX_4X8,        0,    RTX_4X16  },
    [BS_4x8]     = { RTX_4X8,    TX_4X4,        0,    RTX_4X8   },
    [BS_4x4]     = {  TX_4X4,    TX_4X4,    TX_4X4,    TX_4X4   },
};

const uint8_t /* enum TxfmType */
    dav1d_txtp_from_uvmode[N_UV_INTRA_PRED_MODES] =
{
    [DC_PRED]              = DCT_DCT,
    [VERT_PRED]            = ADST_DCT,
    [HOR_PRED]             = DCT_ADST,
    [DIAG_DOWN_LEFT_PRED]  = DCT_DCT,
    [DIAG_DOWN_RIGHT_PRED] = ADST_ADST,
    [VERT_RIGHT_PRED]      = ADST_DCT,
    [HOR_DOWN_PRED]        = DCT_ADST,
    [HOR_UP_PRED]          = DCT_ADST,
    [VERT_LEFT_PRED]       = ADST_DCT,
    [SMOOTH_PRED]          = ADST_ADST,
    [SMOOTH_V_PRED]        = ADST_DCT,
    [SMOOTH_H_PRED]        = DCT_ADST,
    [PAETH_PRED]           = ADST_ADST,
};

const uint8_t /* enum InterPredMode */
    dav1d_comp_inter_pred_modes[N_COMP_INTER_PRED_MODES][2] =
{
    [NEARESTMV_NEARESTMV] = { NEARESTMV, NEARESTMV },
    [NEARMV_NEARMV]       = { NEARMV,    NEARMV    },
    [NEWMV_NEWMV]         = { NEWMV,     NEWMV     },
    [GLOBALMV_GLOBALMV]   = { GLOBALMV,  GLOBALMV  },
    [NEWMV_NEARESTMV]     = { NEWMV,     NEARESTMV },
    [NEWMV_NEARMV]        = { NEWMV,     NEARMV    },
    [NEARESTMV_NEWMV]     = { NEARESTMV, NEWMV     },
    [NEARMV_NEWMV]        = { NEARMV,    NEWMV     },
};

const uint8_t dav1d_tx_type_count[N_TXTP_SETS] = {
    [TXTP_SET_DCT] = 1,
    [TXTP_SET_DCT_ID] = 2,
    [TXTP_SET_DT4_ID] = 5,
    [TXTP_SET_DT4_ID_1D] = 7,
    [TXTP_SET_DT9_ID_1D] = 12,
    [TXTP_SET_ALL] = 16,
    [TXTP_SET_LOSSLESS] = 1,
};

const uint8_t /* enum TxfmType */
              dav1d_tx_types_per_set[N_TXTP_SETS][N_TX_TYPES] =
{
    [TXTP_SET_DCT]       = { DCT_DCT },
    [TXTP_SET_DCT_ID]    = { IDTX, DCT_DCT },
    [TXTP_SET_DT4_ID]    = { IDTX, DCT_DCT, ADST_ADST, ADST_DCT, DCT_ADST },
    [TXTP_SET_DT4_ID_1D] = { IDTX, DCT_DCT, V_DCT, H_DCT, ADST_ADST, ADST_DCT,
                             DCT_ADST },
    [TXTP_SET_DT9_ID_1D] = { IDTX, V_DCT, H_DCT, DCT_DCT, ADST_DCT, DCT_ADST,
                             FLIPADST_DCT, DCT_FLIPADST, ADST_ADST,
                             FLIPADST_FLIPADST, ADST_FLIPADST, FLIPADST_ADST },
    [TXTP_SET_ALL]       = { IDTX, V_DCT, H_DCT, V_ADST, H_ADST, V_FLIPADST,
                             H_FLIPADST, DCT_DCT, ADST_DCT, DCT_ADST,
                             FLIPADST_DCT, DCT_FLIPADST, ADST_ADST,
                             FLIPADST_FLIPADST, ADST_FLIPADST, FLIPADST_ADST },
    [TXTP_SET_LOSSLESS]  = { WHT_WHT },
};

const uint8_t dav1d_tx_type_set_index[2][N_TXTP_SETS] = {
    { 0, -1,  2,  1, -1, -1, 3 },
    { 0,  3, -1, -1,  2,  1, 4 },
};

const uint8_t dav1d_ymode_size_context[N_BS_SIZES] = {
    [BS_128x128] = 3,
    [BS_128x64]  = 3,
    [BS_64x128]  = 3,
    [BS_64x64]   = 3,
    [BS_64x32]   = 3,
    [BS_64x16]   = 2,
    [BS_32x64]   = 3,
    [BS_32x32]   = 3,
    [BS_32x16]   = 2,
    [BS_32x8 ]   = 1,
    [BS_16x64]   = 2,
    [BS_16x32]   = 2,
    [BS_16x16]   = 2,
    [BS_16x8 ]   = 1,
    [BS_16x4 ]   = 0,
    [BS_8x32 ]   = 1,
    [BS_8x16 ]   = 1,
    [BS_8x8  ]   = 1,
    [BS_8x4  ]   = 0,
    [BS_4x16 ]   = 0,
    [BS_4x8  ]   = 0,
    [BS_4x4  ]   = 0,
};

const uint8_t dav1d_nz_map_ctx_offset[N_RECT_TX_SIZES][5][5] = {
    [TX_4X4] = {
        { 0, 1, 6, 6 },
        { 1, 6, 6, 21 },
        { 6, 6, 21, 21 },
        { 6, 21, 21, 21 },
    }, [TX_8X8] = {
        { 0, 1, 6, 6, 21 },
        { 1, 6, 6, 21, 21 },
        { 6, 6, 21, 21, 21 },
        { 6, 21, 21, 21, 21 },
        { 21, 21, 21, 21, 21 }
    }, [TX_16X16] = {
        { 0, 1, 6, 6, 21 },
        { 1, 6, 6, 21, 21 },
        { 6, 6, 21, 21, 21 },
        { 6, 21, 21, 21, 21 },
        { 21, 21, 21, 21, 21 }
    }, [TX_32X32] = {
        { 0, 1, 6, 6, 21 },
        { 1, 6, 6, 21, 21 },
        { 6, 6, 21, 21, 21 },
        { 6, 21, 21, 21, 21 },
        { 21, 21, 21, 21, 21 }
    }, [TX_64X64] = {
        { 0, 1, 6, 6, 21 },
        { 1, 6, 6, 21, 21 },
        { 6, 6, 21, 21, 21 },
        { 6, 21, 21, 21, 21 },
        { 21, 21, 21, 21, 21 }
    }, [RTX_4X8] = {
        { 0, 11, 11, 11 },
        { 11, 11, 11, 11 },
        { 6, 6, 21, 21 },
        { 6, 21, 21, 21 },
        { 21, 21, 21, 21 }
    }, [RTX_8X4] = {
        { 0, 16, 6, 6, 21 },
        { 16, 16, 6, 21, 21 },
        { 16, 16, 21, 21, 21 },
        { 16, 16, 21, 21, 21 },
    }, [RTX_8X16] = {
        { 0, 11, 11, 11, 11 },
        { 11, 11, 11, 11, 11 },
        { 6, 6, 21, 21, 21 },
        { 6, 21, 21, 21, 21 },
        { 21, 21, 21, 21, 21 }
    }, [RTX_16X8] = {
        { 0, 16, 6, 6, 21 },
        { 16, 16, 6, 21, 21 },
        { 16, 16, 21, 21, 21 },
        { 16, 16, 21, 21, 21 },
        { 16, 16, 21, 21, 21 }
    }, [RTX_16X32] = {
        { 0, 11, 11, 11, 11 },
        { 11, 11, 11, 11, 11 },
        { 6, 6, 21, 21, 21 },
        { 6, 21, 21, 21, 21 },
        { 21, 21, 21, 21, 21 }
    }, [RTX_32X16] = {
        { 0, 16, 6, 6, 21 },
        { 16, 16, 6, 21, 21 },
        { 16, 16, 21, 21, 21 },
        { 16, 16, 21, 21, 21 },
        { 16, 16, 21, 21, 21 }
    }, [RTX_32X64] = {
        { 0, 11, 11, 11, 11 },
        { 11, 11, 11, 11, 11 },
        { 6, 6, 21, 21, 21 },
        { 6, 21, 21, 21, 21 },
        { 21, 21, 21, 21, 21 }
    }, [RTX_64X32] = {
        { 0, 16, 6, 6, 21 },
        { 16, 16, 6, 21, 21 },
        { 16, 16, 21, 21, 21 },
        { 16, 16, 21, 21, 21 },
        { 16, 16, 21, 21, 21 }
    }, [RTX_4X16] = {
        { 0, 11, 11, 11 },
        { 11, 11, 11, 11 },
        { 6, 6, 21, 21 },
        { 6, 21, 21, 21 },
        { 21, 21, 21, 21 }
    }, [RTX_16X4] = {
        { 0, 16, 6, 6, 21 },
        { 16, 16, 6, 21, 21 },
        { 16, 16, 21, 21, 21 },
        { 16, 16, 21, 21, 21 },
    }, [RTX_8X32] = {
        { 0, 11, 11, 11, 11 },
        { 11, 11, 11, 11, 11 },
        { 6, 6, 21, 21, 21 },
        { 6, 21, 21, 21, 21 },
        { 21, 21, 21, 21, 21 }
    }, [RTX_32X8] = {
        { 0, 16, 6, 6, 21 },
        { 16, 16, 6, 21, 21 },
        { 16, 16, 21, 21, 21 },
        { 16, 16, 21, 21, 21 },
        { 16, 16, 21, 21, 21 }
    }, [RTX_16X64] = {
        { 0, 11, 11, 11, 11 },
        { 11, 11, 11, 11, 11 },
        { 6, 6, 21, 21, 21 },
        { 6, 21, 21, 21, 21 },
        { 21, 21, 21, 21, 21 }
    }, [RTX_64X16] = {
        { 0, 16, 6, 6, 21 },
        { 16, 16, 6, 21, 21 },
        { 16, 16, 21, 21, 21 },
        { 16, 16, 21, 21, 21 },
        { 16, 16, 21, 21, 21 }
    }
};

const uint8_t /* enum TxClass */ dav1d_tx_type_class[N_TX_TYPES_PLUS_LL] = {
    [DCT_DCT]           = TX_CLASS_2D,
    [ADST_DCT]          = TX_CLASS_2D,
    [DCT_ADST]          = TX_CLASS_2D,
    [ADST_ADST]         = TX_CLASS_2D,
    [FLIPADST_DCT]      = TX_CLASS_2D,
    [DCT_FLIPADST]      = TX_CLASS_2D,
    [FLIPADST_FLIPADST] = TX_CLASS_2D,
    [ADST_FLIPADST]     = TX_CLASS_2D,
    [FLIPADST_ADST]     = TX_CLASS_2D,
    [IDTX]              = TX_CLASS_2D,
    [V_DCT]             = TX_CLASS_V,
    [H_DCT]             = TX_CLASS_H,
    [V_ADST]            = TX_CLASS_V,
    [H_ADST]            = TX_CLASS_H,
    [V_FLIPADST]        = TX_CLASS_V,
    [H_FLIPADST]        = TX_CLASS_H,
    [WHT_WHT]           = TX_CLASS_2D,
};

const uint8_t /* enum Filter2d */ dav1d_filter_2d[N_FILTERS][N_FILTERS] = {
    [FILTER_8TAP_REGULAR] = {
        [FILTER_8TAP_REGULAR] = FILTER_2D_8TAP_REGULAR,
        [FILTER_8TAP_SHARP]   = FILTER_2D_8TAP_REGULAR_SHARP,
        [FILTER_8TAP_SMOOTH]  = FILTER_2D_8TAP_REGULAR_SMOOTH,
    }, [FILTER_8TAP_SHARP] = {
        [FILTER_8TAP_REGULAR] = FILTER_2D_8TAP_SHARP_REGULAR,
        [FILTER_8TAP_SHARP]   = FILTER_2D_8TAP_SHARP,
        [FILTER_8TAP_SMOOTH]  = FILTER_2D_8TAP_SHARP_SMOOTH,
    }, [FILTER_8TAP_SMOOTH] = {
        [FILTER_8TAP_REGULAR] = FILTER_2D_8TAP_SMOOTH_REGULAR,
        [FILTER_8TAP_SHARP]   = FILTER_2D_8TAP_SMOOTH_SHARP,
        [FILTER_8TAP_SMOOTH]  = FILTER_2D_8TAP_SMOOTH,
    }, [FILTER_BILINEAR] = {
        [FILTER_BILINEAR]     = FILTER_2D_BILINEAR,
    }
};

const uint8_t /* enum FilterMode */ dav1d_filter_dir[N_2D_FILTERS][2] = {
    [FILTER_2D_8TAP_REGULAR]        = { FILTER_8TAP_REGULAR, FILTER_8TAP_REGULAR },
    [FILTER_2D_8TAP_REGULAR_SMOOTH] = { FILTER_8TAP_SMOOTH,  FILTER_8TAP_REGULAR },
    [FILTER_2D_8TAP_REGULAR_SHARP]  = { FILTER_8TAP_SHARP,   FILTER_8TAP_REGULAR },
    [FILTER_2D_8TAP_SHARP_REGULAR]  = { FILTER_8TAP_REGULAR, FILTER_8TAP_SHARP   },
    [FILTER_2D_8TAP_SHARP_SMOOTH]   = { FILTER_8TAP_SMOOTH,  FILTER_8TAP_SHARP   },
    [FILTER_2D_8TAP_SHARP]          = { FILTER_8TAP_SHARP,   FILTER_8TAP_SHARP   },
    [FILTER_2D_8TAP_SMOOTH_REGULAR] = { FILTER_8TAP_REGULAR, FILTER_8TAP_SMOOTH  },
    [FILTER_2D_8TAP_SMOOTH]         = { FILTER_8TAP_SMOOTH,  FILTER_8TAP_SMOOTH  },
    [FILTER_2D_8TAP_SMOOTH_SHARP]   = { FILTER_8TAP_SHARP,   FILTER_8TAP_SMOOTH  },
    [FILTER_2D_BILINEAR]            = { FILTER_BILINEAR,     FILTER_BILINEAR     },
};

const uint8_t dav1d_filter_mode_to_y_mode[5] = {
    DC_PRED, VERT_PRED, HOR_PRED, HOR_DOWN_PRED, DC_PRED
};

const uint8_t dav1d_intra_mode_context[N_INTRA_PRED_MODES] = {
    [DC_PRED]              = 0,
    [VERT_PRED]            = 1,
    [HOR_PRED]             = 2,
    [DIAG_DOWN_LEFT_PRED]  = 3,
    [DIAG_DOWN_RIGHT_PRED] = 4,
    [VERT_RIGHT_PRED]      = 4,
    [HOR_DOWN_PRED]        = 4,
    [HOR_UP_PRED]          = 4,
    [VERT_LEFT_PRED]       = 3,
    [SMOOTH_PRED]          = 0,
    [SMOOTH_V_PRED]        = 1,
    [SMOOTH_H_PRED]        = 2,
    [PAETH_PRED]           = 0,
};

const uint8_t dav1d_wedge_ctx_lut[N_BS_SIZES] = {
    [BS_32x32] = 6,
    [BS_32x16] = 5,
    [BS_32x8]  = 8,
    [BS_16x32] = 4,
    [BS_16x16] = 3,
    [BS_16x8]  = 2,
    [BS_8x32]  = 7,
    [BS_8x16]  = 1,
    [BS_8x8]   = 0,
};

const WarpedMotionParams dav1d_default_wm_params = {
    .type = WM_TYPE_IDENTITY,
    .matrix = {
        0, 0, 1 << 16,
        0, 0, 1 << 16,
    },
    .alpha = 0,
    .beta = 0,
    .gamma = 0,
    .delta = 0,
};

const int16_t dav1d_sgr_params[16][4] = { // r0, r1, e0, e1
    { 2, 1, 140, 3236 }, { 2, 1, 112, 2158 }, { 2, 1, 93, 1618 },
    { 2, 1,  80, 1438 }, { 2, 1,  70, 1295 }, { 2, 1, 58, 1177 },
    { 2, 1,  47, 1079 }, { 2, 1,  37,  996 }, { 2, 1, 30,  925 },
    { 2, 1,  25,  863 }, { 0, 1,  -1, 2589 }, { 0, 1, -1, 1618 },
    { 0, 1,  -1, 1177 }, { 0, 1,  -1,  925 }, { 2, 0, 56,   -1 },
    { 2, 0,  22,   -1 },
};

const int dav1d_sgr_x_by_xplus1[256] = {
  1,   128, 171, 192, 205, 213, 219, 224, 228, 230, 233, 235, 236, 238, 239,
  240, 241, 242, 243, 243, 244, 244, 245, 245, 246, 246, 247, 247, 247, 247,
  248, 248, 248, 248, 249, 249, 249, 249, 249, 250, 250, 250, 250, 250, 250,
  250, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 252, 252, 252, 252,
  252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 253, 253,
  253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253,
  253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 254, 254, 254,
  254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254,
  254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254,
  254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254,
  254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254,
  254, 254, 254, 254, 254, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
  256,
};

const int8_t ALIGN(dav1d_mc_subpel_filters[5][15][8], 8) = {
    [FILTER_8TAP_REGULAR] = {
        {   0,   1,  -3,  63,   4,  -1,   0,   0 },
        {   0,   1,  -5,  61,   9,  -2,   0,   0 },
        {   0,   1,  -6,  58,  14,  -4,   1,   0 },
        {   0,   1,  -7,  55,  19,  -5,   1,   0 },
        {   0,   1,  -7,  51,  24,  -6,   1,   0 },
        {   0,   1,  -8,  47,  29,  -6,   1,   0 },
        {   0,   1,  -7,  42,  33,  -6,   1,   0 },
        {   0,   1,  -7,  38,  38,  -7,   1,   0 },
        {   0,   1,  -6,  33,  42,  -7,   1,   0 },
        {   0,   1,  -6,  29,  47,  -8,   1,   0 },
        {   0,   1,  -6,  24,  51,  -7,   1,   0 },
        {   0,   1,  -5,  19,  55,  -7,   1,   0 },
        {   0,   1,  -4,  14,  58,  -6,   1,   0 },
        {   0,   0,  -2,   9,  61,  -5,   1,   0 },
        {   0,   0,  -1,   4,  63,  -3,   1,   0 }
    }, [FILTER_8TAP_SMOOTH] = {
        {   0,   1,  14,  31,  17,   1,   0,   0 },
        {   0,   0,  13,  31,  18,   2,   0,   0 },
        {   0,   0,  11,  31,  20,   2,   0,   0 },
        {   0,   0,  10,  30,  21,   3,   0,   0 },
        {   0,   0,   9,  29,  22,   4,   0,   0 },
        {   0,   0,   8,  28,  23,   5,   0,   0 },
        {   0,  -1,   8,  27,  24,   6,   0,   0 },
        {   0,  -1,   7,  26,  26,   7,  -1,   0 },
        {   0,   0,   6,  24,  27,   8,  -1,   0 },
        {   0,   0,   5,  23,  28,   8,   0,   0 },
        {   0,   0,   4,  22,  29,   9,   0,   0 },
        {   0,   0,   3,  21,  30,  10,   0,   0 },
        {   0,   0,   2,  20,  31,  11,   0,   0 },
        {   0,   0,   2,  18,  31,  13,   0,   0 },
        {   0,   0,   1,  17,  31,  14,   1,   0 }
    }, [FILTER_8TAP_SHARP] = {
        {  -1,   1,  -3,  63,   4,  -1,   1,   0 },
        {  -1,   3,  -6,  62,   8,  -3,   2,  -1 },
        {  -1,   4,  -9,  60,  13,  -5,   3,  -1 },
        {  -2,   5, -11,  58,  19,  -7,   3,  -1 },
        {  -2,   5, -11,  54,  24,  -9,   4,  -1 },
        {  -2,   5, -12,  50,  30, -10,   4,  -1 },
        {  -2,   5, -12,  45,  35, -11,   5,  -1 },
        {  -2,   6, -12,  40,  40, -12,   6,  -2 },
        {  -1,   5, -11,  35,  45, -12,   5,  -2 },
        {  -1,   4, -10,  30,  50, -12,   5,  -2 },
        {  -1,   4,  -9,  24,  54, -11,   5,  -2 },
        {  -1,   3,  -7,  19,  58, -11,   5,  -2 },
        {  -1,   3,  -5,  13,  60,  -9,   4,  -1 },
        {  -1,   2,  -3,   8,  62,  -6,   3,  -1 },
        {   0,   1,  -1,   4,  63,  -3,   1,  -1 }
    /* width <= 4 */
    }, [3 + FILTER_8TAP_REGULAR] = {
        {   0,   0,  -2,  63,   4,  -1,   0,   0 },
        {   0,   0,  -4,  61,   9,  -2,   0,   0 },
        {   0,   0,  -5,  58,  14,  -3,   0,   0 },
        {   0,   0,  -6,  55,  19,  -4,   0,   0 },
        {   0,   0,  -6,  51,  24,  -5,   0,   0 },
        {   0,   0,  -7,  47,  29,  -5,   0,   0 },
        {   0,   0,  -6,  42,  33,  -5,   0,   0 },
        {   0,   0,  -6,  38,  38,  -6,   0,   0 },
        {   0,   0,  -5,  33,  42,  -6,   0,   0 },
        {   0,   0,  -5,  29,  47,  -7,   0,   0 },
        {   0,   0,  -5,  24,  51,  -6,   0,   0 },
        {   0,   0,  -4,  19,  55,  -6,   0,   0 },
        {   0,   0,  -3,  14,  58,  -5,   0,   0 },
        {   0,   0,  -2,   9,  61,  -4,   0,   0 },
        {   0,   0,  -1,   4,  63,  -2,   0,   0 }
    }, [3 + FILTER_8TAP_SMOOTH] = {
        {   0,   0,  15,  31,  17,   1,   0,   0 },
        {   0,   0,  13,  31,  18,   2,   0,   0 },
        {   0,   0,  11,  31,  20,   2,   0,   0 },
        {   0,   0,  10,  30,  21,   3,   0,   0 },
        {   0,   0,   9,  29,  22,   4,   0,   0 },
        {   0,   0,   8,  28,  23,   5,   0,   0 },
        {   0,   0,   7,  27,  24,   6,   0,   0 },
        {   0,   0,   6,  26,  26,   6,   0,   0 },
        {   0,   0,   6,  24,  27,   7,   0,   0 },
        {   0,   0,   5,  23,  28,   8,   0,   0 },
        {   0,   0,   4,  22,  29,   9,   0,   0 },
        {   0,   0,   3,  21,  30,  10,   0,   0 },
        {   0,   0,   2,  20,  31,  11,   0,   0 },
        {   0,   0,   2,  18,  31,  13,   0,   0 },
        {   0,   0,   1,  17,  31,  15,   0,   0 }
    }
};

const int8_t ALIGN(dav1d_mc_warp_filter[193][8], 8) = {
   // [-1, 0)
    { 0, 127,   0, 0,   0,   1, 0, 0 }, { 0, 127,   0, 0,  -1,   2, 0, 0 },
    { 1, 127,  -1, 0,  -3,   4, 0, 0 }, { 1, 126,  -2, 0,  -4,   6, 1, 0 },
    { 1, 126,  -3, 0,  -5,   8, 1, 0 }, { 1, 125,  -4, 0,  -6,  11, 1, 0 },
    { 1, 124,  -4, 0,  -7,  13, 1, 0 }, { 2, 123,  -5, 0,  -8,  15, 1, 0 },
    { 2, 122,  -6, 0,  -9,  18, 1, 0 }, { 2, 121,  -6, 0, -10,  20, 1, 0 },
    { 2, 120,  -7, 0, -11,  22, 2, 0 }, { 2, 119,  -8, 0, -12,  25, 2, 0 },
    { 3, 117,  -8, 0, -13,  27, 2, 0 }, { 3, 116,  -9, 0, -13,  29, 2, 0 },
    { 3, 114, -10, 0, -14,  32, 3, 0 }, { 3, 113, -10, 0, -15,  35, 2, 0 },
    { 3, 111, -11, 0, -15,  37, 3, 0 }, { 3, 109, -11, 0, -16,  40, 3, 0 },
    { 3, 108, -12, 0, -16,  42, 3, 0 }, { 4, 106, -13, 0, -17,  45, 3, 0 },
    { 4, 104, -13, 0, -17,  47, 3, 0 }, { 4, 102, -14, 0, -17,  50, 3, 0 },
    { 4, 100, -14, 0, -17,  52, 3, 0 }, { 4,  98, -15, 0, -18,  55, 4, 0 },
    { 4,  96, -15, 0, -18,  58, 3, 0 }, { 4,  94, -16, 0, -18,  60, 4, 0 },
    { 4,  91, -16, 0, -18,  63, 4, 0 }, { 4,  89, -16, 0, -18,  65, 4, 0 },
    { 4,  87, -17, 0, -18,  68, 4, 0 }, { 4,  85, -17, 0, -18,  70, 4, 0 },
    { 4,  82, -17, 0, -18,  73, 4, 0 }, { 4,  80, -17, 0, -18,  75, 4, 0 },
    { 4,  78, -18, 0, -18,  78, 4, 0 }, { 4,  75, -18, 0, -17,  80, 4, 0 },
    { 4,  73, -18, 0, -17,  82, 4, 0 }, { 4,  70, -18, 0, -17,  85, 4, 0 },
    { 4,  68, -18, 0, -17,  87, 4, 0 }, { 4,  65, -18, 0, -16,  89, 4, 0 },
    { 4,  63, -18, 0, -16,  91, 4, 0 }, { 4,  60, -18, 0, -16,  94, 4, 0 },
    { 3,  58, -18, 0, -15,  96, 4, 0 }, { 4,  55, -18, 0, -15,  98, 4, 0 },
    { 3,  52, -17, 0, -14, 100, 4, 0 }, { 3,  50, -17, 0, -14, 102, 4, 0 },
    { 3,  47, -17, 0, -13, 104, 4, 0 }, { 3,  45, -17, 0, -13, 106, 4, 0 },
    { 3,  42, -16, 0, -12, 108, 3, 0 }, { 3,  40, -16, 0, -11, 109, 3, 0 },
    { 3,  37, -15, 0, -11, 111, 3, 0 }, { 2,  35, -15, 0, -10, 113, 3, 0 },
    { 3,  32, -14, 0, -10, 114, 3, 0 }, { 2,  29, -13, 0,  -9, 116, 3, 0 },
    { 2,  27, -13, 0,  -8, 117, 3, 0 }, { 2,  25, -12, 0,  -8, 119, 2, 0 },
    { 2,  22, -11, 0,  -7, 120, 2, 0 }, { 1,  20, -10, 0,  -6, 121, 2, 0 },
    { 1,  18,  -9, 0,  -6, 122, 2, 0 }, { 1,  15,  -8, 0,  -5, 123, 2, 0 },
    { 1,  13,  -7, 0,  -4, 124, 1, 0 }, { 1,  11,  -6, 0,  -4, 125, 1, 0 },
    { 1,   8,  -5, 0,  -3, 126, 1, 0 }, { 1,   6,  -4, 0,  -2, 126, 1, 0 },
    { 0,   4,  -3, 0,  -1, 127, 1, 0 }, { 0,   2,  -1, 0,   0, 127, 0, 0 },
    // [0, 1)
    {  0,   0,   1, 0, 0, 127,   0,  0 }, {  0,  -1,   2, 0, 0, 127,   0,  0 },
    {  0,  -3,   4, 1, 1, 127,  -2,  0 }, {  0,  -5,   6, 1, 1, 127,  -2,  0 },
    {  0,  -6,   8, 1, 2, 126,  -3,  0 }, { -1,  -7,  11, 2, 2, 126,  -4, -1 },
    { -1,  -8,  13, 2, 3, 125,  -5, -1 }, { -1, -10,  16, 3, 3, 124,  -6, -1 },
    { -1, -11,  18, 3, 4, 123,  -7, -1 }, { -1, -12,  20, 3, 4, 122,  -7, -1 },
    { -1, -13,  23, 3, 4, 121,  -8, -1 }, { -2, -14,  25, 4, 5, 120,  -9, -1 },
    { -1, -15,  27, 4, 5, 119, -10, -1 }, { -1, -16,  30, 4, 5, 118, -11, -1 },
    { -2, -17,  33, 5, 6, 116, -12, -1 }, { -2, -17,  35, 5, 6, 114, -12, -1 },
    { -2, -18,  38, 5, 6, 113, -13, -1 }, { -2, -19,  41, 6, 7, 111, -14, -2 },
    { -2, -19,  43, 6, 7, 110, -15, -2 }, { -2, -20,  46, 6, 7, 108, -15, -2 },
    { -2, -20,  49, 6, 7, 106, -16, -2 }, { -2, -21,  51, 7, 7, 104, -16, -2 },
    { -2, -21,  54, 7, 7, 102, -17, -2 }, { -2, -21,  56, 7, 8, 100, -18, -2 },
    { -2, -22,  59, 7, 8,  98, -18, -2 }, { -2, -22,  62, 7, 8,  96, -19, -2 },
    { -2, -22,  64, 7, 8,  94, -19, -2 }, { -2, -22,  67, 8, 8,  91, -20, -2 },
    { -2, -22,  69, 8, 8,  89, -20, -2 }, { -2, -22,  72, 8, 8,  87, -21, -2 },
    { -2, -21,  74, 8, 8,  84, -21, -2 }, { -2, -22,  77, 8, 8,  82, -21, -2 },
    { -2, -21,  79, 8, 8,  79, -21, -2 }, { -2, -21,  82, 8, 8,  77, -22, -2 },
    { -2, -21,  84, 8, 8,  74, -21, -2 }, { -2, -21,  87, 8, 8,  72, -22, -2 },
    { -2, -20,  89, 8, 8,  69, -22, -2 }, { -2, -20,  91, 8, 8,  67, -22, -2 },
    { -2, -19,  94, 8, 7,  64, -22, -2 }, { -2, -19,  96, 8, 7,  62, -22, -2 },
    { -2, -18,  98, 8, 7,  59, -22, -2 }, { -2, -18, 100, 8, 7,  56, -21, -2 },
    { -2, -17, 102, 7, 7,  54, -21, -2 }, { -2, -16, 104, 7, 7,  51, -21, -2 },
    { -2, -16, 106, 7, 6,  49, -20, -2 }, { -2, -15, 108, 7, 6,  46, -20, -2 },
    { -2, -15, 110, 7, 6,  43, -19, -2 }, { -2, -14, 111, 7, 6,  41, -19, -2 },
    { -1, -13, 113, 6, 5,  38, -18, -2 }, { -1, -12, 114, 6, 5,  35, -17, -2 },
    { -1, -12, 116, 6, 5,  33, -17, -2 }, { -1, -11, 118, 5, 4,  30, -16, -1 },
    { -1, -10, 119, 5, 4,  27, -15, -1 }, { -1,  -9, 120, 5, 4,  25, -14, -2 },
    { -1,  -8, 121, 4, 3,  23, -13, -1 }, { -1,  -7, 122, 4, 3,  20, -12, -1 },
    { -1,  -7, 123, 4, 3,  18, -11, -1 }, { -1,  -6, 124, 3, 3,  16, -10, -1 },
    { -1,  -5, 125, 3, 2,  13,  -8, -1 }, { -1,  -4, 126, 2, 2,  11,  -7, -1 },
    {  0,  -3, 126, 2, 1,   8,  -6,  0 }, {  0,  -2, 127, 1, 1,   6,  -5,  0 },
    {  0,  -2, 127, 1, 1,   4,  -3,  0 }, {  0,   0, 127, 0, 0,   2,  -1,  0 },
    // [1, 2)
    { 0, 0, 127,   0, 0,   1,   0, 0 }, { 0, 0, 127,   0, 0,  -1,   2, 0 },
    { 0, 1, 127,  -1, 0,  -3,   4, 0 }, { 0, 1, 126,  -2, 0,  -4,   6, 1 },
    { 0, 1, 126,  -3, 0,  -5,   8, 1 }, { 0, 1, 125,  -4, 0,  -6,  11, 1 },
    { 0, 1, 124,  -4, 0,  -7,  13, 1 }, { 0, 2, 123,  -5, 0,  -8,  15, 1 },
    { 0, 2, 122,  -6, 0,  -9,  18, 1 }, { 0, 2, 121,  -6, 0, -10,  20, 1 },
    { 0, 2, 120,  -7, 0, -11,  22, 2 }, { 0, 2, 119,  -8, 0, -12,  25, 2 },
    { 0, 3, 117,  -8, 0, -13,  27, 2 }, { 0, 3, 116,  -9, 0, -13,  29, 2 },
    { 0, 3, 114, -10, 0, -14,  32, 3 }, { 0, 3, 113, -10, 0, -15,  35, 2 },
    { 0, 3, 111, -11, 0, -15,  37, 3 }, { 0, 3, 109, -11, 0, -16,  40, 3 },
    { 0, 3, 108, -12, 0, -16,  42, 3 }, { 0, 4, 106, -13, 0, -17,  45, 3 },
    { 0, 4, 104, -13, 0, -17,  47, 3 }, { 0, 4, 102, -14, 0, -17,  50, 3 },
    { 0, 4, 100, -14, 0, -17,  52, 3 }, { 0, 4,  98, -15, 0, -18,  55, 4 },
    { 0, 4,  96, -15, 0, -18,  58, 3 }, { 0, 4,  94, -16, 0, -18,  60, 4 },
    { 0, 4,  91, -16, 0, -18,  63, 4 }, { 0, 4,  89, -16, 0, -18,  65, 4 },
    { 0, 4,  87, -17, 0, -18,  68, 4 }, { 0, 4,  85, -17, 0, -18,  70, 4 },
    { 0, 4,  82, -17, 0, -18,  73, 4 }, { 0, 4,  80, -17, 0, -18,  75, 4 },
    { 0, 4,  78, -18, 0, -18,  78, 4 }, { 0, 4,  75, -18, 0, -17,  80, 4 },
    { 0, 4,  73, -18, 0, -17,  82, 4 }, { 0, 4,  70, -18, 0, -17,  85, 4 },
    { 0, 4,  68, -18, 0, -17,  87, 4 }, { 0, 4,  65, -18, 0, -16,  89, 4 },
    { 0, 4,  63, -18, 0, -16,  91, 4 }, { 0, 4,  60, -18, 0, -16,  94, 4 },
    { 0, 3,  58, -18, 0, -15,  96, 4 }, { 0, 4,  55, -18, 0, -15,  98, 4 },
    { 0, 3,  52, -17, 0, -14, 100, 4 }, { 0, 3,  50, -17, 0, -14, 102, 4 },
    { 0, 3,  47, -17, 0, -13, 104, 4 }, { 0, 3,  45, -17, 0, -13, 106, 4 },
    { 0, 3,  42, -16, 0, -12, 108, 3 }, { 0, 3,  40, -16, 0, -11, 109, 3 },
    { 0, 3,  37, -15, 0, -11, 111, 3 }, { 0, 2,  35, -15, 0, -10, 113, 3 },
    { 0, 3,  32, -14, 0, -10, 114, 3 }, { 0, 2,  29, -13, 0,  -9, 116, 3 },
    { 0, 2,  27, -13, 0,  -8, 117, 3 }, { 0, 2,  25, -12, 0,  -8, 119, 2 },
    { 0, 2,  22, -11, 0,  -7, 120, 2 }, { 0, 1,  20, -10, 0,  -6, 121, 2 },
    { 0, 1,  18,  -9, 0,  -6, 122, 2 }, { 0, 1,  15,  -8, 0,  -5, 123, 2 },
    { 0, 1,  13,  -7, 0,  -4, 124, 1 }, { 0, 1,  11,  -6, 0,  -4, 125, 1 },
    { 0, 1,   8,  -5, 0,  -3, 126, 1 }, { 0, 1,   6,  -4, 0,  -2, 126, 1 },
    { 0, 0,   4,  -3, 0,  -1, 127, 1 }, { 0, 0,   2,  -1, 0,   0, 127, 0 },
    // dummy (replicate row index 191)
    { 0, 0,   2,  -1, 0,   0, 127, 0 }
};

const uint8_t dav1d_sm_weights[128] = {
    // Unused, because we always offset by bs, which is at least 2.
      0,   0,
    // bs = 2
    255, 128,
    // bs = 4
    255, 149,  85,  64,
    // bs = 8
    255, 197, 146, 105,  73,  50,  37,  32,
    // bs = 16
    255, 225, 196, 170, 145, 123, 102,  84,
     68,  54,  43,  33,  26,  20,  17,  16,
    // bs = 32
    255, 240, 225, 210, 196, 182, 169, 157,
    145, 133, 122, 111, 101,  92,  83,  74,
     66,  59,  52,  45,  39,  34,  29,  25,
     21,  17,  14,  12,  10,   9,   8,   8,
    // bs = 64
    255, 248, 240, 233, 225, 218, 210, 203,
    196, 189, 182, 176, 169, 163, 156, 150,
    144, 138, 133, 127, 121, 116, 111, 106,
    101,  96,  91,  86,  82,  77,  73,  69,
     65,  61,  57,  54,  50,  47,  44,  41,
     38,  35,  32,  29,  27,  25,  22,  20,
     18,  16,  15,  13,  12,  10,   9,   8,
      7,   6,   6,   5,   5,   4,   4,   4
};

const int16_t dav1d_dr_intra_derivative[90] = {
    // More evenly spread out angles and limited to 10-bit
    // Values that are 0 will never be used
       0, 0, 0,       // Approx angle
    1023, 0, 0,       // 3, ...
     547, 0, 0,       // 6, ...
     372, 0, 0, 0, 0, // 9, ...
     273, 0, 0,       // 14, ...
     215, 0, 0,       // 17, ...
     178, 0, 0,       // 20, ...
     151, 0, 0,       // 23, ... (113 & 203 are base angles)
     132, 0, 0,       // 26, ...
     116, 0, 0,       // 29, ...
     102, 0, 0, 0,    // 32, ...
      90, 0, 0,       // 36, ...
      80, 0, 0,       // 39, ...
      71, 0, 0,       // 42, ...
      64, 0, 0,       // 45, ... (45 & 135 are base angles)
      57, 0, 0,       // 48, ...
      51, 0, 0,       // 51, ...
      45, 0, 0, 0,    // 54, ...
      40, 0, 0,       // 58, ...
      35, 0, 0,       // 61, ...
      31, 0, 0,       // 64, ...
      27, 0, 0,       // 67, ... (67 & 157 are base angles)
      23, 0, 0,       // 70, ...
      19, 0, 0,       // 73, ...
      15, 0, 0, 0, 0, // 76, ...
      11, 0, 0,       // 81, ...
       7, 0, 0,       // 84, ...
       3, 0, 0,       // 87, ...
};

const int8_t ALIGN(dav1d_filter_intra_taps[5][64], 16) = {
    {
         -6,  10,  -5,   2,  -3,   1,  -3,   1,
         -4,   6,  -3,   2,  -3,   2,  -3,   1,
          0,   0,  10,   0,   1,  10,   1,   2,
          0,   0,   6,   0,   2,   6,   2,   2,
          0,  12,   0,   9,   0,   7,  10,   5,
          0,   2,   0,   2,   0,   2,   6,   3,
          0,   0,   0,   0,   0,   0,   0,   0,
         12,   0,   9,   0,   7,   0,   5,   0
    }, {
        -10,  16,  -6,   0,  -4,   0,  -2,   0,
        -10,  16,  -6,   0,  -4,   0,  -2,   0,
          0,   0,  16,   0,   0,  16,   0,   0,
          0,   0,  16,   0,   0,  16,   0,   0,
          0,  10,   0,   6,   0,   4,  16,   2,
          0,   0,   0,   0,   0,   0,  16,   0,
          0,   0,   0,   0,   0,   0,   0,   0,
         10,   0,   6,   0,   4,   0,   2,   0
    }, {
         -8,   8,  -8,   0,  -8,   0,  -8,   0,
         -4,   4,  -4,   0,  -4,   0,  -4,   0,
          0,   0,   8,   0,   0,   8,   0,   0,
          0,   0,   4,   0,   0,   4,   0,   0,
          0,  16,   0,  16,   0,  16,   8,  16,
          0,   0,   0,   0,   0,   0,   4,   0,
          0,   0,   0,   0,   0,   0,   0,   0,
         16,   0,  16,   0,  16,   0,  16,   0
    }, {
         -2,   8,  -1,   3,  -1,   2,   0,   1,
         -1,   4,  -1,   3,  -1,   2,  -1,   2,
          0,   0,   8,   0,   3,   8,   2,   3,
          0,   0,   4,   0,   3,   4,   2,   3,
          0,  10,   0,   6,   0,   4,   8,   2,
          0,   3,   0,   4,   0,   4,   4,   3,
          0,   0,   0,   0,   0,   0,   0,   0,
         10,   0,   6,   0,   4,   0,   3,   0
    }, {
        -12,  14, -10,   0,  -9,   0,  -8,   0,
        -10,  12,  -9,   1,  -8,   0,  -7,   0,
          0,   0,  14,   0,   0,  14,   0,   0,
          0,   0,  12,   0,   0,  12,   0,   1,
          0,  14,   0,  12,   0,  11,  14,  10,
          0,   0,   0,   0,   0,   1,  12,   1,
          0,   0,   0,   0,   0,   0,   0,   0,
         14,   0,  12,   0,  11,   0,   9,   0
    }
};
