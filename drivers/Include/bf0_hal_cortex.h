/*
 * SPDX-FileCopyrightText: 2016 STMicroelectronics
 * SPDX-FileCopyrightText: 2019-2025 SiFli Technologies(Nanjing) Co., Ltd
 *
 * SPDX-License-Identifier: BSD-3-Clause AND Apache-2.0
 */

#ifndef __BF0_HAL_CORTEX_H
#define __BF0_HAL_CORTEX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "bf0_hal_def.h"

/** @addtogroup BF0_HAL_Driver
  * @{
  */

/** @defgroup CORTEX CORTEX-M interface
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup CORTEX_Exported_Types CORTEX Exported Types
  * @{
  */

#if (__MPU_PRESENT == 1)
/** @defgroup CORTEX_MPU_Region_Initialization_Structure_definition MPU Region Initialization Structure Definition
  * @{
  */
typedef struct
{
    uint8_t                Enable;                /*!< Specifies the status of the region.
                                                     This parameter can be a value of @ref CORTEX_MPU_Region_Enable                 */
    uint8_t                Number;                /*!< Specifies the number of the region to protect.
                                                     This parameter can be a value of @ref CORTEX_MPU_Region_Number                 */
    uint32_t               BaseAddress;           /*!< Specifies the base address of the region to protect.                           */
    uint8_t                Size;                  /*!< Specifies the size of the region to protect.
                                                     This parameter can be a value of @ref CORTEX_MPU_Region_Size                   */
    uint8_t                SubRegionDisable;      /*!< Specifies the number of the subregion protection to disable.
                                                     This parameter must be a number between Min_Data = 0x00 and Max_Data = 0xFF    */
    uint8_t                TypeExtField;          /*!< Specifies the TEX field level.
                                                     This parameter can be a value of @ref CORTEX_MPU_TEX_Levels                    */
    uint8_t                AccessPermission;      /*!< Specifies the region access permission type.
                                                     This parameter can be a value of @ref CORTEX_MPU_Region_Permission_Attributes  */
    uint8_t                DisableExec;           /*!< Specifies the instruction access status.
                                                     This parameter can be a value of @ref CORTEX_MPU_Instruction_Access            */
    uint8_t                IsShareable;           /*!< Specifies the shareability status of the protected region.
                                                     This parameter can be a value of @ref CORTEX_MPU_Access_Shareable              */
    uint8_t                IsCacheable;           /*!< Specifies the cacheable status of the region protected.
                                                     This parameter can be a value of @ref CORTEX_MPU_Access_Cacheable              */
    uint8_t                IsBufferable;          /*!< Specifies the bufferable status of the protected region.
                                                     This parameter can be a value of @ref CORTEX_MPU_Access_Bufferable             */
} MPU_Region_InitTypeDef;
/**
  * @}
  */
#endif /* __MPU_PRESENT */

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/

/** @defgroup CORTEX_Exported_Constants CORTEX Exported Constants
  * @{
  */

/** @defgroup CORTEX_Preemption_Priority_Group CORTEX Preemption Priority Group
  * @{
  */
#define NVIC_PRIORITYGROUP_0         ((uint32_t)0x00000007) /*!< 0 bit  for pre-emption priority,
                                                                 4 bits for subpriority */
#define NVIC_PRIORITYGROUP_1         ((uint32_t)0x00000006) /*!< 1 bit  for pre-emption priority,
                                                                 3 bits for subpriority */
#define NVIC_PRIORITYGROUP_2         ((uint32_t)0x00000005) /*!< 2 bits for pre-emption priority,
                                                                 2 bits for subpriority */
#define NVIC_PRIORITYGROUP_3         ((uint32_t)0x00000004) /*!< 3 bits for pre-emption priority,
                                                                 1 bit  for subpriority */
#define NVIC_PRIORITYGROUP_4         ((uint32_t)0x00000003) /*!< 4 bits for pre-emption priority,
                                                                 0 bit  for subpriority */
/**
  * @}
  */

/** @defgroup CORTEX_SysTick_clock_source CORTEX SysTick clock source
  * @{
  */
#define SYSTICK_CLKSOURCE_HCLK_DIV8    ((uint32_t)0x00000000)
#define SYSTICK_CLKSOURCE_HCLK         ((uint32_t)0x00000004)
/**
  * @}
  */

