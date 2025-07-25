/*
 * SPDX-FileCopyrightText: 2016 STMicroelectronics
 * SPDX-FileCopyrightText: 2019-2025 SiFli Technologies(Nanjing) Co., Ltd
 *
 * SPDX-License-Identifier: BSD-3-Clause AND Apache-2.0
 */

#ifndef __BF0_HAL_LPTIM_H
#define __BF0_HAL_LPTIM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "bf0_hal_def.h"

/** @addtogroup BF0_HAL_Driver
  * @{
  */

/** @defgroup LPTIM Low power hardware timer.
  * @brief LPTIM HAL module driver
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup LPTIM_Exported_Types LPTIM Exported Types
  * @{
  */

/** @defgroup LPTIM_WAKEUPTIMER_EXTILINE LPTIM WAKEUP Timer EXTI Line
  * @{
  */
#define LPTIM_EXTI_LINE_WAKEUPTIMER_EVENT  ((uint32_t)EXTI_IMR_MR23)  /*!< External interrupt line 23 Connected to the LPTIM EXTI Line */
/**
  * @}
  */

/**
  * @brief  LPTIM Clock configuration definition
  */
typedef struct
{
    uint32_t Source;         /*!< Selects the clock source.
                           This parameter can be a value of @ref LPTIM_Clock_Source   */

    uint32_t Prescaler;      /*!< Specifies the counter clock Prescaler.
                           This parameter can be a value of @ref LPTIM_Clock_Prescaler */

    uint32_t ExtSource;      /*!< Specifies the external clock source.
                           This parameter can be a value of @ref LPTIM_EX_Clock_Source  */

    uint32_t IntSource;      /*!< Specifies the internal clock source.
                           This parameter can be a value of @ref LPTIM_INT_Clock_Source  */
} LPTIM_ClockConfigTypeDef;

/**
  * @brief  LPTIM Clock configuration definition
  */
typedef struct
{
    uint32_t Polarity;      /*!< Selects the polarity of the active edge for the counter unit
                           if the ULPTIM input is selected.
                           Note: This parameter is used only when Ultra low power clock source is used.
                           Note: If the polarity is configured on 'both edges', an auxiliary clock
                           (one of the Low power oscillator) must be active.
                           This parameter can be a value of @ref LPTIM_Clock_Polarity */

    uint32_t SampleTime;     /*!< Selects the clock sampling time to configure the clock glitch filter.
                           Note: This parameter is used only when Ultra low power clock source is used.
                           This parameter can be a value of @ref LPTIM_Clock_Sample_Time */

} LPTIM_ULPClockConfigTypeDef;

/**
  * @brief  LPTIM Trigger configuration definition
  */
typedef struct
{
    uint32_t Source;        /*!< Selects the Trigger source.
                          This parameter can be a value of @ref LPTIM_Trigger_Source */

    uint32_t ActiveEdge;    /*!< Selects the Trigger active edge.
                          Note: This parameter is used only when an external trigger is used.
                          This parameter can be a value of @ref LPTIM_External_Trigger_Polarity */

    uint32_t SampleTime;    /*!< Selects the trigger sampling time to configure the clock glitch filter.
                          Note: This parameter is used only when an external trigger is used.
                          This parameter can be a value of @ref LPTIM_Trigger_Sample_Time  */
} LPTIM_TriggerConfigTypeDef;

/**
  * @brief  LPTIM Initialization Structure definition
  */
typedef struct
{
    LPTIM_ClockConfigTypeDef     Clock;               /*!< Specifies the clock parameters */

    LPTIM_ULPClockConfigTypeDef  UltraLowPowerClock;  /*!< Specifies the Ultra Low Power clock parameters */

    LPTIM_TriggerConfigTypeDef   Trigger;             /*!< Specifies the Trigger parameters */

    uint32_t                     OutputPolarity;      /*!< Specifies the Output polarity.
                                                    This parameter can be a value of @ref LPTIM_Output_Polarity */

    //uint32_t                     UpdateMode;          /*!< Specifies whether the update of the autorelaod and the compare
    //                                                values is done immediately or after the end of current period.
    //                                                This parameter can be a value of @ref LPTIM_Updating_Mode */

    uint32_t                     CounterSource;       /*!< Specifies whether the counter is incremented each internal event
                                                    or each external event.
                                                    This parameter can be a value of @ref LPTIM_Counter_Source */

} LPTIM_InitTypeDef;

/**
  * @brief  LPTIM Mode Structure definition
  */
typedef enum
{
    HAL_LPTIM_ONESHOT,
    HAL_LPTIM_PERIOD
} HAL_LPTIM_ModeTypeDef;

/**
  * @brief  HAL LPTIM State structure definition
  */
typedef enum __HAL_LPTIM_StateTypeDef
{
    HAL_LPTIM_STATE_RESET            = 0x00U,    /*!< Peripheral not yet initialized or disabled  */
    HAL_LPTIM_STATE_READY            = 0x01U,    /*!< Peripheral Initialized and ready for use    */
    HAL_LPTIM_STATE_BUSY             = 0x02U,    /*!< An internal process is ongoing              */
    HAL_LPTIM_STATE_TIMEOUT          = 0x03U,    /*!< Timeout state                               */
    HAL_LPTIM_STATE_ERROR            = 0x04U     /*!< Internal Process is ongoing                 */
} HAL_LPTIM_StateTypeDef;

/**
  * @brief  LPTIM handle Structure definition
  */
