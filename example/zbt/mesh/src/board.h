/* board.h - Board-specific hooks */

/*
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */


#ifdef __cplusplus
extern "C" {
#endif

void board_output_number(bt_mesh_output_action_t action, uint32_t number);

void board_prov_complete(void);

int board_init(struct k_work *button_work);

void board_led_set(bool val);


#ifdef __cplusplus
}
#endif