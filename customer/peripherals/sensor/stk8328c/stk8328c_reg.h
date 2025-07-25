/*
 * SPDX-FileCopyrightText: 2019-2022 SiFli Technologies(Nanjing) Co., Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __STK8328C_REG_H__
#define __STK8328C_REG_H__

#include <stdint.h>

/* STK832x PSEUDO CODE
 * STK832x SA0/SDO(Pin1) Must be GND or connected to VDD and cannot be float.
 * #define STKI2C_ADDRESS   0x0F  //Pin1 connected to GND
 * #define STKI2C_ADDRESS   0x1F  //Pin1 connected to VDD
 *
 *
 */



#ifdef __cplusplus
extern "C" {
#endif

/* SPI mode needs to open this macro, IIC mode is blocked */
#define STK_SPI_MODE    0

#define STK832x_REG_RANGESEL    0x0F
#define STK832x_RANGE_2G        0x03
#define STK832x_RANGE_4G        0x05
#define STK832x_RANGE_8G        0x08
#define STK832x_RANGE_16G       0x0C

#define STK_REG_POWMODE     0x11
#define STK_SUSPEND_MODE    0x80
#define STK_PWR_MODE_VAL    0x74 // odr 50hz

#define STK832x_SET_ODR_25HZ
//#define   STK832x_SET_ODR_50HZ
//#define   STK832x_SET_ODR_100HZ

#define STK_REG_CHIPID      0x00
#define STK8327_CHIPID_VAL  0x26    /* STK8327 CHIP ID = 0x26 */
#define STK8329_CHIPID_VAL  0x25    /* STK8329&STK8325&STK8328-C CHIP ID = 0x25 */
#define STK832x_CHIPID_VAL  0x23    /* STK8321 or STK8323 CHIP ID = 0x23 */
#define FIFO_FRAME_MAX_CNT  32

#define STK_REG_SOFT_RESET  0x14
#define STK_SOFT_RESET_VAL  0xB6

#define STK_REG_ENG_MODE    0x5E
#define STK_ENG_MODE_VAL    0xC0

#define STK_REG_I2C_WDT     0x34
#define STK_I2C_WDT_VAL     0x04

#define STK_REG_BAND_WIDTH  0x10
#define STK_BAND_WIDTH_VAL  0x0C

#define STK_REG_ES_MODE     0x12
#define STK_ES_MODE_VAL     0x08

#define STK_REG_FIFO_MODE   0x3E
#define STK_FIFO_MODE_VAL   0x20
#define STK_BYPASS_MODE_VAL 0x00
#define STK_STREAM_MODE_VAL 0xC0

#define STK_REG_FIFO_COUNT  0x0C

#define STK_REG_FIFO_DATA   0x3F

typedef int32_t (*stmdev_write_ptr)(void *, uint8_t, uint8_t *, uint16_t);
typedef int32_t (*stmdev_read_ptr)(void *, uint8_t, uint8_t *, uint16_t);

typedef struct
{
    /** Component mandatory fields **/
    stmdev_write_ptr  write_reg;
    stmdev_read_ptr   read_reg;
    /** Customizable optional pointer **/
    void *handle;
} sifdev_sensor_ctx_t;

int32_t stk8328c_read_reg(sifdev_sensor_ctx_t *ctx, uint8_t reg, uint8_t *data, uint16_t len);
int32_t stk8328c_write_reg(sifdev_sensor_ctx_t *ctx, uint8_t reg, uint8_t *data, uint16_t len);
int32_t stk8328c_device_id_get(sifdev_sensor_ctx_t *ctx, uint8_t *buff);
int32_t stk8328c_reset_set(sifdev_sensor_ctx_t *ctx, uint8_t val);
int32_t stk8328c_xl_full_scale_set(sifdev_sensor_ctx_t *ctx, uint8_t val);
int32_t stk8328c_fifo_mode_set(sifdev_sensor_ctx_t *ctx, uint8_t val);
int32_t stk8328c_fifo_count_get(sifdev_sensor_ctx_t *ctx, uint8_t *buff);
int32_t stk8328c_eng_mode_set(sifdev_sensor_ctx_t *ctx, uint8_t val);
int32_t stk8328c_i2c_wdt_set(sifdev_sensor_ctx_t *ctx, uint8_t val);
int32_t stk8328c_band_width_set(sifdev_sensor_ctx_t *ctx, uint8_t val);
int32_t stk8328c_es_mode_set(sifdev_sensor_ctx_t *ctx, uint8_t val);
int32_t stk8328c_power_mode_set(sifdev_sensor_ctx_t *ctx, uint8_t val);
int32_t stk8328c_read_fifo_data(sifdev_sensor_ctx_t *ctx, uint8_t *data, uint16_t len);



#ifdef __cplusplus
}
#endif
#endif /* __SC7A22_REG_H__*/