typedef struct
{
    LPTIM_TypeDef              *Instance;         /*!< Register base address     */

    LPTIM_InitTypeDef           Init;             /*!< LPTIM required parameters */

    HAL_StatusTypeDef           Status;           /*!< LPTIM peripheral status   */

    HAL_LockTypeDef             Lock;             /*!< LPTIM locking object      */

    HAL_LPTIM_ModeTypeDef       Mode;             /*!< LPTIM timer mode          */

    __IO  HAL_LPTIM_StateTypeDef   State;            /*!< LPTIM peripheral state    */

} LPTIM_HandleTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup LPTIM_Exported_Constants LPTIM Exported Constants
  * @{
  */

/** @defgroup LPTIM_Clock_Source LPTIM Clock Source
  * @{
  */
#define LPTIM_CLOCKSOURCE_APBCLOCK_LPOSC        0x00U
#define LPTIM_CLOCKSOURCE_ULPTIM                LPTIM_CFGR_CKSEL
/**
  * @}
  */

/** @defgroup LPTIM_EX_Clock_Source LPTIM Clock Source
  * @{
  */
#define LPTIM_EXCLOCKSOURCE_IO                  0x00U
#define LPTIM_EXCLOCKSOURCE_COMP                LPTIM_CFGR_EXTCKSEL
/**
  * @}
  */

/** @defgroup LPTIM_INT_Clock_Source LPTIM Clock Source
  * @{
  */
#define LPTIM_INTCLOCKSOURCE_LPCLOCK            0x00U
#define LPTIM_INTLOCKSOURCE_APBCLOCK            LPTIM_CFGR_INTCKSEL
/**
  * @}
  */


/** @defgroup LPTIM_Clock_Prescaler LPTIM Clock Prescaler
  * @{
  */
#define LPTIM_PRESCALER_DIV1                    0x00000000U
#define LPTIM_PRESCALER_DIV2                    LPTIM_CFGR_PRESC_0
#define LPTIM_PRESCALER_DIV4                    LPTIM_CFGR_PRESC_1
#define LPTIM_PRESCALER_DIV8                    ((uint32_t)(LPTIM_CFGR_PRESC_0 | LPTIM_CFGR_PRESC_1))
#define LPTIM_PRESCALER_DIV16                   LPTIM_CFGR_PRESC_2
#define LPTIM_PRESCALER_DIV32                   ((uint32_t)(LPTIM_CFGR_PRESC_0 | LPTIM_CFGR_PRESC_2))
#define LPTIM_PRESCALER_DIV64                   ((uint32_t)(LPTIM_CFGR_PRESC_1 | LPTIM_CFGR_PRESC_2))
#define LPTIM_PRESCALER_DIV128                  ((uint32_t)LPTIM_CFGR_PRESC)
/**
  * @}
  */

/** @defgroup LPTIM_Output_Polarity LPTIM Output Polarity
  * @{
  */

#define LPTIM_OUTPUTPOLARITY_HIGH               (LPTIM_CFGR_WAVPOL)
#define LPTIM_OUTPUTPOLARITY_LOW                0
/**
  * @}
  */

/** @defgroup LPTIM_Clock_Sample_Time LPTIM Clock Sample Time
  * @{
  */
#define LPTIM_CLOCKSAMPLETIME_DIRECTTRANSITION 0x00000000U
#define LPTIM_CLOCKSAMPLETIME_2TRANSITIONS     LPTIM_CFGR_CKFLT_0
#define LPTIM_CLOCKSAMPLETIME_4TRANSITIONS     LPTIM_CFGR_CKFLT_1
#define LPTIM_CLOCKSAMPLETIME_8TRANSITIONS     LPTIM_CFGR_CKFLT
/**
  * @}
  */

/** @defgroup LPTIM_Clock_Polarity LPTIM Clock Polarity
  * @{
  */

#define LPTIM_CLOCKPOLARITY_RISING                0x00000000U
#define LPTIM_CLOCKPOLARITY_FALLING               LPTIM_CFGR_CKPOL_0
#define LPTIM_CLOCKPOLARITY_RISING_FALLING        LPTIM_CFGR_CKPOL_1
/**
  * @}
  */

/** @defgroup LPTIM_Trigger_Source LPTIM Trigger Source
  * @{
  */
#define LPTIM_TRIGSOURCE_SOFTWARE               0x0000FFFFU
#define LPTIM_TRIGSOURCE_0                      0x00000000U
#define LPTIM_TRIGSOURCE_1                      ((uint32_t)LPTIM_CFGR_TRIGSEL_0)
#define LPTIM_TRIGSOURCE_2                      LPTIM_CFGR_TRIGSEL_1
#define LPTIM_TRIGSOURCE_3                      ((uint32_t)LPTIM_CFGR_TRIGSEL_0 | LPTIM_CFGR_TRIGSEL_1)
#define LPTIM_TRIGSOURCE_4                      LPTIM_CFGR_TRIGSEL_2
#define LPTIM_TRIGSOURCE_5                      ((uint32_t)LPTIM_CFGR_TRIGSEL_0 | LPTIM_CFGR_TRIGSEL_2)
/**
  * @}
  */

/** @defgroup LPTIM_External_Trigger_Polarity LPTIM External Trigger Polarity
  * @{
  */
#define LPTIM_ACTIVEEDGE_RISING                LPTIM_CFGR_TRIGEN_0
#define LPTIM_ACTIVEEDGE_FALLING               LPTIM_CFGR_TRIGEN_1
#define LPTIM_ACTIVEEDGE_RISING_FALLING        LPTIM_CFGR_TRIGEN
/**
  * @}
  */

/** @defgroup LPTIM_Trigger_Sample_Time LPTIM Trigger Sample Time
  * @{
  */
#define LPTIM_TRIGSAMPLETIME_DIRECTTRANSITION  0x00000000U
#define LPTIM_TRIGSAMPLETIME_2TRANSITIONS      LPTIM_CFGR_TRGFLT_0
#define LPTIM_TRIGSAMPLETIME_4TRANSITIONS      LPTIM_CFGR_TRGFLT_1
#define LPTIM_TRIGSAMPLETIME_8TRANSITIONS      LPTIM_CFGR_TRGFLT
/**
  * @}
  */

/** @defgroup LPTIM_Updating_Mode LPTIM Updating Mode
  * @{
  */

#define LPTIM_UPDATE_IMMEDIATE                  0x00000000U
#define LPTIM_UPDATE_ENDOFPERIOD                LPTIM_CFGR_PRELOAD
/**
  * @}
  */

/** @defgroup LPTIM_Counter_Source LPTIM Counter Source
  * @{
  */

#define LPTIM_COUNTERSOURCE_INTERNAL            0x00000000U
#define LPTIM_COUNTERSOURCE_EXTERNAL            LPTIM_CFGR_COUNTMODE
/**
  * @}
  */

/** @defgroup LPTIM_Flag_Definition LPTIM Flag Definition
  * @{
  */
#define LPTIM_FLAG_UE                            LPTIM_ISR_UE
#define LPTIM_FLAG_OF                            LPTIM_ISR_OF
#define LPTIM_FLAG_OC                            LPTIM_ISR_OC
#define LPTIM_FLAG_ET                            LPTIM_ISR_ET
#define LPTIM_FLAG_UEWKUP                        LPTIM_ISR_UEWKUP
#define LPTIM_FLAG_OFWKUP                        LPTIM_ISR_OFWKUP
#define LPTIM_FLAG_OCWKUP                        LPTIM_ISR_OCWKUP

/**
  * @}
  */

/** @defgroup LPTIM_Interrupts_Definition LPTIM Interrupts Definition
  * @{
  */
#define LPTIM_IT_UEIE                            LPTIM_IER_UEIE
#define LPTIM_IT_OFIE                            LPTIM_IER_OFIE
#define LPTIM_IT_OCIE                            LPTIM_IER_OCIE
#define LPTIM_IT_ETIE                            LPTIM_IER_ETIE
#define LPTIM_IT_UEWE                            LPTIM_IER_UEWE
#define LPTIM_IT_OFWE                            LPTIM_IER_OFWE
#define LPTIM_IT_OCWE                            LPTIM_IER_OCWE

/**
  * @}
  */

/** @defgroup LPTIM_Option Register Definition
  * @{
  */
#define LPTIM_OP_PAD_AF                          0x00000000U
#define LPTIM_OP_PAD_PA4                         LPTIM_OR_LPT_IN1_RMP_0
#define LPTIM_OP_PAD_PB9                         LPTIM_OR_LPT_IN1_RMP_1
#define LPTIM_OP_TIM_DAC                         LPTIM_OR_LPT_IN1_RMP

/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup LPTIM_Exported_Macros LPTIM Exported Macros
  * @{
  */

/** @brief Reset LPTIM handle state
  * @param  \__HANDLE__ LPTIM handle
  * @retval None
  */
#define __HAL_LPTIM_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = HAL_LPTIM_STATE_RESET)

/**
  * @brief  Enable/Disable the LPTIM peripheral.
  * @param  \__HANDLE__ LPTIM handle
  * @retval None
  */
#define __HAL_LPTIM_ENABLE(__HANDLE__)   ((__HANDLE__)->Instance->CR |=  (LPTIM_CR_ENABLE))
#define __HAL_LPTIM_DISABLE(__HANDLE__)  ((__HANDLE__)->Instance->CR &=  ~(LPTIM_CR_ENABLE))

/**
  * @brief  Starts the LPTIM peripheral in Continuous or in single mode.
  * @param  \__HANDLE__ DMA handle
  * @retval None
  */
#define __HAL_LPTIM_START_CONTINUOUS(__HANDLE__)  ((__HANDLE__)->Instance->CR |=  LPTIM_CR_CNTSTRT)
#define __HAL_LPTIM_START_SINGLE(__HANDLE__)      ((__HANDLE__)->Instance->CR |=  LPTIM_CR_SNGSTRT)


/**
  * @brief  Reset the LPTIM counter.
  * @param  \__HANDLE__ DMA handle
  * @retval None
  */

#define __HAL_LPTIM_COUNTRST_RESET(__HANDLE__)  ((__HANDLE__)->Instance->CR |= LPTIM_CR_COUNTRST)

/**
  * @brief  Get the LPTIM counter reset status.
  * @param  \__HANDLE__ DMA handle
  * @retval None
  */
#define __HAL_LPTIM_COUNTRST_GET(__HANDLE__)             (((__HANDLE__)->Instance->CR & (LPTIM_CR_COUNTRST_Msk)) >> LPTIM_CR_COUNTRST_Pos)


/**
  * @brief  Writes the passed parameter in the Autoreload register.
  * @param  \__HANDLE__ LPTIM handle
  * @param  \__VALUE__  Autoreload value
  * @retval None
  */
#define __HAL_LPTIM_AUTORELOAD_SET(__HANDLE__ , __VALUE__)  ((__HANDLE__)->Instance->ARR =  (__VALUE__))

/**
  * @brief  Writes the passed parameter in the Compare register.
  * @param  \__HANDLE__ LPTIM handle
  * @param  \__VALUE__  Compare value
  * @retval None
  */
#define __HAL_LPTIM_COMPARE_SET(__HANDLE__ , __VALUE__)     ((__HANDLE__)->Instance->CMP =  (__VALUE__))

/**
  * @brief  Checks whether the specified LPTIM flag is set or not.
  * @param  \__HANDLE__ LPTIM handle
  * @param  \__FLAG__   LPTIM flag to check
  *            This parameter can be a value of:
  *            @arg LPTIM_FLAG_DOWN    : Counter direction change up Flag.
  *            @arg LPTIM_FLAG_UP      : Counter direction change down to up Flag.
  *            @arg LPTIM_FLAG_ARROK   : Autoreload register update OK Flag.
  *            @arg LPTIM_FLAG_CMPOK   : Compare register update OK Flag.
  *            @arg LPTIM_FLAG_ET      : External trigger edge event Flag.
  *            @arg LPTIM_FLAG_ARRM    : Autoreload match Flag.
  *            @arg LPTIM_FLAG_CMPM    : Compare match Flag.
  * @retval The state of the specified flag (SET or RESET).
  */
#define __HAL_LPTIM_GET_FLAG(__HANDLE__, __FLAG__)          (((__HANDLE__)->Instance->ISR &(__FLAG__)) == (__FLAG__))

/**
  * @brief  Clears the specified LPTIM flag.
  * @param  \__HANDLE__ LPTIM handle.
  * @param  \__FLAG__   LPTIM flag to clear.
  *            This parameter can be a value of:
  *            @arg LPTIM_IT_UEIE    : Update event interrupt.
  *            @arg LPTIM_IT_OFIE    : Overflow Interrupt.
  *            @arg LPTIM_IT_OCIE    : Output compare Interrupt.
  *            @arg LPTIM_IT_ETIE    : External trigger valid edge Interrupt.
  *            @arg LPTIM_IT_UEWE    : all Wakeup Interrupt.
  * @retval None.
  */
#define __HAL_LPTIM_CLEAR_FLAG(__HANDLE__, __FLAG__)         ((__HANDLE__)->Instance->ICR  = (__FLAG__))
/**
  * @brief  Enable the specified LPTIM interrupt.
  * @param  \__HANDLE__     LPTIM handle.
  * @param  \__INTERRUPT__  LPTIM interrupt to set.
  *            This parameter can be a value of:
  *            @arg LPTIM_IT_UEIE    : Update event interrupt.
  *            @arg LPTIM_IT_OFIE    : Overflow Interrupt.
  *            @arg LPTIM_IT_OCIE    : Output compare Interrupt.
  *            @arg LPTIM_IT_ETIE    : External trigger valid edge Interrupt.
  *            @arg LPTIM_IT_UEWE    : Update event Wakeup Interrupt.
  *            @arg LPTIM_IT_OFWE    : Overflow Wakeup Interrupt.
  *            @arg LPTIM_IT_OCWE    : Output compare Wakeup Interrupt.

  * @retval None.
  */
#define __HAL_LPTIM_ENABLE_IT(__HANDLE__, __INTERRUPT__)         ((__HANDLE__)->Instance->IER  |= (__INTERRUPT__))

/**
 * @brief  Disable the specified LPTIM interrupt.
 * @param  \__HANDLE__     LPTIM handle.
 * @param  \__INTERRUPT__  LPTIM interrupt to set.
 *            This parameter can be a value of:
 *            @arg LPTIM_IT_UEIE    : Update event interrupt.
 *            @arg LPTIM_IT_OFIE    : Overflow Interrupt.
 *            @arg LPTIM_IT_OCIE    : Output compare Interrupt.
 *            @arg LPTIM_IT_ETIE    : External trigger valid edge Interrupt.
 *            @arg LPTIM_IT_UEWE    : Update event Wakeup Interrupt.
 *            @arg LPTIM_IT_OFWE    : Overflow Wakeup Interrupt.
 *            @arg LPTIM_IT_OCWE    : Output compare Wakeup Interrupt.
 * @retval None.
 */
#define __HAL_LPTIM_DISABLE_IT(__HANDLE__, __INTERRUPT__)         ((__HANDLE__)->Instance->IER  &= (~(__INTERRUPT__)))

/**
* @brief  Checks whether the specified LPTIM interrupt is set or not.
* @param  \__HANDLE__     LPTIM handle.
* @param  \__INTERRUPT__  LPTIM interrupt to check.
*            This parameter can be a value of:
*            @arg LPTIM_IT_UEIE    : Update event interrupt.
*            @arg LPTIM_IT_OFIE    : Overflow Interrupt.
*            @arg LPTIM_IT_OCIE    : Output compare Interrupt.
*            @arg LPTIM_IT_ETIE    : External trigger valid edge Interrupt.
*            @arg LPTIM_IT_UEWE    : Update event Wakeup Interrupt.
*            @arg LPTIM_IT_OFWE    : Overflow Wakeup Interrupt.
*            @arg LPTIM_IT_OCWE    : Output compare Wakeup Interrupt.
* @retval Interrupt status.
*/
#define __HAL_LPTIM_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__) ((((__HANDLE__)->Instance->IER & (__INTERRUPT__)) == (__INTERRUPT__)) ? SET : RESET)


/**
* @brief  Set the specified LPTIM prescaler.
* @param  \__HANDLE__     LPTIM handle.
* @param  \__DIV__        LPTIM prescaler to set.
*            This parameter can be a value of:
*            @arg LPTIM_PRESCALER_DIV1   : Configure the prescaler division factor as 1.
*            @arg LPTIM_PRESCALER_DIV2   : Configure the prescaler division factor as 2.
*            @arg LPTIM_PRESCALER_DIV4   : Configure the prescaler division factor as 4.
*            @arg LPTIM_PRESCALER_DIV8   : Configure the prescaler division factor as 8.
*            @arg LPTIM_PRESCALER_DIV16  : Configure the prescaler division factor as 16.
*            @arg LPTIM_PRESCALER_DIV32  : Configure the prescaler division factor as 32.
*            @arg LPTIM_PRESCALER_DIV64  : Configure the prescaler division factor as 64.
*            @arg LPTIM_PRESCALER_DIV128 : Configure the prescaler division factor as 128.
* @retval None.
*/

#define __HAL_LPTIM_SET_PRESCALER(__HANDLE__, __DIV__) ((__HANDLE__)->Instance->CFGR |= (__DIV__))

/**
* @brief  Clear the LPTIM prescaler register.
* @param  \__HANDLE__     LPTIM handle.
* @param  \__MASK__       LPTIM prescaler mask to clean.
*            This parameter can be a value of:
*            @arg LPTIM_PRESCALER_DIV128 : Clear the prescaler register.
* @retval None.
*/

#define __HAL_LPTIM_CLEAR_PRESCALER(__HANDLE__, __MASK__) ((__HANDLE__)->Instance->CFGR &= ~(__MASK__))



/** @brief  LPTIM Option Register
  * @param  \__HANDLE__ LPTIM handle
  * @param  \__VALUE__ This parameter can be a value of :
  *            @arg  LPTIM_OP_PAD_AF
  *            @arg  LPTIM_OP_PAD_PA4
  *            @arg  LPTIM_OP_PAD_PB9
  *            @arg  LPTIM_OP_TIM_DAC
  * @retval None
  */
#define __HAL_LPTIM_OPTR_CONFIG(__HANDLE__ , __VALUE__)     ((__HANDLE__)->Instance->OR  =  (__VALUE__))

/**
  * @brief  Enable interrupt on the LPTIM Wake-up Timer associated Exti line.
  * @retval None
  */
#define __HAL_LPTIM_WAKEUPTIMER_EXTI_ENABLE_IT()       (EXTI->IMR |= LPTIM_EXTI_LINE_WAKEUPTIMER_EVENT)

/**
  * @brief  Disable interrupt on the LPTIM Wake-up Timer associated Exti line.
  * @retval None
  */
#define __HAL_LPTIM_WAKEUPTIMER_EXTI_DISABLE_IT()      (EXTI->IMR &= ~(LPTIM_EXTI_LINE_WAKEUPTIMER_EVENT))

/**
  * @brief  Enable event on the LPTIM Wake-up Timer associated Exti line.
  * @retval None.
  */
#define __HAL_LPTIM_WAKEUPTIMER_EXTI_ENABLE_EVENT()    (EXTI->EMR |= LPTIM_EXTI_LINE_WAKEUPTIMER_EVENT)

/**
  * @brief  Disable event on the LPTIM Wake-up Timer associated Exti line.
  * @retval None.
  */
#define __HAL_LPTIM_WAKEUPTIMER_EXTI_DISABLE_EVENT()   (EXTI->EMR &= ~(LPTIM_EXTI_LINE_WAKEUPTIMER_EVENT))

/**
  * @brief  Enable falling edge trigger on the LPTIM Wake-up Timer associated Exti line.
  * @retval None.
  */
#define __HAL_LPTIM_WAKEUPTIMER_EXTI_ENABLE_FALLING_EDGE()   (EXTI->FTSR |= LPTIM_EXTI_LINE_WAKEUPTIMER_EVENT)

/**
  * @brief  Disable falling edge trigger on the LPTIM Wake-up Timer associated Exti line.
  * @retval None.
  */
#define __HAL_LPTIM_WAKEUPTIMER_EXTI_DISABLE_FALLING_EDGE()  (EXTI->FTSR &= ~(LPTIM_EXTI_LINE_WAKEUPTIMER_EVENT))

/**
  * @brief  Enable rising edge trigger on the LPTIM Wake-up Timer associated Exti line.
  * @retval None.
  */
#define __HAL_LPTIM_WAKEUPTIMER_EXTI_ENABLE_RISING_EDGE()    (EXTI->RTSR |= LPTIM_EXTI_LINE_WAKEUPTIMER_EVENT)

/**
  * @brief  Disable rising edge trigger on the LPTIM Wake-up Timer associated Exti line.
  * @retval None.
  */
#define __HAL_LPTIM_WAKEUPTIMER_EXTI_DISABLE_RISING_EDGE()   (EXTI->RTSR &= ~(LPTIM_EXTI_LINE_WAKEUPTIMER_EVENT))

/**
  * @brief  Enable rising & falling edge trigger on the LPTIM Wake-up Timer associated Exti line.
  * @retval None.
  */
#define __HAL_LPTIM_WAKEUPTIMER_EXTI_ENABLE_RISING_FALLING_EDGE() do{__HAL_LPTIM_WAKEUPTIMER_EXTI_ENABLE_RISING_EDGE();\
                                                                     __HAL_LPTIM_WAKEUPTIMER_EXTI_ENABLE_FALLING_EDGE();\
                                                                    }while(0U)

/**
  * @brief  Disable rising & falling edge trigger on the LPTIM Wake-up Timer associated Exti line.
  * This parameter can be:
  * @retval None.
  */
#define __HAL_LPTIM_WAKEUPTIMER_EXTI_DISABLE_RISING_FALLING_EDGE() do{__HAL_LPTIM_WAKEUPTIMER_EXTI_DISABLE_RISING_EDGE();\
                                                                      __HAL_LPTIM_WAKEUPTIMER_EXTI_DISABLE_FALLING_EDGE();\
                                                                     }while(0U)

