/*
 * SPDX-FileCopyrightText: 2019-2022 SiFli Technologies(Nanjing) Co., Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "littlevgl2rtt.h"
#include "lvgl.h"
#include "board.h"
#include "drv_touch.h"

static lv_indev_drv_t indev_drv;
static rt_device_t touch_device = NULL;
static rt_uint32_t touch_data_cnt = 0;

static rt_err_t rx_indicate(rt_device_t dev, rt_size_t size)
{
    ++touch_data_cnt;

    //rt_kprintf("lv touch device rx indicate!  %d\r\n", touch_data_cnt);

    return RT_EOK;
}

static void input_read(struct _lv_indev_drv_t *indev_drv, lv_indev_data_t *data)   //(lv_indev_data_t *data)//(struct _lv_indev_drv_t * indev_drv, lv_indev_data_t * data
{

    if (touch_device)
    {
        struct touch_message touch_data;

        rt_device_read(touch_device, 0, &touch_data, 1);

        switch (touch_data.event)
        {
        case TOUCH_EVENT_DOWN:
        case TOUCH_EVENT_MOVE:
            data->state = LV_INDEV_STATE_PR;
            break;

        case TOUCH_EVENT_UP:
        default:
            data->state = LV_INDEV_STATE_REL;
            break;
        }

        data->point.x = touch_data.x;
        data->point.y = touch_data.y;

        if (touch_data_cnt > 0) --touch_data_cnt;
    }

#ifdef BSP_USING_LVGL_INPUT_AGENT
    {
        extern int lv_indev_agent_filter(lv_indev_drv_t *drv, lv_indev_data_t *data);
        lv_indev_agent_filter(indev_drv, data);
    }
#endif
    data->continue_reading = (touch_data_cnt > 0);
}

static lv_indev_t *touch_indev;

void touch_init()
{
    //slv_indev_t *dev;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;

    /*Open touch device*/
    RT_ASSERT(NULL == touch_device);
    touch_device = rt_device_find("touch");
    if (touch_device)
    {
        if (RT_EOK == rt_device_open(touch_device, RT_DEVICE_FLAG_RDONLY))
        {
            touch_device->rx_indicate = rx_indicate;
        }
        else
        {
            touch_device = NULL;
        }
    }

    indev_drv.read_cb = input_read;
    touch_indev = lv_indev_drv_register(&indev_drv);

#ifdef BSP_USING_LVGL_INPUT_AGENT
    {
        extern void lv_indev_agent_init(lv_indev_drv_t *drv);
        lv_indev_agent_init(&indev_drv);
    }
#endif

}

lv_indev_t *touch_get_indev_handler(void)
{
    return touch_indev;
}

