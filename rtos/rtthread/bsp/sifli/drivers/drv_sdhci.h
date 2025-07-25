/*
 * SPDX-FileCopyrightText: 2019-2022 SiFli Technologies(Nanjing) Co., Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __DRV_SDHCI_H__
#define __DRV_SDHCI_H__

#include <rtthread.h>
#include "rtdevice.h"
#include <rthw.h>
#include <drv_common.h>
#include <string.h>
#include <drivers/mmcsd_core.h>
#include <drivers/sdio.h>
#include "board.h"
//#include "bf0_hal_sdhci.h"


#define SDHCI_ADMA_MAX_SIZE         (65536)


#define SDHCI_USER_CONFIG_CLK       (1<<0)
#define SDHCI_USER_CONFIG_DDR       (1<<1)
#define SDHCI_USER_CONFIG_DMA       (1<<2)

#define IS_BUF_ACCROSS_512K_BOUNDARY(addr,size) ((addr&0xFFF80000)!=((addr+size)&0xFFF80000))

typedef enum
{
    SDHCI_SDCARD = 0,
    SDHCI_SDEMMC = 1,
    SDHCI_SDIO = 2,
    SDHCI_TYPE_CNT
} Sdhci_cardType_Enum_T;

typedef struct
{
    uint32_t max_clk;
    uint8_t dma_mode;   //enum SD_DMA_MODE_E
    uint8_t ddr_mode;
    uint8_t sdio_mode;  // Sdhci_cardType_Enum_T
    uint8_t reserved;
} sdhci_user_config_t;


struct sdhci_ops_t;

struct sdhci_host
{
    SDHCI_HandleTypeDef handle;
    /* Data set by hardware interface driver */
    const char      *hw_name;   /* Hardware bus name */
    //int         irq;        /* Device IRQ */

    const struct sdhci_ops_t  *ops;       /* Low level hw interface */

    /* Internal data */
    struct rt_mmcsd_host        *mmc;       /* MMC structure */
    //uint64_t            dma_mask;   /* custom DMA mask */

    unsigned int        version;    /* SDHCI spec. version */
    unsigned int        max_clk;    /* Max possible freq (MHz) */
    unsigned int        timeout_clk;    /* Timeout freq (KHz) */

    unsigned int        clock;      /* Current clock (MHz) */

    struct rt_mmcsd_req *mrq;       /* Current request */
    struct rt_mmcsd_cmd *cmd;       /* Current command */
    struct rt_mmcsd_data        *data;      /* Current data request */
    unsigned char        data_early;  /* Data finished before cmd */

    uint8_t         *adma_desc; /* ADMA descriptor table */
    uint32_t        adma_addr;  /* Mapped ADMA descr. table */

    // add new memb for rtos
    struct rt_event event;
    struct rt_mutex mutex;

    // user config
    uint8_t cfg_flag;
    sdhci_user_config_t usr_cfg;
    rt_uint32_t *org_buf;
    rt_uint32_t *cache_buf;

    uint32_t irq_flag;
};

struct sdhci_ops_t
{
    void (*set_clock)(struct sdhci_host *host, unsigned int clock);

    int (*enable_dma)(struct sdhci_host *host);
    unsigned int (*get_max_clock)(struct sdhci_host *host);
    unsigned int (*get_min_clock)(struct sdhci_host *host);
    unsigned int (*get_timeout_clock)(struct sdhci_host *host);
};

extern struct sdhci_host *sdhci_alloc_host(rt_device_t *dev,
        size_t priv_size);
extern void sdhci_free_host(struct sdhci_host *host);

extern int sdhci_add_host(struct sdhci_host *host);
extern void sdhci_remove_host(struct sdhci_host *host, int dead);

int rt_hw_sdmmc_deinit(uint8_t id);
int rt_hw_sdmmc_init(void);

//#if DRV_DEBUG
const char *sd_cmd_name(int index);
//#endif

#endif /* __DRV_SDHCI_H__ */