/**
  * @brief Check whether the LPTIM Wake-up Timer associated Exti line interrupt flag is set or not.
  * @retval Line Status.
  */
#define __HAL_LPTIM_WAKEUPTIMER_EXTI_GET_FLAG()              (EXTI->PR & LPTIM_EXTI_LINE_WAKEUPTIMER_EVENT)

/**
  * @brief Clear the LPTIM Wake-up Timer associated Exti line flag.
  * @retval None.
  */
#define __HAL_LPTIM_WAKEUPTIMER_EXTI_CLEAR_FLAG()            (EXTI->PR = LPTIM_EXTI_LINE_WAKEUPTIMER_EVENT)

/**
  * @brief Generate a Software interrupt on the LPTIM Wake-up Timer associated Exti line.
  * @retval None.
  */
#define __HAL_LPTIM_WAKEUPTIMER_EXTI_GENERATE_SWIT()         (EXTI->SWIER |= LPTIM_EXTI_LINE_WAKEUPTIMER_EVENT)

/**
  * @}
  */
/* Exported functions --------------------------------------------------------*/
/** @defgroup LPTIM_Exported_Functions LPTIM Exported Functions
  * @{
  */

/* Initialization/de-initialization functions  ********************************/

/**
  * @brief  Set default setting for the LPTIM
  * @param  hlptim LPTIM handle
  */