#if (__MPU_PRESENT == 1)
/** @defgroup CORTEX_MPU_HFNMI_PRIVDEF_Control CORTEX MPU HFNMI and PRIVILEGED Access control
  * @{
  */
#define  MPU_HFNMI_PRIVDEF_NONE      ((uint32_t)0x00000000)
#define  MPU_HARDFAULT_NMI           ((uint32_t)0x00000002)
#define  MPU_PRIVILEGED_DEFAULT      ((uint32_t)0x00000004)
#define  MPU_HFNMI_PRIVDEF           ((uint32_t)0x00000006)
/**
  * @}
  */

/** @defgroup CORTEX_MPU_Region_Enable CORTEX MPU Region Enable
  * @{
  */
#define  MPU_REGION_ENABLE           ((uint8_t)0x01)
#define  MPU_REGION_DISABLE          ((uint8_t)0x00)
/**
  * @}
  */

/** @defgroup CORTEX_MPU_Instruction_Access CORTEX MPU Instruction Access
  * @{
  */
#define  MPU_INSTRUCTION_ACCESS_ENABLE      ((uint8_t)0x00)
#define  MPU_INSTRUCTION_ACCESS_DISABLE     ((uint8_t)0x01)
/**
  * @}
  */

/** @defgroup CORTEX_MPU_Access_Shareable CORTEX MPU Instruction Access Shareable
  * @{
  */
#define  MPU_ACCESS_SHAREABLE        ((uint8_t)0x01)
#define  MPU_ACCESS_NOT_SHAREABLE    ((uint8_t)0x00)
/**
  * @}
  */

/** @defgroup CORTEX_MPU_Access_Cacheable CORTEX MPU Instruction Access Cacheable
  * @{
  */
#define  MPU_ACCESS_CACHEABLE        ((uint8_t)0x01)
#define  MPU_ACCESS_NOT_CACHEABLE    ((uint8_t)0x00)
/**
  * @}
  */

/** @defgroup CORTEX_MPU_Access_Bufferable CORTEX MPU Instruction Access Bufferable
  * @{
  */
#define  MPU_ACCESS_BUFFERABLE       ((uint8_t)0x01)
#define  MPU_ACCESS_NOT_BUFFERABLE   ((uint8_t)0x00)
/**
  * @}
  */

/** @defgroup CORTEX_MPU_TEX_Levels CORTEX MPU TEX Levels
  * @{
  */
#define  MPU_TEX_LEVEL0              ((uint8_t)0x00)
#define  MPU_TEX_LEVEL1              ((uint8_t)0x01)
#define  MPU_TEX_LEVEL2              ((uint8_t)0x02)
/**
  * @}
  */

/** @defgroup CORTEX_MPU_Region_Size CORTEX MPU Region Size
  * @{
  */
#define   MPU_REGION_SIZE_32B        ((uint8_t)0x04)
#define   MPU_REGION_SIZE_64B        ((uint8_t)0x05)
#define   MPU_REGION_SIZE_128B       ((uint8_t)0x06)
#define   MPU_REGION_SIZE_256B       ((uint8_t)0x07)
#define   MPU_REGION_SIZE_512B       ((uint8_t)0x08)
#define   MPU_REGION_SIZE_1KB        ((uint8_t)0x09)
#define   MPU_REGION_SIZE_2KB        ((uint8_t)0x0A)
#define   MPU_REGION_SIZE_4KB        ((uint8_t)0x0B)
#define   MPU_REGION_SIZE_8KB        ((uint8_t)0x0C)
#define   MPU_REGION_SIZE_16KB       ((uint8_t)0x0D)
#define   MPU_REGION_SIZE_32KB       ((uint8_t)0x0E)
#define   MPU_REGION_SIZE_64KB       ((uint8_t)0x0F)
#define   MPU_REGION_SIZE_128KB      ((uint8_t)0x10)
#define   MPU_REGION_SIZE_256KB      ((uint8_t)0x11)
#define   MPU_REGION_SIZE_512KB      ((uint8_t)0x12)
#define   MPU_REGION_SIZE_1MB        ((uint8_t)0x13)
#define   MPU_REGION_SIZE_2MB        ((uint8_t)0x14)
#define   MPU_REGION_SIZE_4MB        ((uint8_t)0x15)
#define   MPU_REGION_SIZE_8MB        ((uint8_t)0x16)
#define   MPU_REGION_SIZE_16MB       ((uint8_t)0x17)
#define   MPU_REGION_SIZE_32MB       ((uint8_t)0x18)
#define   MPU_REGION_SIZE_64MB       ((uint8_t)0x19)
#define   MPU_REGION_SIZE_128MB      ((uint8_t)0x1A)
#define   MPU_REGION_SIZE_256MB      ((uint8_t)0x1B)
#define   MPU_REGION_SIZE_512MB      ((uint8_t)0x1C)
#define   MPU_REGION_SIZE_1GB        ((uint8_t)0x1D)
#define   MPU_REGION_SIZE_2GB        ((uint8_t)0x1E)
#define   MPU_REGION_SIZE_4GB        ((uint8_t)0x1F)
/**
  * @}
  */

