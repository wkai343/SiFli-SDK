#include "rtthread.h"
#include "bf0_hal.h"
#include "drv_io.h"
#include "stdio.h"
#include "string.h"
#include "lvgl.h"
#include "littlevgl2rtt.h"
#include "lv_ex_data.h"

LV_IMG_DECLARE(img_shanghai);

typedef struct
{
    lv_obj_t *img_shanghai;

} eez_studio_t;

eez_studio_t *eez_image  = NULL; // Global pointer to EEZ Studio instance

//According to the size of the incoming target, set the scaling of the specified image object
/**
 * @brief Set the zoom level of a specified image object according to target size
 *
 * @param obj_img Image object to set zoom level for
 * @param src Source image data
 * @param obj_width Target display width
 * @param obj_height Target display height
 */
static void lv_obj_img_set_zoom(lv_obj_t *obj_img, const void *src, uint32_t obj_width, uint32_t obj_height)
{
    uint32_t img_width = 0, img_height = 0, zoom_factor = 0;
    lv_img_header_t header;
    // Get image information
    if (lv_img_decoder_get_info(src, &header) != LV_RES_OK)
    {
        rt_kprintf("lv_img_decoder_get_info error\n");
        return;
    }

    img_width = header.w;
    img_height = header.h;

    rt_kprintf("img_widtg:%u, img_height%u, obj_width:%u, obj_height%u\n", img_width, img_height, obj_width, obj_height);
    // Calculate and set zoom factor if image dimensions are valid
    if (img_width != 0 && img_height != 0)
    {
        uint32_t y_a = obj_height;
        uint32_t x_b = obj_width;

        if (x_b >= y_a)
        {
            uint32_t x = obj_height * 256;
            zoom_factor = x / img_height;
            lv_img_set_zoom(obj_img, zoom_factor);
        }
        else
        {
            uint32_t x = obj_width * 256;
            zoom_factor = x / img_width;
            lv_img_set_zoom(obj_img, zoom_factor);
        }
    }
}

/**
 * @brief Initialize EEZ Studio display
 */
void eez_studio_init(void)
{
    // Allocate memory and initialize
    eez_image = (eez_studio_t *)rt_malloc(sizeof(eez_studio_t));
    memset(eez_image, 0, sizeof(eez_studio_t));
    // Create image object for Shanghai
    eez_image->img_shanghai = lv_img_create(lv_scr_act());
    lv_obj_align(eez_image->img_shanghai, LV_ALIGN_CENTER, 0, 0);
    // Set the image source
    lv_img_set_src(eez_image->img_shanghai, &img_shanghai);
    // Set target dimensions and adjust zoom level
    unsigned int obj_width = 390, obj_height = 450;
    lv_obj_img_set_zoom(eez_image->img_shanghai, &img_shanghai, obj_width, obj_height);
}

/**
 * @brief  Main program
 * @param  None
 * @retval 0 if success, otherwise failure number
 */
int main(void)
{
    rt_err_t ret = RT_EOK;
    rt_uint32_t ms;

    /* init littlevGL */
    ret = littlevgl2rtt_init("lcd");
    if (ret != RT_EOK)
    {
        return ret;
    }
    lv_ex_data_pool_init();

    rt_kprintf("EEZ Studio LVGL Image Example\n");
    eez_studio_init();
    /* Infinite loop */
    while (1)
    {
        ms = lv_task_handler();
        rt_thread_mdelay(ms);
    }
    return 0;
}