void HAL_LPTIM_InitDefault(LPTIM_HandleTypeDef *hlptim);
/**
  * @brief  Initializes the LPTIM according to the specified parameters in the
  *         LPTIM_InitTypeDef and creates the associated handle.
  * @param  hlptim LPTIM handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_LPTIM_Init(LPTIM_HandleTypeDef *hlptim);
/**
  * @brief  DeInitializes the LPTIM peripheral.
  * @param  hlptim LPTIM handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_LPTIM_DeInit(LPTIM_HandleTypeDef *hlptim);

/* MSP functions  *************************************************************/
/**
  * @brief  Initializes the LPTIM MSP.
  * @param  hlptim LPTIM handle
  * @retval None
  */
void HAL_LPTIM_MspInit(LPTIM_HandleTypeDef *hlptim);
/**
  * @brief  DeInitializes LPTIM MSP.
  * @param  hlptim LPTIM handle
  * @retval None
  */
void HAL_LPTIM_MspDeInit(LPTIM_HandleTypeDef *hlptim);

/* Start/Stop operation functions  *********************************************/
/* ################################# PWM Mode ################################*/
/* Blocking mode: Polling */
/**
  * @brief  Starts the LPTIM PWM generation.
  * @param  hlptim  LPTIM handle
  * @param  Period  Specifies the Autoreload value.
  *         This parameter must be a value between 0x000000 and 0xFFFFFF.
  * @param  Pulse  Specifies the compare value.
  *         This parameter must be a value between 0x000000 and 0xFFFFFF.
  * @param  psc_reg Prescale value
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_LPTIM_PWM_Start(LPTIM_HandleTypeDef *hlptim, uint32_t Period, uint32_t Pulse, uint32_t psc_reg);
/**
  * @brief  Stops the LPTIM PWM generation.
  * @param  hlptim  LPTIM handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_LPTIM_PWM_Stop(LPTIM_HandleTypeDef *hlptim);

/* Non-Blocking mode: Interrupt */
/**
  * @brief  Starts the LPTIM PWM generation in interrupt mode.
  * @param  hlptim  LPTIM handle
  * @param  Period  Specifies the Autoreload value.
  *         This parameter must be a value between 0x000000 and 0xFFFFFF
  * @param  Pulse  Specifies the compare value.
  *         This parameter must be a value between 0x000000 and 0xFFFFFF
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_LPTIM_PWM_Start_IT(LPTIM_HandleTypeDef *hlptim, uint32_t Period, uint32_t Pulse);
/**
  * @brief  Stops the LPTIM PWM generation in interrupt mode.
  * @param  hlptim  LPTIM handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_LPTIM_PWM_Stop_IT(LPTIM_HandleTypeDef *hlptim);

/**
  * @brief  Tthe LPTIM PWM set period, pulse, pscaler,  for real-time chang period.
  * @param  hlptim  LPTIM handle
  * @param  Period  Specifies the Autoreload value.
  *         This parameter must be a value between 0x000000 and 0xFFFFFF
  * @param  Pulse  Specifies the compare value.
  *         This parameter must be a value between 0x000000 and 0xFFFFFF
  * @param  psc_reg Prescale value, ref LPTIM_Clock_Prescaler
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_LPTIM_PWM_Set_Period(LPTIM_HandleTypeDef *hlptim, uint32_t Period, uint32_t Pulse, uint32_t psc_reg);


/* ############################# One Pulse Mode ##############################*/
/* Blocking mode: Polling */
/**
  * @brief  Starts the LPTIM One pulse generation.
  * @param  hlptim  LPTIM handle
  * @param  Period  Specifies the Autoreload value.
  *         This parameter must be a value between 0x000000 and 0xFFFFFF.
  * @param  Pulse  Specifies the compare value.
  *         This parameter must be a value between 0x000000 and 0xFFFFFF.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_LPTIM_OnePulse_Start(LPTIM_HandleTypeDef *hlptim, uint32_t Period, uint32_t Pulse);
/**
  * @brief  Stops the LPTIM One pulse generation.
  * @param  hlptim  LPTIM handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_LPTIM_OnePulse_Stop(LPTIM_HandleTypeDef *hlptim);
/* Non-Blocking mode: Interrupt */
/**
  * @brief  Starts the LPTIM One pulse generation in interrupt mode.
  * @param  hlptim  LPTIM handle
  * @param  Period  Specifies the Autoreload value.
  *         This parameter must be a value between 0x000000 and 0xFFFFFF.
  * @param  Pulse  Specifies the compare value.
  *         This parameter must be a value between 0x000000 and 0xFFFFFF.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_LPTIM_OnePulse_Start_IT(LPTIM_HandleTypeDef *hlptim, uint32_t Period, uint32_t Pulse);
/**
  * @brief  Stops the LPTIM One pulse generation in interrupt mode.
  * @param  hlptim  LPTIM handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_LPTIM_OnePulse_Stop_IT(LPTIM_HandleTypeDef *hlptim);

/* ############################## Set once Mode ##############################*/
/* Blocking mode: Polling */
/**
  * @brief  Starts the LPTIM in Set once mode.
  * @param  hlptim  LPTIM handle
  * @param  Period  Specifies the Autoreload value.
  *         This parameter must be a value between 0x000000 and 0xFFFFFF.
  * @param  Pulse  Specifies the compare value.
  *         This parameter must be a value between 0x000000 and 0xFFFFFF.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_LPTIM_SetOnce_Start(LPTIM_HandleTypeDef *hlptim, uint32_t Period, uint32_t Pulse);
/**
  * @brief  Stops the LPTIM Set once mode.
  * @param  hlptim  LPTIM handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_LPTIM_SetOnce_Stop(LPTIM_HandleTypeDef *hlptim);
/* Non-Blocking mode: Interrupt */
/**
  * @brief  Starts the LPTIM Set once mode in interrupt mode.
  * @param  hlptim  LPTIM handle
  * @param  Period  Specifies the Autoreload value.
  *         This parameter must be a value between 0x000000 and 0xFFFFFF.
  * @param  Pulse  Specifies the compare value.
  *         This parameter must be a value between 0x000000 and 0xFFFFFF.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_LPTIM_SetOnce_Start_IT(LPTIM_HandleTypeDef *hlptim, uint32_t Period, uint32_t Pulse);

/**
  * @brief  Stops the LPTIM Set once mode in interrupt mode.
  * @param  hlptim  LPTIM handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_LPTIM_SetOnce_Stop_IT(LPTIM_HandleTypeDef *hlptim);

/* ############################# Time out  Mode ##############################*/
/* Blocking mode: Polling */
/**
  * @brief  Starts the Timeout function. The first trigger event will start the
  *         timer, any successive trigger event will reset the counter and
  *         the timer restarts.
  * @param  hlptim  LPTIM handle
  * @param  Period  Specifies the Autoreload value.
  *         This parameter must be a value between 0x000000 and 0xFFFFFF.
  * @param  Timeout  Specifies the TimeOut value to rest the counter.
  *         This parameter must be a value between 0x000000 and 0xFFFFFF.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_LPTIM_TimeOut_Start(LPTIM_HandleTypeDef *hlptim, uint32_t Period, uint32_t Timeout);
/**
  * @brief  Stops the Timeout function.
  * @param  hlptim  LPTIM handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_LPTIM_TimeOut_Stop(LPTIM_HandleTypeDef *hlptim);
/* Non-Blocking mode: Interrupt */
/**
  * @brief  Starts the Timeout function in interrupt mode. The first trigger
  *         event will start the timer, any successive trigger event will reset
  *         the counter and the timer restarts.
  * @param  hlptim  LPTIM handle
  * @param  Period  Specifies the Autoreload value.
  *         This parameter must be a value between 0x000000 and 0xFFFFFF.
  * @param  Timeout  Specifies the TimeOut value to rest the counter.
  *         This parameter must be a value between 0x000000 and 0xFFFFFF.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_LPTIM_TimeOut_Start_IT(LPTIM_HandleTypeDef *hlptim, uint32_t Period, uint32_t Timeout);
/**
  * @brief  Stops the Timeout function in interrupt mode.
  * @param  hlptim  LPTIM handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_LPTIM_TimeOut_Stop_IT(LPTIM_HandleTypeDef *hlptim);

/* ############################## Counter Mode ###############################*/
/* Blocking mode: Polling */
/**
  * @brief  Starts the Counter mode.
  * @param  hlptim  LPTIM handle
  * @param  Period  Specifies the Autoreload value.
  *         This parameter must be a value between 0x000000 and 0xFFFFFF.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_LPTIM_Counter_Start(LPTIM_HandleTypeDef *hlptim, uint32_t Period);
/**
  * @brief  Stops the Counter mode.
  * @param  hlptim  LPTIM handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_LPTIM_Counter_Stop(LPTIM_HandleTypeDef *hlptim);
/* Non-Blocking mode: Interrupt */
/**
  * @brief  Starts the Counter mode in interrupt mode.
  * @param  hlptim  LPTIM handle
  * @param  Period  Specifies the Autoreload value.
  *         This parameter must be a value between 0x000000 and 0xFFFFFF.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_LPTIM_Counter_Start_IT(LPTIM_HandleTypeDef *hlptim, uint32_t Period);
/**
  * @brief  Stops the Counter mode in interrupt mode.
  * @param  hlptim  LPTIM handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_LPTIM_Counter_Stop_IT(LPTIM_HandleTypeDef *hlptim);

/* Reading operation functions ************************************************/
/**
  * @brief  This function returns the current counter value.
  * @param  hlptim LPTIM handle
  * @retval Counter value.
  */
