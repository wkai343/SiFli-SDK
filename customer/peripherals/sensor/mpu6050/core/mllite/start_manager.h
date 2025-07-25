/*
 * SPDX-FileCopyrightText: 2019-2022 SiFli Technologies(Nanjing) Co., Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef INV_START_MANAGER_H__
#define INV_START_MANAGER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "mltypes.h"

/** Max number of start callbacks we can handle. */
#define INV_MAX_START_CB 20

inv_error_t inv_init_start_manager(void);
inv_error_t inv_register_mpl_start_notification(inv_error_t (*start_cb)(void));
inv_error_t inv_execute_mpl_start_notification(void);
inv_error_t inv_unregister_mpl_start_notification(inv_error_t (*start_cb)(void));

#ifdef __cplusplus
}
#endif
#endif  // INV_START_MANAGER_H__
