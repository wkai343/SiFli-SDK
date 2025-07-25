/*
 * SPDX-FileCopyrightText: 2019-2022 SiFli Technologies(Nanjing) Co., Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef INV_MOTION_NO_MOTION_H__
#define INV_MOTION_NO_MOTION_H__

#include "mltypes.h"

#ifdef __cplusplus
extern "C" {
#endif

inv_error_t inv_enable_motion_no_motion(void);
inv_error_t inv_disable_motion_no_motion(void);
inv_error_t inv_init_motion_no_motion(void);
inv_error_t inv_start_motion_no_motion(void);
inv_error_t inv_stop_motion_no_motion(void);

inv_error_t inv_set_no_motion_time(long time_ms);

#ifdef __cplusplus
}
#endif

#endif // INV_MOTION_NO_MOTION_H__