/** @defgroup CORTEX_MPU_Region_Permission_Attributes CORTEX MPU Region Permission Attributes
  * @{
  */
#define  MPU_REGION_NO_ACCESS        ((uint8_t)0x00)
#define  MPU_REGION_PRIV_RW          ((uint8_t)0x01)
#define  MPU_REGION_PRIV_RW_URO      ((uint8_t)0x02)
#define  MPU_REGION_FULL_ACCESS      ((uint8_t)0x03)
#define  MPU_REGION_PRIV_RO          ((uint8_t)0x05)
#define  MPU_REGION_PRIV_RO_URO      ((uint8_t)0x06)
/**
  * @}
  */

/** @defgroup CORTEX_MPU_Region_Number CORTEX MPU Region Number
  * @{
  */
#define  MPU_REGION_NUMBER0          ((uint8_t)0x00)
#define  MPU_REGION_NUMBER1          ((uint8_t)0x01)
#define  MPU_REGION_NUMBER2          ((uint8_t)0x02)
#define  MPU_REGION_NUMBER3          ((uint8_t)0x03)
#define  MPU_REGION_NUMBER4          ((uint8_t)0x04)
#define  MPU_REGION_NUMBER5          ((uint8_t)0x05)
#define  MPU_REGION_NUMBER6          ((uint8_t)0x06)
#define  MPU_REGION_NUMBER7          ((uint8_t)0x07)
/**
  * @}
  */
