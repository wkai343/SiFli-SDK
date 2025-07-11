#pragma once

#include "board.h"
#include "sensor.h"

#include "mmc56x3.h"


#ifdef __cplusplus
extern "C" {
#endif

int rt_hw_mmc56x3_init(const char *name, struct rt_sensor_config *cfg);

#ifdef __cplusplus
}
#endif