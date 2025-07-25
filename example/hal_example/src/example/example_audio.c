/*
 * SPDX-FileCopyrightText: 2019-2022 SiFli Technologies(Nanjing) Co., Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <string.h>
#include <stdlib.h>
#include "utest.h"
#include "board.h"
#include "tc_utils.h"

#ifdef HAL_PDM_MODULE_ENABLED

#include "dma_config.h"

//static I2S_HandleTypeDef I2S_Handle = {0};
static PDM_HandleTypeDef PDM_Handle = {0};
static DMA_HandleTypeDef DMA_Handle = {0};
static volatile uint8_t overFlag = 0;
static IRQn_Type pdm_dma_irq;

void HAL_PDM_RxCpltCallback(PDM_HandleTypeDef *hpdm)
{
    overFlag = 1;
}

#ifndef DMA_SUPPORT_DYN_CHANNEL_ALLOC
void PDM1_L_DMA_IRQHandler(void)
{
    /* enter interrupt */
    ENTER_INTERRUPT();

    //LOG_I("PDM1_L_DMA_IRQHandler");

    HAL_DMA_IRQHandler(PDM_Handle.hdmarx);

    /* leave interrupt */
    LEAVE_INTERRUPT();
}
#endif /* !DMA_SUPPORT_DYN_CHANNEL_ALLOC */

static rt_err_t utest_tc_init(void)
{
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    return RT_EOK;
}

static void bf0_audio_init(PDM_HandleTypeDef *hpdm)
{
    hpdm->Instance = hwp_pdm1;
    hpdm->hdmarx = &DMA_Handle;

    pdm_dma_irq = PDM1_L_DMA_IRQ;
    hpdm->hdmarx->Instance = PDM1_L_DMA_INSTANCE;
    hpdm->hdmarx->Init.Request = PDM1_L_DMA_REQUEST;

    hpdm->Init.Mode = PDM_MODE_LOOP;
    hpdm->Init.Channels = PDM_CHANNEL_LEFT_ONLY;
    hpdm->Init.SampleRate = PDM_SAMPLE_16KHZ;
    hpdm->Init.ChannelDepth = PDM_CHANNEL_DEPTH_16BIT;
    PDM_Handle.RxXferSize = 1024;
}

typedef enum
{
    ARGI_BUF_LENTH_IN_KB,
    ARGI_MAX,
    ARGI_OUTPUT_UART = ARGI_MAX, /*Optional*/
} ARG_IDX;

static void testcase(int argc, char **argv)
{
    rt_device_t p_uart_dev = NULL;
    uint32_t expect_len = 200;
    uint32_t m;

    p_uart_dev = rt_device_find(argv[ARGI_OUTPUT_UART]);
    if (p_uart_dev)
    {
        rt_device_open(p_uart_dev, RT_DEVICE_FLAG_RDWR);
    }
    else
    {
        uassert_true_ret(0);
        goto FINAL_STEP;
    }

    expect_len = strtol(argv[ARGI_BUF_LENTH_IN_KB], 0, 10);

    PDM_Handle.RxXferSize = 1024;
    PDM_Handle.pRxBuffPtr = (uint8_t *) rt_malloc(PDM_Handle.RxXferSize);
    if (PDM_Handle.pRxBuffPtr == NULL)
    {
        uassert_false(RT_TRUE);
        goto FINAL_STEP;
    }
    memset(PDM_Handle.pRxBuffPtr, 0, PDM_Handle.RxXferSize);

    bf0_audio_init(&PDM_Handle);
    PDM_Handle.Init.SampleRate = 8000;
    PDM_Handle.Init.ChannelDepth = 16;
    PDM_Handle.Init.Channels = PDM_CHANNEL_STEREO;
    HAL_PDM_Init(&PDM_Handle);
    HAL_NVIC_EnableIRQ(pdm_dma_irq);

    for (m = 0; m < expect_len; m++)
    {
        overFlag = 0;
        HAL_PDM_Receive_DMA(&PDM_Handle, PDM_Handle.pRxBuffPtr, PDM_Handle.RxXferSize);
        LOG_I("Read data to buffer:%x, len: %d", (uint32_t)PDM_Handle.pRxBuffPtr, PDM_Handle.RxXferSize);

        while (overFlag == 0)
        {

        }

        if (p_uart_dev)
        {
            //LOG_I("Out Audio size=%d\n", len);
            rt_device_write(p_uart_dev, 0, &PDM_Handle.pRxBuffPtr[0], PDM_Handle.RxXferSize);
        }
    }

    HAL_NVIC_DisableIRQ(pdm_dma_irq);
    HAL_PDM_DMAStop(&PDM_Handle);
    HAL_PDM_DeInit(&PDM_Handle);

FINAL_STEP:
    if (PDM_Handle.pRxBuffPtr)
    {
        rt_free(PDM_Handle.pRxBuffPtr);
        PDM_Handle.pRxBuffPtr = NULL;
    }

    if (p_uart_dev)
    {
        rt_device_close(p_uart_dev);
    }

    return;

}

UTEST_TC_EXPORT(testcase, "example_audio", utest_tc_init, utest_tc_cleanup, 10);

#endif