uint32_t HAL_LPTIM_ReadCounter(LPTIM_HandleTypeDef *hlptim);
/**
  * @brief  This function return the current Autoreload (Period) value.
  * @param  hlptim LPTIM handle
  * @retval Autoreload value.
  */
uint32_t HAL_LPTIM_ReadAutoReload(LPTIM_HandleTypeDef *hlptim);
/**
  * @brief  This function return the current Compare (Pulse) value.
  * @param  hlptim LPTIM handle
  * @retval Compare value.
  */
uint32_t HAL_LPTIM_ReadCompare(LPTIM_HandleTypeDef *hlptim);

/* LPTIM IRQ functions  *******************************************************/
/**
  * @brief  This function handles LPTIM interrupt request.
  * @param  hlptim LPTIM handle
  * @retval None
  */
void HAL_LPTIM_IRQHandler(LPTIM_HandleTypeDef *hlptim);

/* CallBack functions  ********************************************************/
/**
  * @brief  Compare match callback in non blocking mode
  * @param  hlptim  LPTIM handle
  * @retval None
  */
void HAL_LPTIM_CompareMatchCallback(LPTIM_HandleTypeDef *hlptim);
/**
  * @brief  Autoreload match callback in non blocking mode
  * @param  hlptim  LPTIM handle
  * @retval None
  */
