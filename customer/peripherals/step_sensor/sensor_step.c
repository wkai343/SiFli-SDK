/*
 * SPDX-FileCopyrightText: 2019-2022 SiFli Technologies(Nanjing) Co., Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifdef STEP_USING_VIRTUAL

#include "sensor_step.h"
#include "step_wraper.h"
#define DBG_TAG "sensor.step"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>
#include "sensor.h"

static struct virt_step_device *step_dev;

static rt_err_t _step_init(void)
{
    if (virt_step_init() == 0)
    {
        step_dev = rt_calloc(1, sizeof(struct virt_step_device));
        if (step_dev == RT_NULL)
        {
            return RT_ENOMEM;
        }
        step_dev->bus = NULL;
        step_dev->i2c_addr = 0XFF;
        step_dev->id = 0XFF;
        //step_dev->config;
    }

    return RT_EOK;
}

static rt_err_t _step_set_range(rt_sensor_t sensor, rt_int32_t range)
{
    return RT_EOK;
}

static rt_err_t _step_set_mode(rt_sensor_t sensor, rt_uint8_t mode)
{
    if (mode == RT_SENSOR_MODE_POLLING)
    {
        LOG_D("set mode to POLLING");
    }
    else
    {
        LOG_D("Unsupported mode, code is %d", mode);
        return -RT_ERROR;
    }
    return RT_EOK;
}

static rt_err_t _step_set_power(rt_sensor_t sensor, rt_uint8_t power)
{
    return RT_EOK;
}

static rt_size_t _step_polling_get_data(rt_sensor_t sensor, struct rt_sensor_data *data)
{
    int cnt;
    if (sensor->info.type == RT_SENSOR_CLASS_STEP)
    {
        cnt = vstep_get_step();

        data->type = RT_SENSOR_CLASS_STEP;
        data->data.step = cnt;
        data->timestamp = rt_sensor_get_ts();
    }

    return 1;
}

static rt_size_t step_fetch_data(struct rt_sensor_device *sensor, void *buf, rt_size_t len)
{
    RT_ASSERT(buf);

    if (sensor->config.mode == RT_SENSOR_MODE_POLLING)
    {
        return _step_polling_get_data(sensor, buf);
    }
    else
        return 0;
}

static rt_err_t step_control(struct rt_sensor_device *sensor, int cmd, void *args)
{
    rt_err_t result = RT_EOK;

    switch (cmd)
    {
    case RT_SENSOR_CTRL_GET_ID:
        *(uint8_t *)args = step_dev->id;
        break;
    case RT_SENSOR_CTRL_SET_RANGE:
        result = _step_set_range(sensor, (rt_int32_t)args);
        break;
    case RT_SENSOR_CTRL_SET_ODR:
        result = -RT_EINVAL;
        break;
    case RT_SENSOR_CTRL_SET_MODE:
        result = _step_set_mode(sensor, (rt_uint32_t)args & 0xff);
        break;
    case RT_SENSOR_CTRL_SET_POWER:
        result = _step_set_power(sensor, (rt_uint32_t)args & 0xff);
        break;
    case RT_SENSOR_CTRL_SELF_TEST:
        break;
    default:
        return -RT_ERROR;
    }
    return result;
}

static struct rt_sensor_ops sensor_ops =
{
    step_fetch_data,
    step_control
};

int rt_virt_step_init(const char *name, struct rt_sensor_config *cfg)
{
    rt_int8_t result;
    rt_sensor_t step_acce = RT_NULL;

    result = _step_init();
    if (result != RT_EOK)
    {
        LOG_E("step init err code: %d", result);
        goto __exit;
    }

    /* step sensor register */
    {
        step_acce = rt_calloc(1, sizeof(struct rt_sensor_device));
        if (step_acce == RT_NULL)
            return -1;

        step_acce->info.type       = RT_SENSOR_CLASS_STEP;
        step_acce->info.vendor     = RT_SENSOR_VENDOR_UNKNOWN;
        step_acce->info.model      = "virt_step";
        step_acce->info.unit       = RT_SENSOR_UNIT_ONE;
        step_acce->info.intf_type  = RT_SENSOR_INTF_I2C;
        step_acce->info.range_max  = 100000;
        step_acce->info.range_min  = 1;
        step_acce->info.period_min = 1;

        rt_memcpy(&step_acce->config, cfg, sizeof(struct rt_sensor_config));
        step_acce->ops = &sensor_ops;

        result = rt_hw_sensor_register(step_acce, name, RT_DEVICE_FLAG_RDWR, RT_NULL);
        if (result != RT_EOK)
        {
            LOG_E("device register err code: %d", result);
            goto __exit;
        }
    }

    LOG_I("sensor init success");
    return RT_EOK;

__exit:
    if (step_acce)
        rt_free(step_acce);
    if (step_dev)
        rt_free(step_dev);
    return -RT_ERROR;
}

#endif // STEP_USING_VIRTUAL

