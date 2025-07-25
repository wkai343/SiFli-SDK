/*
 * SPDX-FileCopyrightText: 2019-2022 SiFli Technologies(Nanjing) Co., Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <string.h>
#include <stdlib.h>
#include "utest.h"
#include "bf0_hal.h"
#include "tc_utils.h"

#ifdef SOC_SF32LB52X
    #define EXAMPLE_EXTDMA_COMPRESS_ENABLE 0
#else
    #define EXAMPLE_EXTDMA_COMPRESS_ENABLE 1
#endif
/*
    This example demo:
    If EXAMPLE_EXTDMA_COMPRESS_ENABLE is 0:

        1. Compress&copy an image from FLASH to PSRAM
        2. Done.

     else

        1. Copy an image from FLASH to PSRAM
        2. Compare data on flash with data on PSRAM
*/

static EXT_DMA_HandleTypeDef DMA_Handle = {0};

void EXTDMA_IRQHandler(void)
{
    /* enter interrupt */
    ENTER_INTERRUPT();

    HAL_EXT_DMA_IRQHandler(&DMA_Handle);

    /* leave interrupt */
    LEAVE_INTERRUPT();
}

static void dma_done_cb()
{
    LOG_I("EXTDMA Done.");
}

static void dma_err_cb()
{
    LOG_I("EXTDMA Error!");
}

static void testcase(int argc, char **argv)
{
#define FRAMEBUFFER_HOR_PIXELS  100
#define FRAMEBUFFER_VER_PIXELS  100
#define FRAMEBUFFER_BYTES_PER_PIXEL  3

    HAL_StatusTypeDef res = HAL_OK;
    uint32_t len;

    uint32_t src, dst, len_in_words;

#ifdef SOC_SF32LB55X
    src = 0x10000000;
    dst = 0x60020000;
#elif defined(SOC_SF32LB56X)
    src = 0x10000000;
    dst = 0x60200000;
#elif defined(SOC_SF32LB52X)
    src = 0x10100000;
    dst = 0x60200000;
#else
    src = 0x10000000;
    dst = 0x62200000;
#endif
    len_in_words = FRAMEBUFFER_HOR_PIXELS *  FRAMEBUFFER_VER_PIXELS * FRAMEBUFFER_BYTES_PER_PIXEL / 4;

    /*Data copy config    */
    DMA_Handle.Init.SrcInc = HAL_EXT_DMA_SRC_INC | HAL_EXT_DMA_SRC_BURST16; //Source address auto-increment and burst 16
    DMA_Handle.Init.DstInc = HAL_EXT_DMA_DST_INC | HAL_EXT_DMA_DST_BURST16; //Dest address auto-increment and burst 16

#if (1 == EXAMPLE_EXTDMA_COMPRESS_ENABLE)
    /*Compression config  */
    DMA_Handle.Init.cmpr_en = true;
    DMA_Handle.Init.src_format = EXTDMA_CMPRCR_SRCFMT_RGB888;
    DMA_Handle.Init.cmpr_rate = 1;
    DMA_Handle.Init.col_num = FRAMEBUFFER_HOR_PIXELS;
    DMA_Handle.Init.row_num = FRAMEBUFFER_VER_PIXELS;

#else
    DMA_Handle.Init.cmpr_en = false;
#endif

    HAL_EXT_DMA_Init(&DMA_Handle);

    /* NVIC configuration for DMA transfer complete interrupt */
    HAL_NVIC_SetPriority(EXTDMA_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTDMA_IRQn);

    /* Regist EXTDMA xfer complete&error callback function */
    HAL_EXT_DMA_RegisterCallback(&DMA_Handle, HAL_EXT_DMA_XFER_CPLT_CB_ID, dma_done_cb);
    HAL_EXT_DMA_RegisterCallback(&DMA_Handle, HAL_EXT_DMA_XFER_ERROR_CB_ID, dma_err_cb);

    LOG_I("exdma  src:%x dst:%x len: %d words", src, dst, len_in_words);

    /*Start EXTDMA transfer*/
    HAL_EXT_DMA_Start_IT(&DMA_Handle, src, dst, len_in_words);

    rt_thread_mdelay(1000);

#if (1 == EXAMPLE_EXTDMA_COMPRESS_ENABLE)

    LOG_I("EXTDMA compress done, use lcdc to decompress and display framebuffer 0x%x", dst);

#else

    /* Destination data should match with source input  */
    if (memcmp((void *)src, (void *)dst, len_in_words * 4) == 0)
        LOG_I("EXTDMA src&dst matched.");
    else
        LOG_I("EXTDMA Error: src&dst NOT matched.");

#endif
}

UTEST_TC_EXPORT(testcase, "example_extdma", NULL, NULL, 10);