void HAL_LPTIM_AutoReloadMatchCallback(LPTIM_HandleTypeDef *hlptim);
/**
  * @brief  Trigger detected callback in non blocking mode
  * @param  hlptim  LPTIM handle
  * @retval None
  */
void HAL_LPTIM_TriggerCallback(LPTIM_HandleTypeDef *hlptim);
/**
  * @brief  Ouput compare callback in non blocking mode
  * @param  hlptim  LPTIM handle
  * @retval None
  */
void HAL_LPTIM_OutCompareCallback(LPTIM_HandleTypeDef *hlptim);
/**
  * @brief  Update event callback in non blocking mode
  * @param  hlptim  LPTIM handle
  * @retval None
  */
void HAL_LPTIM_UpdateEventCallback(LPTIM_HandleTypeDef *hlptim);
/**
  * @brief  Compare write callback in non blocking mode
  * @param  hlptim  LPTIM handle
  * @retval None
  */
void HAL_LPTIM_CompareWriteCallback(LPTIM_HandleTypeDef *hlptim);
/**
  * @brief  Autoreload write callback in non blocking mode
  * @param  hlptim  LPTIM handle
  * @retval None
  */
void HAL_LPTIM_AutoReloadWriteCallback(LPTIM_HandleTypeDef *hlptim);
/**
  * @brief  Autoreload Overflow wakeup callback in non blocking mode
  * @param  hlptim  LPTIM handle
  * @retval None
  */