#endif /* __MPU_PRESENT */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/** @defgroup CORTEX_Exported_Macros CORTEX Exported Macros
  * @{
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup CORTEX_Exported_Functions CORTEX Exported Functions
  * @{
  */

/** @defgroup CORTEX_Exported_Functions_Group1 Initialization and Configuration functions
  * @brief    Initialization and Configuration functions
  * @{
  */
/* Initialization and Configuration functions *****************************/
/**
  * @brief  Set the priority grouping field (pre-emption priority and subpriority)
  *         using the required unlock sequence.
  * @param  PriorityGroup: The priority grouping bits length.
  *         This parameter can be one of the following values:
  *         @arg NVIC_PRIORITYGROUP_0: 0 bit  for pre-emption priority,
  *                                    4 bits for subpriority
  *         @arg NVIC_PRIORITYGROUP_1: 1 bit  for pre-emption priority,
  *                                    3 bits for subpriority
  *         @arg NVIC_PRIORITYGROUP_2: 2 bits for pre-emption priority,
  *                                    2 bits for subpriority
  *         @arg NVIC_PRIORITYGROUP_3: 3 bits for pre-emption priority,
  *                                    1 bit  for subpriority
  *         @arg NVIC_PRIORITYGROUP_4: 4 bits for pre-emption priority,
  *                                    0 bit  for subpriority
  * @note   When the NVIC_PriorityGroup_0 is selected, IRQ pre-emption is no more possible.
  *         The pending IRQ priority will be managed only by the subpriority.
  * @retval None
  */
void HAL_NVIC_SetPriorityGrouping(uint32_t PriorityGroup);

/**
  * @brief  Set the priority of an interrupt.
  * @param  IRQn: External interrupt number.
  *         This parameter can be an enumerator of IRQn_Type enumeration
  * @param  PreemptPriority: The pre-emption priority for the IRQn channel.
  *         This parameter can be a value between 0 and 15
  *         A lower priority value indicates a higher priority
  * @param  SubPriority: the subpriority level for the IRQ channel.
  *         This parameter can be a value between 0 and 15
  *         A lower priority value indicates a higher priority.
  * @retval None
  */
void HAL_NVIC_SetPriority(IRQn_Type IRQn, uint32_t PreemptPriority, uint32_t SubPriority);

/**
  * @brief  Enable a device specific interrupt in the NVIC interrupt controller.
  * @note   To configure interrupts priority correctly, the NVIC_PriorityGroupConfig()
  *         function should be called before.
  * @param  IRQn External interrupt number.
  *         This parameter can be an enumerator of IRQn_Type enumeration
  * @retval None
  */
void HAL_NVIC_EnableIRQ(IRQn_Type IRQn);

/**
  * @brief  Disable a device specific interrupt in the NVIC interrupt controller.
  * @param  IRQn External interrupt number.
  *         This parameter can be an enumerator of IRQn_Type enumeration
  * @retval None
  */
void HAL_NVIC_DisableIRQ(IRQn_Type IRQn);

/**
  * @brief  Initiate a system reset request to reset the MCU.
  * @retval None
  */
void HAL_NVIC_SystemReset(void);

/**
  * @brief  Initialize the System Timer with interrupt enabled and start the System Tick Timer (SysTick):
  *         Counter is in free running mode to generate periodic interrupts.
  * @param  TicksNumb: Specifies the ticks Number of ticks between two interrupts.
  * @retval status:  - 0  Function succeeded.
  *                  - 1  Function failed.
  */
uint32_t HAL_SYSTICK_Config(uint32_t TicksNumb);

/**
  * @}
  */

/** @defgroup CORTEX_Exported_Functions_Group2 Peripheral Control functions
  * @brief   Cortex control functions
  * @{
  */
/* Peripheral Control functions ***********************************************/
/**
  * @brief  Get the priority grouping field from the NVIC Interrupt Controller.
  * @retval Priority grouping field (SCB->AIRCR [10:8] PRIGROUP field)
  */
uint32_t HAL_NVIC_GetPriorityGrouping(void);

/**
  * @brief  Get the priority of an interrupt.
  * @param  IRQn: External interrupt number.
  *         This parameter can be an enumerator of IRQn_Type enumeration
  * @param   PriorityGroup: the priority grouping bits length.
  *         This parameter can be one of the following values:
  *           @arg NVIC_PRIORITYGROUP_0: 0 bit for pre-emption priority,
  *                                      4 bits for subpriority
  *           @arg NVIC_PRIORITYGROUP_1: 1 bit for pre-emption priority,
  *                                      3 bits for subpriority
  *           @arg NVIC_PRIORITYGROUP_2: 2 bits for pre-emption priority,
  *                                      2 bits for subpriority
  *           @arg NVIC_PRIORITYGROUP_3: 3 bits for pre-emption priority,
  *                                      1 bit for subpriority
  *           @arg NVIC_PRIORITYGROUP_4: 4 bits for pre-emption priority,
  *                                      0 bit for subpriority
  * @param  pPreemptPriority: Pointer on the Preemptive priority value (starting from 0).
  * @param  pSubPriority: Pointer on the Subpriority value (starting from 0).
  * @retval None
  */
void HAL_NVIC_GetPriority(IRQn_Type IRQn, uint32_t PriorityGroup, uint32_t *pPreemptPriority, uint32_t *pSubPriority);


/**
  * @brief  Get Pending Interrupt (read the pending register in the NVIC
  *         and return the pending bit for the specified interrupt).
  * @param  IRQn External interrupt number.
  *          This parameter can be an enumerator of IRQn_Type enumeration
  * @retval status: - 0  Interrupt status is not pending.
  *                 - 1  Interrupt status is pending.
  */
uint32_t HAL_NVIC_GetPendingIRQ(IRQn_Type IRQn);

/**
  * @brief  Set Pending bit of an external interrupt.
  * @param  IRQn External interrupt number
  *         This parameter can be an enumerator of IRQn_Type enumeration
  * @retval None
  */
void HAL_NVIC_SetPendingIRQ(IRQn_Type IRQn);

/**
  * @brief  Clear the pending bit of an external interrupt.
  * @param  IRQn External interrupt number.
  *         This parameter can be an enumerator of IRQn_Type enumeration
  * @retval None
  */
void HAL_NVIC_ClearPendingIRQ(IRQn_Type IRQn);


/**
  * @brief Get active interrupt (read the active register in NVIC and return the active bit).
  * @param IRQn External interrupt number
  *         This parameter can be an enumerator of IRQn_Type enumeration
  * @retval status: - 0  Interrupt status is not pending.
  *                 - 1  Interrupt status is pending.
  */
uint32_t HAL_NVIC_GetActive(IRQn_Type IRQn);

/**
  * @brief Get the enable status for the specified interrupt IRQn.
  * @param IRQn External interrupt number
  *         This parameter can be an enumerator of IRQn_Type enumeration
  * @retval status: - 0  Interrupt is not enabled.
  *                 - 1  Interrupt is enabled.
  */
uint32_t HAL_NVIC_GetEnableIRQ(IRQn_Type IRQn);


/**
  * @brief  Configure the SysTick clock source.
  * @param  CLKSource: specifies the SysTick clock source.
  *          This parameter can be one of the following values:
  *             @arg SYSTICK_CLKSOURCE_HCLK_DIV8: AHB clock divided by 8 selected as SysTick clock source.
  *             @arg SYSTICK_CLKSOURCE_HCLK: AHB clock selected as SysTick clock source.
  * @retval None
  */
void HAL_SYSTICK_CLKSourceConfig(uint32_t CLKSource);

/**
  * @brief  Handle SYSTICK interrupt request.
  * @retval None
  */
void HAL_SYSTICK_IRQHandler(void);

/**
  * @brief  SYSTICK callback.
  * @retval None
  */
void HAL_SYSTICK_Callback(void);

#if (__MPU_PRESENT == 1)

/**
  * @brief  Enable the MPU.
  * @param  MPU_Control: Specifies the control mode of the MPU during hard fault,
  *          NMI, FAULTMASK and privileged accessto the default memory
  *          This parameter can be one of the following values:
  *            @arg MPU_HFNMI_PRIVDEF_NONE
  *            @arg MPU_HARDFAULT_NMI
  *            @arg MPU_PRIVILEGED_DEFAULT
  *            @arg MPU_HFNMI_PRIVDEF
  * @retval None
  */
void HAL_MPU_Enable(uint32_t MPU_Control);

/**
  * @brief  Disable the MPU.
  * @retval None
  */
void HAL_MPU_Disable(void);

/**
  * @brief  Initialize and configure the Region and the memory to be protected.
  * @param  MPU_Init: Pointer to a MPU_Region_InitTypeDef structure that contains
  *                the initialization and configuration information.
  * @retval None
  */
void HAL_MPU_ConfigRegion(MPU_Region_InitTypeDef *MPU_Init);
#endif /* __MPU_PRESENT */
/**
  * @}
  */

/**
  * @}
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/** @defgroup CORTEX_Private_Macros CORTEX Private Macros
  * @{
  */
#define IS_NVIC_PRIORITY_GROUP(GROUP) (((GROUP) == NVIC_PRIORITYGROUP_0) || \
                                       ((GROUP) == NVIC_PRIORITYGROUP_1) || \
                                       ((GROUP) == NVIC_PRIORITYGROUP_2) || \
                                       ((GROUP) == NVIC_PRIORITYGROUP_3) || \
                                       ((GROUP) == NVIC_PRIORITYGROUP_4))

#define IS_NVIC_PREEMPTION_PRIORITY(PRIORITY)  ((PRIORITY) < 0x10)

#define IS_NVIC_SUB_PRIORITY(PRIORITY)         ((PRIORITY) < 0x10)

#define IS_NVIC_DEVICE_IRQ(IRQ)                ((IRQ) >= 0x00)

#define IS_SYSTICK_CLK_SOURCE(SOURCE) (((SOURCE) == SYSTICK_CLKSOURCE_HCLK) || \
                                       ((SOURCE) == SYSTICK_CLKSOURCE_HCLK_DIV8))

