/*
 * SPDX-FileCopyrightText: 2019-2022 SiFli Technologies(Nanjing) Co., Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __PMIC_CONTROLLER_H
#define __PMIC_CONTROLLER_H

#include <stdint.h>
#include <stdbool.h>
#ifdef __cplusplus
extern "C" {
#endif

/**
only called when driver init
*/
void BSP_PMIC_Init(int scl, int sda);
//void BSP_PMIC_Init();
/**
  * @brief  open pmic power to default voltage, controlled by twi, not thread safe, only called before multi-thread os ready
  * @param[in]  out_map using PMIC_OUT_* definition, can set one or more value
  * @param[in]  is_enable enable or disable power select by out_map
  * @param[in]  lvsw1_twi_en, only effect for lvsw1. if true lvsw1 open or close by twi,
                else lvsw1 is controlled by hardware interface EN_LVSW1 pin.
  * @retval no use now
*/
int BSP_PMIC_Control(uint16_t out_map, int is_enable, bool lvsw1_twi_en);

/**
    out_map parameter for BSP_PMIC_Control(out_map， ) and pmic_device_control(uint16_t out_map,)
*/
#define PMIC_OUT_1V8_LVSW100_1      (1<<0)
#define PMIC_OUT_1V8_LVSW100_2      (1<<1)
#define PMIC_OUT_1V8_LVSW100_3      (1<<2)
#define PMIC_OUT_1V8_LVSW100_4      (1<<3)
#define PMIC_OUT_1V8_LVSW100_5      (1<<4)
#define PMIC_OUT_VBAT_HVSW150_1     (1<<5)
#define PMIC_OUT_VBAT_HVSW150_2     (1<<6)
#define PMIC_OUT_LDO28_VOUT         (1<<7)    //LDO4
#define PMIC_OUT_LDO33_VOUT         (1<<8)    //LDO2
#define PMIC_OUT_LDO30_VOUT         (1<<9)    //LDO3
/**
  * @brief  open pmic power to default voltage, controlled by twithread safe, only called after multi-thread os ready
  * @param[in]  out_map using PMIC_OUT_* definition, can set one or more value use PMIC_OUT_* | PMIC_OUT_* 
  * @param[in]  is_enable enable or disable power select by out_map
  * @param[in]  lvsw1_twi_en, only effect for lvsw1. if true lvsw1 open or close by twi,
                else lvsw1 is controlled by hardware interface EN_LVSW1 pin.
  * @retval no use now
*/
int pmic_device_control(uint16_t out_map, int is_enable, bool lvsw1_twi_en);

/*
    following interface is used for detail control for diffrent register,
    some can set to contol by pad_en, not by twi, see register spec,
    all the API at following are not thread safe, must and mutex yourself
    if want to call at diffrent os thread at same time
*/

typedef enum
{
    PMIC_STATUS_BUCK_POWERON,  //buck power finished
    PMIC_STATUS_BUCK_LOWPOWER, //buck voltage in lower power status
    PMIC_STATUS_LDO1_POWERON,  //ldo1 power on finished
    PMIC_STATUS_LDO2_POWERON,  //ldo2 power on finished
    PMIC_STATUS_LDO3_POWERON,  //ldo2 power on finished
    PMIC_STATUS_LDO4_POWERON,  //ldo3 power on finished
} pmic_status_t;
/**
  * @brief  check pmic status coming on  or not
  * @param[in]  which_to_check 
  * @retval return true if status coming
*/
bool pmic_get_status(pmic_status_t which_to_check);

typedef enum 
{
    PMIC_LDO_1,
    PMIC_LDO_2,
    PMIC_LDO_3,
    PMIC_LDO_4,
} pmic_ldo_set_t;

/**
  * @brief open or close ldo by twi, and set ldo voltage if open, PMIC_LDO_1 can't be closed
           voltage is set to 2.65V + 50mv * vol_steps. vol_steps should <= 0x0F
  * @param[in]  ldo  which ldo to open or close 
  * @param[in]  is_open, open or close ldo
  * @param[in]  vol_steps, voltage steps
  * @retval void
*/
void pmic_twi_ldo_set(pmic_ldo_set_t ldo, bool is_open, uint8_t vol_steps);

typedef enum
{
    PMIC_LVSW_1,
    PMIC_LVSW_2,
    PMIC_LVSW_3,
    PMIC_LVSW_4,
    PMIC_LVSW_5,
    PMIC_HVSW_1,
    PMIC_HVSW_2,
} pmic_loadsw_t;
/**
  * @brief open or close loadsw by twi
  * @param[in]  sw  which loadsw to open or close 
  * @param[in]  is_open, open or close loadsw
  * @param[in]  lvsw1_twi_en, only effect for lvsw1. if true lvsw1 open or close by twi,
                else lvsw1 is controlled by hardware EN_LVSW1 pin.
  * @retval void
*/
void pmic_twi_loadsw_set(pmic_loadsw_t sw, bool is_open, bool lvsw1_twi_en);

/**
  * @brief buck volate fine tuning, about (6.0mv * steps) ajust
  * @param[in]  steps should <=0x0F
  * @retval void
*/
void pmic_buck_voltage_fine_tuning(uint8_t steps);

/**
  * @brief pmic twi pin setting on chip
  * @retval void
*/
void pmic_twi_pin_set(bool scl_big_current, bool scl_pulldown_enable, bool sda_big_currrent, bool sda_pulldown_enable);

#ifdef __cplusplus
}
#endif

#endif /* __PMIC_CONTROLLER_H */