void HAL_LPTIM_OverFlowWakeUpCallback(LPTIM_HandleTypeDef *hlptim);
/**
  * @brief  Direction counter changed from Down to Up callback in non blocking mode
  * @param  hlptim  LPTIM handle
  * @retval None
  */
void HAL_LPTIM_DirectionUpCallback(LPTIM_HandleTypeDef *hlptim);

/**
  * @brief  Direction counter changed from Up to Down callback in non blocking mode
  * @param  hlptim  LPTIM handle
  * @retval None
  */
void HAL_LPTIM_DirectionDownCallback(LPTIM_HandleTypeDef *hlptim);

/* Peripheral State functions  ************************************************/
/**
  * @brief  Returns the LPTIM state.
  * @param  hlptim LPTIM handle
  * @retval HAL state
  */
HAL_LPTIM_StateTypeDef HAL_LPTIM_GetState(LPTIM_HandleTypeDef *hlptim);

/**
  * @}
  */

/* Private types -------------------------------------------------------------*/
/** @defgroup LPTIM_Private_Types LPTIM Private Types
  * @{
  */

/**
  * @}
  */

/* Private variables ---------------------------------------------------------*/
/** @defgroup LPTIM_Private_Variables LPTIM Private Variables
  * @{
  */

/**
  * @}
  */