#if (__MPU_PRESENT == 1)
#define IS_MPU_REGION_ENABLE(STATE) (((STATE) == MPU_REGION_ENABLE) || \
                                     ((STATE) == MPU_REGION_DISABLE))

#define IS_MPU_INSTRUCTION_ACCESS(STATE) (((STATE) == MPU_INSTRUCTION_ACCESS_ENABLE) || \
                                          ((STATE) == MPU_INSTRUCTION_ACCESS_DISABLE))

#define IS_MPU_ACCESS_SHAREABLE(STATE)   (((STATE) == MPU_ACCESS_SHAREABLE) || \
                                          ((STATE) == MPU_ACCESS_NOT_SHAREABLE))

#define IS_MPU_ACCESS_CACHEABLE(STATE)   (((STATE) == MPU_ACCESS_CACHEABLE) || \
                                          ((STATE) == MPU_ACCESS_NOT_CACHEABLE))

#define IS_MPU_ACCESS_BUFFERABLE(STATE)   (((STATE) == MPU_ACCESS_BUFFERABLE) || \
                                          ((STATE) == MPU_ACCESS_NOT_BUFFERABLE))

#define IS_MPU_TEX_LEVEL(TYPE) (((TYPE) == MPU_TEX_LEVEL0)  || \
                                ((TYPE) == MPU_TEX_LEVEL1)  || \
                                ((TYPE) == MPU_TEX_LEVEL2))

