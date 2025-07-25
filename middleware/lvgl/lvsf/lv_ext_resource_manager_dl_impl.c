/*
 * SPDX-FileCopyrightText: 2019-2022 SiFli Technologies(Nanjing) Co., Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "lv_ext_resource_manager.h"

#if defined(LV_EXT_RES_STANDALONE) && defined(RT_USING_MODULE)

#include "dlmodule.h"
#include "dlfcn.h"

static struct lv_ext_res_mng_tag res_mng_dl_impl;

#if 0
static lv_res_t load(lv_ext_res_mng_t res_mng)
{
    lv_ext_res_mng_dl_impl_data_t *data;
    lv_res_t result;

    data = (lv_ext_res_mng_dl_impl_data_t *)res_mng->user_data;

    data->img_module = dlopen(data->img_module_name, 0);
    if (!data->img_module)
    {
        result = LV_RES_INV;
        goto __exit;
    }
    data->str_module = dlopen(data->str_module_name, 0);
    if (!data->str_module)
    {
        result = LV_RES_INV;
        goto __exit;
    }

    result = LV_RES_OK;

__exit:
    return result;
}

static lv_img_dsc_t *get_img(lv_ext_res_mng_t res_mng, const char *key)
{
    lv_ext_res_mng_dl_impl_data_t *data;
    lv_img_dsc_t *img = NULL;

    data = (lv_ext_res_mng_dl_impl_data_t *)res_mng->user_data;

    if (data->img_module)
    {
        img = dlsym(data->img_module, key);
    }

    return img;
}

const char *get_string(lv_ext_res_mng_t res_mng, uint32_t offset, const char *key)
{
    return NULL;
}

static const lv_i18n_lang_pack_t *get_lang_pack(lv_ext_res_mng_t res_mng)
{
    lv_ext_res_mng_dl_impl_data_t *data;
    const lv_i18n_lang_pack_t *lang_pack = NULL;

    data = (lv_ext_res_mng_dl_impl_data_t *)res_mng->user_data;

    if (data->str_module)
    {
        lang_pack = dlsym(data->str_module, "lv_i18n_lang_pack");
    }

    return lang_pack;
}

static const lv_ex_font_config_t *get_font_config(lv_ext_res_mng_t res_mng)
{
    lv_ext_res_mng_dl_impl_data_t *data;
    const lv_ex_font_config_t *font_config = NULL;

    data = (lv_ext_res_mng_dl_impl_data_t *)res_mng->user_data;

    if (data->font_module)
    {
        font_config = dlsym(data->str_module, "lv_ex_font_config");
    }

    return font_config;
}

lv_res_t lv_ext_res_mng_init(void *user_data)
{
    res_mng_dl_impl.get_img = get_img;
    res_mng_dl_impl.get_string = get_string;
    res_mng_dl_impl.load = load;
    res_mng_dl_impl.get_lang_pack = get_lang_pack;
    res_mng_dl_impl.get_font_config = get_font_config;
    res_mng_dl_impl.user_data = user_data;

    return lv_ext_register_res_manager(&res_mng_dl_impl);
}

lv_res_t lv_ext_res_mng_dl_impl_init(lv_ext_res_mng_t res_mng, lv_ext_res_mng_dl_impl_data_t *user_data)
{
    void *module;
    lv_res_t result;
    const lv_i18n_lang_pack_t *lang_pack;
    void *user_data_copy;

    RT_ASSERT(res_mng);

    memset(res_mng, 0, sizeof(*res_mng));

    module = dlrun(user_data->str_module_name, LANG_INSTALL_PATH);
    if (!module)
    {
        result = LV_RES_INV;
        goto __EXIT;
    }

    lang_pack = dlsym(module, "lv_i18n_lang_pack");
    user_data->str_module = module;

    user_data_copy = lv_mem_alloc(sizeof(lv_ext_res_mng_dl_impl_data_t));
    RT_ASSERT(user_data_copy);
    memcpy(user_data_copy, user_data, sizeof(lv_ext_res_mng_dl_impl_data_t));

    rt_enter_critical();

    res_mng->lang_pack = lang_pack;
    res_mng->curr_lang = lang_pack[0];
    res_mng->user_data = user_data_copy;

    rt_exit_critical();

    return LV_RES_OK;
__EXIT:
    return result;
}

lv_res_t lv_ext_res_mng_dl_impl_destroy(lv_ext_res_mng_t res_mng)
{
    int res;
    lv_ext_res_mng_dl_impl_data_t *data;

    data = (lv_ext_res_mng_dl_impl_data_t *)res_mng->user_data;

    dlclose(data->str_module);

    lv_mem_free(res_mng->user_data);
    res_mng->user_data = NULL;

    return LV_RES_OK;
}
#endif

#endif /*LV_EXT_RESOURCE_MANAGER_DL_IMPL*/