/* Private constants ---------------------------------------------------------*/
/** @defgroup LPTIM_Private_Constants LPTIM Private Constants
  * @{
  */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup LPTIM_Private_Macros LPTIM Private Macros
  * @{
  */

#define IS_LPTIM_CLOCK_SOURCE(__SOURCE__)           (((__SOURCE__) == LPTIM_CLOCKSOURCE_ULPTIM) || \
                                                     ((__SOURCE__) == LPTIM_CLOCKSOURCE_APBCLOCK_LPOSC))

#define IS_LPTIM_CLOCK_PRESCALER(__PRESCALER__)     (((__PRESCALER__) ==  LPTIM_PRESCALER_DIV1  ) || \
                                                     ((__PRESCALER__) ==  LPTIM_PRESCALER_DIV2  ) || \
                                                     ((__PRESCALER__) ==  LPTIM_PRESCALER_DIV4  ) || \
                                                     ((__PRESCALER__) ==  LPTIM_PRESCALER_DIV8  ) || \
                                                     ((__PRESCALER__) ==  LPTIM_PRESCALER_DIV16 ) || \
                                                     ((__PRESCALER__) ==  LPTIM_PRESCALER_DIV32 ) || \
                                                     ((__PRESCALER__) ==  LPTIM_PRESCALER_DIV64 ) || \
                                                     ((__PRESCALER__) ==  LPTIM_PRESCALER_DIV128))
#define IS_LPTIM_CLOCK_PRESCALERDIV1(__PRESCALER__) ((__PRESCALER__) ==  LPTIM_PRESCALER_DIV1)

#define IS_LPTIM_OUTPUT_POLARITY(__POLARITY__)      (((__POLARITY__) == LPTIM_OUTPUTPOLARITY_LOW ) || \
                                                     ((__POLARITY__) == LPTIM_OUTPUTPOLARITY_HIGH))

#define IS_LPTIM_CLOCK_SAMPLE_TIME(__SAMPLETIME__)  (((__SAMPLETIME__) == LPTIM_CLOCKSAMPLETIME_DIRECTTRANSITION) || \
                                                     ((__SAMPLETIME__) == LPTIM_CLOCKSAMPLETIME_2TRANSITIONS)     || \
                                                     ((__SAMPLETIME__) == LPTIM_CLOCKSAMPLETIME_4TRANSITIONS)     || \
                                                     ((__SAMPLETIME__) == LPTIM_CLOCKSAMPLETIME_8TRANSITIONS))

#define IS_LPTIM_CLOCK_POLARITY(__POLARITY__)       (((__POLARITY__) == LPTIM_CLOCKPOLARITY_RISING)  || \
                                                     ((__POLARITY__) == LPTIM_CLOCKPOLARITY_FALLING) || \
                                                     ((__POLARITY__) == LPTIM_CLOCKPOLARITY_RISING_FALLING))

#define IS_LPTIM_TRG_SOURCE(__TRIG__)               (((__TRIG__) == LPTIM_TRIGSOURCE_SOFTWARE) || \
                                                     ((__TRIG__) == LPTIM_TRIGSOURCE_0) || \
                                                     ((__TRIG__) == LPTIM_TRIGSOURCE_1) || \
                                                     ((__TRIG__) == LPTIM_TRIGSOURCE_2) || \
                                                     ((__TRIG__) == LPTIM_TRIGSOURCE_3) || \
                                                     ((__TRIG__) == LPTIM_TRIGSOURCE_4) || \
                                                     ((__TRIG__) == LPTIM_TRIGSOURCE_5))

#define IS_LPTIM_EXT_TRG_POLARITY(__POLAR__)        (((__POLAR__) == LPTIM_ACTIVEEDGE_RISING         ) || \
                                                     ((__POLAR__) == LPTIM_ACTIVEEDGE_FALLING        ) || \
                                                     ((__POLAR__) == LPTIM_ACTIVEEDGE_RISING_FALLING ))

#define IS_LPTIM_TRIG_SAMPLE_TIME(__SAMPLETIME__)   (((__SAMPLETIME__) == LPTIM_TRIGSAMPLETIME_DIRECTTRANSITION) || \
                                                     ((__SAMPLETIME__) == LPTIM_TRIGSAMPLETIME_2TRANSITIONS    ) || \
                                                     ((__SAMPLETIME__) == LPTIM_TRIGSAMPLETIME_4TRANSITIONS    ) || \
                                                     ((__SAMPLETIME__) == LPTIM_TRIGSAMPLETIME_8TRANSITIONS    ))

#define IS_LPTIM_COUNTER_SOURCE(__SOURCE__)         (((__SOURCE__) == LPTIM_COUNTERSOURCE_INTERNAL) || \
                                                     ((__SOURCE__) == LPTIM_COUNTERSOURCE_EXTERNAL))

#define IS_LPTIM_AUTORELOAD(__AUTORELOAD__)         ((__AUTORELOAD__) <= LPTIM_CNT_CNT)

#define IS_LPTIM_COMPARE(__COMPARE__)               ((__COMPARE__) <= LPTIM_CMP_CMP)

#define IS_LPTIM_PERIOD(PERIOD)               ((PERIOD) <= LPTIM_CNT_CNT)

#define IS_LPTIM_PULSE(PULSE)                 ((PULSE) <= LPTIM_CMP_CMP)


#define IS_LPTIM_INSTANCE(__INSTANCE__)         (((__INSTANCE__) == LPTIM1)    || \
                                                  ((__INSTANCE__) == LPTIM2)    || \
                                                  ((__INSTANCE__) == LPTIM3))

/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/
/** @defgroup LPTIM_Private_Functions LPTIM Private Functions
  * @{
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */


#ifdef __cplusplus
}
#endif

#endif /* __BF0_HAL_LPTIM_H */