/*
 * SPDX-FileCopyrightText: 2019-2022 SiFli Technologies(Nanjing) Co., Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtthread.h>
#include <string.h>
#include <stdlib.h>
#include "charge.h"


#define DBG_TAG "charge"
#define DBG_LVL DBG_INFO
#ifdef RT_USING_PM
    #include "rtthread.h"
#endif
#include "rtdevice.h"
#ifdef BSP_USING_PM
    #include <drivers/pm.h>
#endif

static rt_device_t g_charge = RT_NULL;

static rt_err_t charge_control(rt_device_t dev, int cmd, void *args)
{
    rt_charge_err_t result = RT_CHARGE_EOK;
    rt_charge_device_t *charge = (rt_charge_device_t *)dev;

#ifdef RT_USING_PM
    if (RT_DEVICE_CTRL_RESUME == cmd)
    {
        uint8_t power_mode = (uint8_t)((uint32_t)args);
        if (PM_SLEEP_MODE_STANDBY == power_mode)
        {

        }
    }
    else if (RT_DEVICE_CTRL_SUSPEND == cmd)
    {
        /* do nothing */
    }
#endif
    result = charge->ops->control(charge, cmd, args);
    return result;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops charge_ops =
{
    RT_NULL,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    charge_control,
};
#endif

rt_charge_err_t rt_charge_enable(uint8_t enable)
{
    return rt_device_control(g_charge, RT_CHARGE_ENABLE, &enable);
}

rt_charge_err_t rt_charge_get_status(uint8_t *state)
{
    return rt_device_control(g_charge, RT_CHARGE_GET_STATUS, state);
}

rt_charge_err_t rt_charge_get_full_status(uint8_t *state)
{
    return rt_device_control(g_charge, RT_CHARGE_GET_FULL_STATUS, state);
}

rt_charge_err_t rt_charge_get_detect_status(uint8_t *state)
{
    return rt_device_control(g_charge, RT_CHARGE_GET_DETECT_STATUS, state);
}

rt_charge_err_t rt_charge_force_enable(uint8_t enable)
{
    return rt_device_control(g_charge, RT_CHARGE_FORCE_ENABLE_CHARGING, &enable);
}

rt_charge_err_t rt_charge_force_resume_charging(void)
{
    return rt_device_control(g_charge, RT_CHARGE_FORCE_RESUME_CHARGING, RT_NULL);
}


rt_charge_err_t rt_charge_force_suspend_charging(void)
{
    return rt_device_control(g_charge, RT_CHARGE_FORCE_SUSPEND_CHARGING, RT_NULL);
}

rt_charge_err_t rt_charge_get_hw_status(rt_charge_hw_state_t *state)
{
    return rt_device_control(g_charge, RT_CHARGE_GET_HW_STATE, state);
}


#if 0//  defined(CHARGE_MONITOR_TEMP_CONFIG)
rt_charge_err_t rt_charge_get_core_temp(int *temp)
{
    return rt_device_control(g_charge, RT_CHARGE_GET_CORE_TEMPERATURE, temp);
}
#endif
rt_charge_err_t rt_charge_set_rx_ind(rt_err_t (*rx_ind)(rt_device_t dev, rt_size_t size))
{
    return rt_device_set_rx_indicate(g_charge, rx_ind);
}


rt_charge_err_t rt_charge_set_precc_current(float current)
{
    return rt_device_control(g_charge, RT_CHARGE_SET_PRECC_CURRENT, &current);
}

rt_charge_err_t rt_charge_set_cc_current(uint32_t current)
{
    return rt_device_control(g_charge, RT_CHARGE_SET_CC_CURRENT, &current);
}

rt_charge_err_t rt_charge_set_target_volt(uint32_t volt)
{
    return rt_device_control(g_charge, RT_CHARGE_SET_TARGET_VOLT, &volt);
}

rt_charge_err_t rt_charge_set_repvolt(uint32_t volt)
{
    return rt_device_control(g_charge, RT_CHARGE_SET_REPVOLT, &volt);
}

rt_charge_err_t rt_charge_set_over_volt(uint32_t volt)
{
    return rt_device_control(g_charge, RT_CHARGE_SET_OVER_VOLT, &volt);
}


void rt_charge_event_notify(rt_charge_event_t event)
{
    if (!g_charge)
    {
        return;
    }

    if (g_charge->rx_indicate)
    {
        g_charge->rx_indicate(g_charge, event);
    }
    return;
}


rt_err_t rt_charge_register(rt_charge_device_t *device, const struct rt_charge_ops *ops, const void *user_data)
{
    rt_err_t result = RT_EOK;
    RT_ASSERT(ops != RT_NULL);

    device->parent.type = RT_Device_Class_Miscellaneous;
    device->parent.rx_indicate = RT_NULL;
    device->parent.tx_complete = RT_NULL;

#ifdef RT_USING_DEVICE_OPS
    device->parent.ops         = &charge_ops;
#else
    device->parent.init        = RT_NULL;
    device->parent.open        = RT_NULL;
    device->parent.close       = RT_NULL;
    device->parent.read        = RT_NULL;
    device->parent.write       = RT_NULL;
    device->parent.control     = charge_control;
#endif
    device->ops = ops;
    device->parent.user_data = (void *)user_data;

    result = rt_device_register(&device->parent, "charge", RT_DEVICE_FLAG_RDWR);
    return result;
}


int charge_init(void)
{
    g_charge = rt_device_find("charge");
    RT_ASSERT(g_charge);
    return RT_EOK;
}

INIT_DEVICE_EXPORT(charge_init);

