/*
 * SPDX-FileCopyrightText: 2019-2022 SiFli Technologies(Nanjing) Co., Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "bsp_board.h"

#ifndef LXT_LP_CYCLE
    #define LXT_LP_CYCLE 200
#endif

static uint16_t mpi1_div = 1;
static uint16_t mpi2_div = 1;
static uint16_t mpi3_div = 1;
static uint16_t mpi5_div = 1;

static uint32_t otp_flash_addr = AUTO_FLASH_MAC_ADDRESS;

#define FUNC_BSP_FLASH_DIV_GET(i) \
uint16_t BSP_GetFlash##i##DIV(void) \
{ \
    return mpi##i##_div; \
}\

#define FUNC_BSP_FLASH_DIV_SET(i) \
void BSP_SetFlash##i##DIV(uint16_t div) \
{ \
    mpi##i##_div = div; \
}\

FUNC_BSP_FLASH_DIV_GET(1);
FUNC_BSP_FLASH_DIV_GET(2);
FUNC_BSP_FLASH_DIV_GET(3);
FUNC_BSP_FLASH_DIV_GET(5);

FUNC_BSP_FLASH_DIV_SET(1)
FUNC_BSP_FLASH_DIV_SET(2)
FUNC_BSP_FLASH_DIV_SET(3)
FUNC_BSP_FLASH_DIV_SET(5)

int rt_hw_flash_init(void);
int BSP_Flash_hw3_init();

uint32_t BSP_GetOtpBase(void)
{
    return otp_flash_addr;
}

#ifdef SOC_BF0_HCPU
#define HXT_DELAY_EXP_VAL 1000
static void LRC_init(void)
{
    HAL_PMU_RC10Kconfig();
    HAL_RC_CAL_update_reference_cycle_on_48M(LXT_LP_CYCLE);
    uint32_t ref_cnt = HAL_RC_CAL_get_reference_cycle_on_48M();
    uint32_t cycle_t = (uint32_t)ref_cnt / (48 * LXT_LP_CYCLE);

    HAL_PMU_SET_HXT3_RDY_DELAY((HXT_DELAY_EXP_VAL / cycle_t + 1));
}
#endif
void HAL_PreInit(void)
{
#ifdef SOC_BF0_HCPU

//#ifndef CFG_BOOTLOADER
//    __asm("B .");
//#endif
    //MODIFY_REG(hwp_hpsys_rcc->CFGR, HPSYS_RCC_CFGR_PDIV2_Msk,
    //           MAKE_REG_VAL(5, HPSYS_RCC_CFGR_PDIV2_Msk, HPSYS_RCC_CFGR_PDIV2_Pos));

    // To avoid somebody cancel request.
    HAL_HPAON_EnableXT48();

    HAL_RCC_HCPU_ClockSelect(RCC_CLK_MOD_SYS, RCC_SYSCLK_HXT48);
    HAL_RCC_HCPU_ClockSelect(RCC_CLK_MOD_HP_PERI, RCC_CLK_PERI_HXT48);

    if (PM_STANDBY_BOOT != SystemPowerOnModeGet())
    {
        // Halt LCPU first to avoid LCPU in running state
        HAL_HPAON_WakeCore(CORE_ID_LCPU);
        HAL_RCC_Reset_and_Halt_LCPU(1);

#ifndef USE_ATE_MODE
        // get system/user configure from FLASH OTP
        // TODO: disabled for now as it affects flash5 data
        BSP_System_Config();
#endif

        HAL_PMU_EnableDLL(1);

        HAL_PMU_SWITCH_VRET_LOWER();

        HAL_HPAON_StartGTimer();
#ifndef CFG_BOOTLOADER
#ifdef LXT_DISABLE
        HAL_PMU_LpCLockSelect(PMU_LPCLK_RC10);
#else
        HAL_PMU_EnableXTAL32();
        HAL_PMU_LpCLockSelect(PMU_LPCLK_XT32);
#endif
#endif /* CFG_BOOTLOADER */
        HAL_RCC_LCPU_ClockSelect(RCC_CLK_MOD_LP_PERI, RCC_CLK_PERI_HXT48);

        HAL_LPAON_EnableXT48();
        HAL_RCC_LCPU_ClockSelect(RCC_CLK_MOD_SYS, RCC_SYSCLK_HXT48);
        //  HAL_RCC_LCPU_SetDiv(1, 1, 3);
        HAL_RCC_LCPU_SetDiv(1, 1, 3);
        if (HAL_PMU_LXT_DISABLED())
            LRC_init();
    }

    __HAL_SYSCFG_HPBG_EN();
    __HAL_SYSCFG_HPBG_VDDPSW_EN();
    HAL_Delay_us(2);    /* Wait after enabling HPBG, 2us at least. */

    HAL_RCC_HCPU_EnableDLL1(240000000);
    HAL_RCC_HCPU_ClockSelect(RCC_CLK_MOD_SYS, RCC_SYSCLK_DLL1);
    HAL_RCC_HCPU_SetDiv(1, 2, 5);

    // Reset sysclk used by HAL_Delay_us
    HAL_Delay_us(0);

    mpi1_div = 1;
    mpi2_div = 1;
    mpi3_div = 4;
    mpi5_div = 1;

    /* Init the low level hardware */
    HAL_MspInit();

    HAL_RCC_HCPU_EnableDLL2(288000000);
    HAL_RCC_HCPU_ClockSelect(RCC_CLK_MOD_FLASH1, RCC_CLK_FLASH_DLL2);
    HAL_RCC_HCPU_ClockSelect(RCC_CLK_MOD_FLASH2, RCC_CLK_FLASH_DLL2);

    HAL_RCC_HCPU_EnableDLL3(288000000);
    HAL_RCC_HCPU_ClockSelect(RCC_CLK_MOD_FLASH3, RCC_CLK_FLASH_DLL3);
