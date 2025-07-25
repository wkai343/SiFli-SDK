/*
 * SPDX-FileCopyrightText: 2019-2022 SiFli Technologies(Nanjing) Co., Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "drv_aes.h"

#ifdef HAL_AES_MODULE_ENABLED
enum
{
    IRQ_MODE,
    POLLING_MODE,
    IRQ_COPY_MODE,
};

static pAESCallback done_cb = NULL;
static rt_sem_t aes_sema = NULL;
static volatile uint8_t aes_api_mode = 0;

static void Lock(void)
{
    RT_ASSERT(aes_sema != NULL);

#ifdef RT_USING_PM
    rt_pm_request(PM_SLEEP_MODE_IDLE);
    rt_pm_hw_device_start();
#endif  /* RT_USING_PM */

    rt_err_t err;
    err = rt_sem_take(aes_sema, rt_tick_from_millisecond(1000));
    RT_ASSERT(RT_EOK == err);
}

static void Unlock(void)
{
    RT_ASSERT(aes_sema != NULL);

    rt_err_t err;
    err = rt_sem_release(aes_sema);
    RT_ASSERT(RT_EOK == err);

#ifdef RT_USING_PM
    rt_pm_release(PM_SLEEP_MODE_IDLE);
    rt_pm_hw_device_stop();
#endif  /* RT_USING_PM */

}

void AES_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    if (IRQ_COPY_MODE == aes_api_mode)
    {
        HAL_AES_IRQHandler_ns();
        HAL_HASH_IRQHandler_ns();
    }
    else
    {
        HAL_AES_IRQHandler();
        HAL_HASH_IRQHandler();
    }
    if (0 == aes_sema->value)
    {
        /* not locked before as HAL API is used directly */
        Unlock();
    }

    /* leave interrupt */
    rt_interrupt_leave();
}

static rt_err_t aes_start(uint8_t api, uint8_t enc, AES_KeyTypeDef *cfg, AES_IOTypeDef *data, pAESCallback cb)
{
    HAL_StatusTypeDef res;

    Lock();
    aes_api_mode = api;
    if (IRQ_COPY_MODE == api)
        res = HAL_AES_init_ns(cfg->key, cfg->key_size, cfg->iv, cfg->mode);    // Key and IV must be 4 bytes aligned.
    else
        res = HAL_AES_init(cfg->key, cfg->key_size, cfg->iv, cfg->mode);    // Key and IV must be 4 bytes aligned.
    if (HAL_OK == res)
    {
        if (POLLING_MODE == api)
        {
            res = HAL_AES_run(enc, data->in_data, data->out_data, data->size);
            Unlock();
        }
        else
        {
            NVIC_EnableIRQ(AES_IRQn);
            HAL_NVIC_SetPriority(AES_IRQn, 5, 0);
            if (IRQ_COPY_MODE == api)
                HAL_AES_Regist_IT_cb_ns(cb);
            else
                HAL_AES_Regist_IT_cb(cb);
            if (IRQ_MODE == api)
                res = HAL_AES_run_IT(enc, data->in_data, data->out_data, data->size);
            else
                res = HAL_AES_copy_IT_ns(data->in_data, data->out_data, data->size);

            if (HAL_OK != res) Unlock();
        }
    }
    else
    {
        Unlock();
    }

    return HAL_OK == res ?  RT_EOK : (rt_err_t)res;
}

rt_err_t drv_aes_enc_async(AES_KeyTypeDef *cfg, AES_IOTypeDef *data, pAESCallback cb)
{
    return aes_start(IRQ_MODE, AES_ENC, cfg, data, cb);
}
rt_err_t drv_aes_dec_async(AES_KeyTypeDef *cfg, AES_IOTypeDef *data, pAESCallback cb)
{
    return aes_start(IRQ_MODE, AES_DEC, cfg, data, cb);
}
rt_err_t drv_aes_enc_sync(AES_KeyTypeDef *cfg, AES_IOTypeDef *data)
{
    return aes_start(POLLING_MODE, AES_ENC, cfg, data, NULL);
}
rt_err_t drv_aes_dec_sync(AES_KeyTypeDef *cfg, AES_IOTypeDef *data)
{
    return aes_start(POLLING_MODE, AES_DEC, cfg, data, NULL);
}

rt_err_t drv_aes_copy_async(AES_IOTypeDef *data, pAESCallback cb)
{
    //Key and iv will not be used in copy mode
    AES_KeyTypeDef cfg =
    {
        .key = NULL,
        .key_size = 32,
        .iv = NULL,
        .mode = AES_MODE_ECB,
    };

    return aes_start(IRQ_COPY_MODE, AES_ENC, &cfg, data, cb);
}

static int AES_Init(void)
{
    if (!aes_sema)
    {
        aes_sema = rt_sem_create("aes_drv", 1, 0);
        RT_ASSERT(aes_sema != NULL);
    }
    return 0;
}

INIT_BOARD_EXPORT(AES_Init);
#endif /* HAL_AES_MODULE_ENABLED */

