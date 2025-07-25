/*
 * SPDX-FileCopyrightText: 2019-2022 SiFli Technologies(Nanjing) Co., Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "rtthread.h"
#include <stdint.h>
#include <stdbool.h>
#include "ipc_queue.h"

#define IPC_QUEUE_DEVICE_WRITE_TIMEOUT   (1000)


static rt_err_t ipc_queue_device_open(rt_device_t dev, rt_uint16_t oflag)
{
    ipc_queue_handle_t q = (ipc_queue_handle_t)dev->user_data;

    RT_ASSERT(IPC_QUEUE_INVALID_HANDLE != q);
    if (!ipc_queue_is_open(q))
    {
        return ipc_queue_open(q);
    }
    else
    {
        return RT_EOK;
    }
}

static rt_err_t ipc_queue_device_close(rt_device_t dev)
{
    ipc_queue_handle_t q = (ipc_queue_handle_t)dev->user_data;

    RT_ASSERT(IPC_QUEUE_INVALID_HANDLE != q);
    return ipc_queue_close(q);
}

static rt_size_t ipc_queue_device_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    ipc_queue_handle_t q = (ipc_queue_handle_t)dev->user_data;

    RT_ASSERT(IPC_QUEUE_INVALID_HANDLE != q);

    return ipc_queue_read(q, buffer, size);
}

static rt_size_t ipc_queue_device_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    ipc_queue_handle_t q = (ipc_queue_handle_t)dev->user_data;

    RT_ASSERT(IPC_QUEUE_INVALID_HANDLE != q);

    return ipc_queue_write(q, buffer, size, IPC_QUEUE_DEVICE_WRITE_TIMEOUT);
}


int32_t ipc_queue_device_rx_ind(ipc_queue_handle_t queue, size_t size)
{
    rt_device_t device;
    int32_t ret;

    ret = ipc_queue_get_user_data(queue, (uint32_t *)&device);
    RT_ASSERT(0 == ret);
    if (device)
    {
        RT_ASSERT(RT_Device_Class_Mailbox == device->type);
        RT_ASSERT((void *)queue == device->user_data);
        if (device->rx_indicate)
        {
            device->rx_indicate(device, size);
        }
    }

    return 0;
}

rt_err_t ipc_queue_device_register(rt_device_t device, const char *name, ipc_queue_handle_t queue)
{
    rt_err_t err;

    if (!device || !name || (IPC_QUEUE_INVALID_HANDLE == queue))
    {
        return -RT_ERROR;
    }

    device->type        = RT_Device_Class_Mailbox;
    device->rx_indicate = RT_NULL;
    device->tx_complete = RT_NULL;

    device->init        = RT_NULL;
    device->open        = ipc_queue_device_open;
    device->close       = ipc_queue_device_close;
    device->read        = ipc_queue_device_read;
    device->write       = ipc_queue_device_write;
    device->control     = RT_NULL;

    device->user_data   = (void *)queue;

    return rt_device_register(device, name, RT_DEVICE_FLAG_RDWR);
}