#if defined (BSP_USING_PSRAM)
    {
        // TODO: rt_psram_init is dependent on RT-Thread. change to RTOS independent.
        extern int rt_psram_init(void);
        rt_psram_init();
    }
#endif

#if defined(BSP_USING_NOR_FLASH3)
    {
        if (PM_STANDBY_BOOT == SystemPowerOnModeGet())
        {
            /* rt_hw_flash_init cannot be called as data has not been restored at this moment,
               so rt_sem_init cannot be called */
            BSP_Flash_hw3_init();
        }
        else
        {
            rt_hw_flash_init();
        }
    }
#endif /* BSP_USING_NOR_FLASH3 */

    HAL_RCC_HCPU_DeepWFIClockSelect(true, RCC_SYSCLK_HXT48);
    HAL_RCC_HCPU_SetDeepWFIDiv(48, 0, 1);

#elif defined(SOC_BF0_LCPU)
    HAL_LPAON_EnableXT48();

    HAL_RCC_LCPU_ClockSelect(RCC_CLK_MOD_SYS, RCC_SYSCLK_HXT48);
    HAL_RCC_LCPU_ClockSelect(RCC_CLK_MOD_LP_PERI, RCC_CLK_PERI_HXT48);

    mpi5_div = 1;

    HAL_RCC_LCPU_SetDiv(1, 1, 3);

#ifdef SF32LB56X
#if defined(BSP_USING_NOR_FLASH) || defined(BSP_USING_SPI_FLASH)
    rt_hw_flash_init();
#endif
#endif /* SF32LB56X */

    if (HAL_PMU_LXT_DISABLED() && PM_STANDBY_BOOT != SystemPowerOnModeGet())
    {
        HAL_RC_CAL_update_reference_cycle_on_48M(LXT_LP_CYCLE);
    }

    HAL_MspInit();

#endif
}

extern void BSP_PIN_Init(void);
// Called in HAL_MspInit
void BSP_IO_Init(void)
{
    BSP_PIN_Init();
    BSP_Power_Up(true);
}

__WEAK void SystemClock_Config(void)
{

}

