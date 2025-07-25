#include "rtthread.h"
#include "bf0_hal.h"
#include "drv_io.h"
#include "littlevgl2rtt.h"
#include "lv_ex_data.h"
#include "game_minesweeper.h"

/**
     * @brief 扫雷小游戏 for SF32
     * @author 启凡科创
     * @date 2025-06-11
     * @version 1.1
     * @copyright OwO
*/

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

    game_minesweeper_load();

    while (1)
    {
        ms = lv_task_handler();
        rt_thread_mdelay(ms);
    }
    return RT_EOK;

}
