/*
 * SPDX-FileCopyrightText: 2019-2022 SiFli Technologies(Nanjing) Co., Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "rtconfig.h"
#include "lvgl.h"
#include <string.h>
#ifdef LVGL_V9
    #define LV_GC_ROOT(x) x
#endif
#include "lvsf.h"

typedef void (*lv_ex_data_change_notify_t)(lv_ex_data_t *data, lv_ex_binding_t *binding);

static void lv_ex_data_notify_string_change(lv_ex_data_t *data, lv_ex_binding_t *binding);
static void lv_ex_data_notify_int32_change(lv_ex_data_t *data, lv_ex_binding_t *binding);
static void lv_ex_data_notify_uint32_change(lv_ex_data_t *data, lv_ex_binding_t *binding);
static void lv_ex_data_notify_float_change(lv_ex_data_t *data, lv_ex_binding_t *binding);
static void lv_ex_data_notify_time_change(lv_ex_data_t *data, lv_ex_binding_t *binding);
static void lv_ex_data_notify_pointer_change(lv_ex_data_t *data, lv_ex_binding_t *binding);
static void lv_ex_data_notify_list_change(lv_ex_data_t *data, lv_ex_binding_t *binding);

static lv_ll_t lv_ex_not_upd_data;
static lv_ll_t lv_ex_updated_data;
static struct rt_semaphore data_sema;
static const lv_ex_data_change_notify_t lv_ex_data_change_notify[] =
{
    [LV_EX_DATA_STRING] = lv_ex_data_notify_string_change,
    [LV_EX_DATA_INT32] = lv_ex_data_notify_int32_change,
    [LV_EX_DATA_UINT32] = lv_ex_data_notify_uint32_change,
    [LV_EX_DATA_FLOAT] = lv_ex_data_notify_float_change,
    [LV_EX_DATA_TIME] = lv_ex_data_notify_time_change,
    [LV_EX_DATA_POINTER] = lv_ex_data_notify_pointer_change,
    [LV_EX_DATA_LIST] = lv_ex_data_notify_list_change,
};

#define LV_EX_DATA_CHANGE_NOTIFIER_NUM   (sizeof(lv_ex_data_change_notify) / sizeof(lv_ex_data_change_notify[0]))

static void lv_ex_invalidate_data(lv_ex_data_t *data)
{
    LV_ASSERT_NULL(data);

    rt_sem_take(&data_sema, RT_WAITING_FOREVER);

    if (!data->updated)
    {
        lv_ll_chg_list(&LV_GC_ROOT(lv_ex_not_upd_data), &LV_GC_ROOT(lv_ex_updated_data), data, true);
    }
    data->updated = true;

    rt_sem_release(&data_sema);

}

static void lv_ex_data_notify_string_change(lv_ex_data_t *data, lv_ex_binding_t *binding)
{
    LV_ASSERT_NULL(data);
    LV_ASSERT_NULL(binding);

    if (LV_EX_DATA_STRING == binding->arg_type)
    {
        lv_ex_data_target_string_setter_t setter = (lv_ex_data_target_string_setter_t)binding->setter;
        setter(binding->target, data->value.s);
    }
    else if (LV_EX_DATA_POINTER == binding->arg_type)
    {
        lv_ex_data_target_pointer_setter_t setter = (lv_ex_data_target_pointer_setter_t)binding->setter;
        setter(binding->target, data->value.ptr);
    }
    else
    {
        LV_ASSERT_FORMAT_MSG(0, "type mismatch %d", binding->arg_type);
    }
}

static void lv_ex_data_notify_int32_change(lv_ex_data_t *data, lv_ex_binding_t *binding)
{
    char buf[32];

    LV_ASSERT_NULL(data);
    LV_ASSERT_NULL(binding);

    if (LV_EX_DATA_STRING == binding->arg_type)
    {
        lv_snprintf(buf, sizeof(buf), "%d", data->value.i);
        lv_ex_data_target_string_setter_t setter = (lv_ex_data_target_string_setter_t)binding->setter;
        setter(binding->target, buf);
    }
    else if (LV_EX_DATA_INT32 == binding->arg_type)
    {
        lv_ex_data_target_int32_setter_t setter = (lv_ex_data_target_int32_setter_t)binding->setter;
        setter(binding->target, data->value.i);
    }
    else if (LV_EX_DATA_UINT32 == binding->arg_type)
    {
        lv_ex_data_target_uint32_setter_t setter = (lv_ex_data_target_uint32_setter_t)binding->setter;
        setter(binding->target, (uint32_t)data->value.i);
    }
    else if (LV_EX_DATA_FLOAT == binding->arg_type)
    {
        lv_ex_data_target_float_setter_t setter = (lv_ex_data_target_float_setter_t)binding->setter;
        setter(binding->target, (float)data->value.i);
    }
    else
    {
        LV_ASSERT_FORMAT_MSG(0, "type mismatch %d", binding->arg_type);
    }
}

static void lv_ex_data_notify_uint32_change(lv_ex_data_t *data, lv_ex_binding_t *binding)
{
    char buf[32];

    LV_ASSERT_NULL(data);
    LV_ASSERT_NULL(binding);

    if (LV_EX_DATA_STRING == binding->arg_type)
    {
        lv_snprintf(buf, sizeof(buf), "%u", data->value.ui);
        lv_ex_data_target_string_setter_t setter = (lv_ex_data_target_string_setter_t)binding->setter;
        setter(binding->target, buf);
    }
    else if (LV_EX_DATA_INT32 == binding->arg_type)
    {
        lv_ex_data_target_int32_setter_t setter = (lv_ex_data_target_int32_setter_t)binding->setter;
        setter(binding->target, (int32_t)data->value.ui);
    }
    else if (LV_EX_DATA_UINT32 == binding->arg_type)
    {
        lv_ex_data_target_uint32_setter_t setter = (lv_ex_data_target_uint32_setter_t)binding->setter;
        setter(binding->target, data->value.ui);
    }
    else if (LV_EX_DATA_FLOAT == binding->arg_type)
    {
        lv_ex_data_target_float_setter_t setter = (lv_ex_data_target_float_setter_t)binding->setter;
        setter(binding->target, (float)data->value.ui);
    }
    else
    {
        LV_ASSERT_FORMAT_MSG(0, "type mismatch %d", binding->arg_type);
    }


}

static void lv_ex_data_notify_float_change(lv_ex_data_t *data, lv_ex_binding_t *binding)
{
    char buf[32];

    LV_ASSERT_NULL(data);
    LV_ASSERT_NULL(binding);

    if (LV_EX_DATA_STRING == binding->arg_type)
    {
        lv_snprintf(buf, sizeof(buf), "%.2f", data->value.f);
        lv_ex_data_target_string_setter_t setter = (lv_ex_data_target_string_setter_t)binding->setter;
        setter(binding->target, buf);
    }
    else if (LV_EX_DATA_INT32 == binding->arg_type)
    {
        lv_ex_data_target_int32_setter_t setter = (lv_ex_data_target_int32_setter_t)binding->setter;
        setter(binding->target, (int32_t)data->value.f);
    }
    else if (LV_EX_DATA_UINT32 == binding->arg_type)
    {
        lv_ex_data_target_uint32_setter_t setter = (lv_ex_data_target_uint32_setter_t)binding->setter;
        setter(binding->target, (uint32_t)data->value.f);
    }
    else if (LV_EX_DATA_FLOAT == binding->arg_type)
    {
        lv_ex_data_target_float_setter_t setter = (lv_ex_data_target_float_setter_t)binding->setter;
        setter(binding->target, data->value.f);
    }
    else
    {
        LV_ASSERT_FORMAT_MSG(0, "type mismatch %d", binding->arg_type);
    }
}

static void lv_ex_data_notify_time_change(lv_ex_data_t *data, lv_ex_binding_t *binding)
{
    LV_ASSERT_FORMAT_MSG(0, "%s", "not support yet");

}


static void lv_ex_data_notify_pointer_change(lv_ex_data_t *data, lv_ex_binding_t *binding)
{
    LV_ASSERT_NULL(data);
    LV_ASSERT_NULL(binding);

    if (LV_EX_DATA_STRING == binding->arg_type)
    {
        lv_ex_data_target_string_setter_t setter = (lv_ex_data_target_string_setter_t)binding->setter;
        setter(binding->target, data->value.ptr);
    }
    else if (LV_EX_DATA_UINT32 == binding->arg_type)
    {
        lv_ex_data_target_uint32_setter_t setter = (lv_ex_data_target_uint32_setter_t)binding->setter;
        setter(binding->target, (uint32_t)data->value.ptr);
    }
    else if (LV_EX_DATA_POINTER == binding->arg_type)
    {
        lv_ex_data_target_pointer_setter_t setter = (lv_ex_data_target_pointer_setter_t)binding->setter;
        setter(binding->target, data->value.ptr);
    }
    else
    {
        LV_ASSERT_FORMAT_MSG(0, "type mismatch %d", binding->arg_type);
    }
}

static void lv_ex_data_notify_list_change(lv_ex_data_t *data, lv_ex_binding_t *binding)
{
    LV_ASSERT_NULL(data);
    LV_ASSERT_NULL(binding);

    if (LV_EX_DATA_POINTER == binding->arg_type)
    {
        lv_ex_data_target_list_setter_t setter = (lv_ex_data_target_list_setter_t)binding->setter;
        setter(binding->target, data->value.ptr);
    }
    else if (LV_EX_DATA_LIST == binding->arg_type)
    {
        lv_ex_data_target_list_setter_t setter = (lv_ex_data_target_list_setter_t)binding->setter;
        setter(binding->target, data->value.ptr);
    }
    else
    {
        LV_ASSERT_FORMAT_MSG(0, "type mismatch %d", binding->arg_type);
    }
}


void lv_ex_data_pool_init(void)
{
    rt_sem_init(&data_sema, "lv_data", 1, RT_IPC_FLAG_FIFO);
    _lv_ll_init(&LV_GC_ROOT(lv_ex_not_upd_data), sizeof(lv_ex_data_t));
    _lv_ll_init(&LV_GC_ROOT(lv_ex_updated_data), sizeof(lv_ex_data_t));
}


// create data object
lv_ex_data_t *lv_ex_data_create(const char *name, lv_ex_data_type_t type)
{
    lv_ex_data_t *data;

    rt_sem_take(&data_sema, RT_WAITING_FOREVER);

    data = _lv_ll_ins_head(&LV_GC_ROOT(lv_ex_not_upd_data));
    LV_ASSERT_NULL(data);

    data->type = type;
    strncpy(data->name, name, MAX_EX_DATA_NAME_LEN);
    data->name[MAX_EX_DATA_NAME_LEN - 1] = 0;
    memset(&data->value, 0, sizeof(data->value));

    _lv_ll_init(&data->listener, sizeof(lv_ex_binding_t));
    data->updated = false;

    rt_sem_release(&data_sema);

    return data;
}

// delete data object
lv_res_t lv_ex_data_delete(lv_ex_data_t *data)
{
    lv_ll_t *ll;

    LV_ASSERT_NULL(data);

    rt_sem_take(&data_sema, RT_WAITING_FOREVER);

    if (data->updated)
    {
        ll = &LV_GC_ROOT(lv_ex_updated_data);
    }
    else
    {
        ll = &LV_GC_ROOT(lv_ex_not_upd_data);
    }

    _lv_ll_clear(&data->listener);

    _lv_ll_remove(ll, data);

    if ((LV_EX_DATA_STRING == data->type)
            && (data->value.s))
    {
        lv_mem_free((void *)data->value.s);
    }

    lv_mem_free(data);

    rt_sem_release(&data_sema);

    return LV_RES_OK;
}

// bind data object with lv object
// limitation: each lv object has only one data bound property
void *lv_ex_bind_data(lv_ex_data_t *data, lv_ex_binding_t *binding)
{
    void *handle;

    LV_ASSERT_NULL(data);
    LV_ASSERT_NULL(binding);

    rt_sem_take(&data_sema, RT_WAITING_FOREVER);

    handle = _lv_ll_ins_head(&LV_GC_ROOT(data->listener));
    LV_ASSERT_NULL(handle);
    memcpy(handle, binding, sizeof(*binding));

    rt_sem_release(&data_sema);

    lv_ex_invalidate_data(data);

    return handle;
}

lv_res_t lv_ex_unbind_data(lv_ex_data_t *data, void *handle)
{
    LV_ASSERT_NULL(data);
    LV_ASSERT_NULL(handle);

    rt_sem_take(&data_sema, RT_WAITING_FOREVER);

    _lv_ll_remove(&LV_GC_ROOT(data->listener), handle);
    lv_mem_free(handle);

    rt_sem_release(&data_sema);

    return LV_RES_OK;
}


// update data object value and notify listeners
lv_res_t lv_ex_data_set_value(lv_ex_data_t *data, void *value)
{
    bool updated = false;

    LV_ASSERT_NULL(data);

    rt_sem_take(&data_sema, RT_WAITING_FOREVER);

    switch (data->type)
    {
    case LV_EX_DATA_INT32:
    case LV_EX_DATA_UINT32:
    case LV_EX_DATA_FLOAT:
    case LV_EX_DATA_TIME:
    case LV_EX_DATA_POINTER:
    {
        memcpy(&data->value, &value, sizeof(data->value));
        updated = true;

        break;
    }
    case LV_EX_DATA_STRING:
    {
        size_t len = strlen(value) + 1;
        if (data->value.s)
        {
            lv_mem_free((void *)data->value.s);
        }
        data->value.s = lv_mem_alloc(len);
        LV_ASSERT_NULL(data->value.s);
        memcpy((char *)data->value.s, value, len - 1);
        *((char *)data->value.s + len - 1) = 0;
        updated = true;
        break;
    }

    default:
    {
        LV_ASSERT_NULL(0);
        break;
    }
    }

    if ((!data->updated) && updated)
    {
        lv_ll_chg_list(&LV_GC_ROOT(lv_ex_not_upd_data), &LV_GC_ROOT(lv_ex_updated_data), data, true);
        data->updated = true;
    }


    rt_sem_release(&data_sema);

    return LV_RES_OK;
}


void lv_ex_process_data(void)
{
    lv_ex_data_t *data;
    void *listener;
    lv_ex_binding_t *binding;

    rt_sem_take(&data_sema, RT_WAITING_FOREVER);

    if (_lv_ll_is_empty(&lv_ex_updated_data))
    {
        rt_sem_release(&data_sema);
        return;
    }

    /* loop in all updated data */
    _LV_LL_READ(&lv_ex_updated_data, data)
    {
        /* loop in all listeners */
        _LV_LL_READ(&data->listener, listener)
        {
            binding = (lv_ex_binding_t *)listener;
            LV_ASSERT_FORMAT_MSG(data->type < LV_EX_DATA_CHANGE_NOTIFIER_NUM, "invalid data type %d", data->type);
            lv_ex_data_change_notify[data->type](data, binding);
        }
        data->updated = false;
    }

    lv_ll_merge_list(&lv_ex_not_upd_data, &lv_ex_updated_data);

    rt_sem_release(&data_sema);
}



