/*
 * SPDX-FileCopyrightText: 2019-2022 SiFli Technologies(Nanjing) Co., Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef R61581_H
#define R61581_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#ifdef LV_CONF_INCLUDE_SIMPLE
#include "lv_drv_conf.h"
#else
#include "../../lv_drv_conf.h"
#endif

#if USE_R61581

#include <stdint.h>
#include "lvgl/lv_misc/lv_color.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/
void r61581_init(void);
void r61581_flush(int32_t x1, int32_t y1, int32_t x2, int32_t y2, const lv_color_t *color_p);
void r61581_fill(int32_t x1, int32_t y1, int32_t x2, int32_t y2, lv_color_t color);
void r61581_map(int32_t x1, int32_t y1, int32_t x2, int32_t y2, const lv_color_t *color_p);
/**********************
 *      MACROS
 **********************/

#endif /* USE_R61581 */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* R61581_H */