#define IS_MPU_REGION_PERMISSION_ATTRIBUTE(TYPE) (((TYPE) == MPU_REGION_NO_ACCESS)   || \
                                                  ((TYPE) == MPU_REGION_PRIV_RW)     || \
                                                  ((TYPE) == MPU_REGION_PRIV_RW_URO) || \
                                                  ((TYPE) == MPU_REGION_FULL_ACCESS) || \
                                                  ((TYPE) == MPU_REGION_PRIV_RO)     || \
                                                  ((TYPE) == MPU_REGION_PRIV_RO_URO))

#define IS_MPU_REGION_NUMBER(NUMBER)    (((NUMBER) == MPU_REGION_NUMBER0) || \
                                         ((NUMBER) == MPU_REGION_NUMBER1) || \
                                         ((NUMBER) == MPU_REGION_NUMBER2) || \
                                         ((NUMBER) == MPU_REGION_NUMBER3) || \
                                         ((NUMBER) == MPU_REGION_NUMBER4) || \
                                         ((NUMBER) == MPU_REGION_NUMBER5) || \
                                         ((NUMBER) == MPU_REGION_NUMBER6) || \
                                         ((NUMBER) == MPU_REGION_NUMBER7))

#define IS_MPU_REGION_SIZE(SIZE)    (((SIZE) == MPU_REGION_SIZE_32B)   || \
                                     ((SIZE) == MPU_REGION_SIZE_64B)   || \
                                     ((SIZE) == MPU_REGION_SIZE_128B)  || \
                                     ((SIZE) == MPU_REGION_SIZE_256B)  || \
                                     ((SIZE) == MPU_REGION_SIZE_512B)  || \
                                     ((SIZE) == MPU_REGION_SIZE_1KB)   || \
                                     ((SIZE) == MPU_REGION_SIZE_2KB)   || \
                                     ((SIZE) == MPU_REGION_SIZE_4KB)   || \
                                     ((SIZE) == MPU_REGION_SIZE_8KB)   || \
                                     ((SIZE) == MPU_REGION_SIZE_16KB)  || \
                                     ((SIZE) == MPU_REGION_SIZE_32KB)  || \
                                     ((SIZE) == MPU_REGION_SIZE_64KB)  || \
                                     ((SIZE) == MPU_REGION_SIZE_128KB) || \
                                     ((SIZE) == MPU_REGION_SIZE_256KB) || \
                                     ((SIZE) == MPU_REGION_SIZE_512KB) || \
                                     ((SIZE) == MPU_REGION_SIZE_1MB)   || \
                                     ((SIZE) == MPU_REGION_SIZE_2MB)   || \
                                     ((SIZE) == MPU_REGION_SIZE_4MB)   || \
                                     ((SIZE) == MPU_REGION_SIZE_8MB)   || \
                                     ((SIZE) == MPU_REGION_SIZE_16MB)  || \
                                     ((SIZE) == MPU_REGION_SIZE_32MB)  || \
                                     ((SIZE) == MPU_REGION_SIZE_64MB)  || \
                                     ((SIZE) == MPU_REGION_SIZE_128MB) || \
                                     ((SIZE) == MPU_REGION_SIZE_256MB) || \
                                     ((SIZE) == MPU_REGION_SIZE_512MB) || \
                                     ((SIZE) == MPU_REGION_SIZE_1GB)   || \
                                     ((SIZE) == MPU_REGION_SIZE_2GB)   || \
                                     ((SIZE) == MPU_REGION_SIZE_4GB))

#define IS_MPU_SUB_REGION_DISABLE(SUBREGION)  ((SUBREGION) < (uint16_t)0x00FF)
#endif /* __MPU_PRESENT */

/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __BF0_HAL_CORTEX_H */