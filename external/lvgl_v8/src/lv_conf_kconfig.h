/** * @file lv_conf_kconfig.h * Configs that need special handling when LVGL is used with Kconfig */

#ifndef LV_CONF_KCONFIG_H
#define LV_CONF_KCONFIG_H

#ifdef __cplusplus
extern "C" {
#endif


#ifdef LV_CONF_KCONFIG_EXTERNAL_INCLUDE
#  include LV_CONF_KCONFIG_EXTERNAL_INCLUDE
#else

#  ifdef ESP_PLATFORM
#    include "sdkconfig.h"
#    include "esp_attr.h"
#  endif

#  ifdef __NuttX__
#    include <nuttx/config.h>
#  elif defined(__RTTHREAD__)
#    define LV_CONF_INCLUDE_SIMPLE
#    include <lv_rt_thread_conf.h>
#  endif

#endif /*LV_CONF_KCONFIG_EXTERNAL_INCLUDE*/

/*******************
 * LV COLOR CHROMA KEY
 *******************/

#ifdef CONFIG_LV_COLOR_CHROMA_KEY_HEX
#  define CONFIG_LV_COLOR_CHROMA_KEY lv_color_hex(CONFIG_LV_COLOR_CHROMA_KEY_HEX)
#endif

/*******************
 * LV_MEM_SIZE
 *******************/

#ifdef CONFIG_LV_MEM_SIZE_KILOBYTES
#  define CONFIG_LV_MEM_SIZE (CONFIG_LV_MEM_SIZE_KILOBYTES * 1024U)
#endif

/*------------------
 * MONITOR POSITION
 *-----------------*/

#ifdef LV_PERF_MONITOR_ALIGN_TOP_LEFT
#  define CONFIG_LV_USE_PERF_MONITOR_POS LV_ALIGN_TOP_LEFT
#elif defined(LV_USE_PERF_MONITOR_ALIGN_TOP_MID)
#  define CONFIG_LV_USE_PERF_MONITOR_POS LV_ALIGN_TOP_MID
#elif defined(LV_PERF_MONITOR_ALIGN_TOP_RIGHT)
#  define CONFIG_LV_USE_PERF_MONITOR_POS LV_ALIGN_TOP_RIGHT
#elif defined(LV_PERF_MONITOR_ALIGN_BOTTOM_LEFT)
#  define CONFIG_LV_USE_PERF_MONITOR_POS LV_ALIGN_BOTTOM_LEFT
#elif defined(LV_PERF_MONITOR_ALIGN_BOTTOM_MID)
#  define CONFIG_LV_USE_PERF_MONITOR_POS LV_ALIGN_BOTTOM_MID
#elif defined(LV_PERF_MONITOR_ALIGN_BOTTOM_RIGHT)
#  define CONFIG_LV_USE_PERF_MONITOR_POS LV_ALIGN_BOTTOM_RIGHT
#elif defined(LV_PERF_MONITOR_ALIGN_LEFT_MID)
#  define CONFIG_LV_USE_PERF_MONITOR_POS LV_ALIGN_LEFT_MID
#elif defined(LV_PERF_MONITOR_ALIGN_RIGHT_MID)
#  define CONFIG_LV_USE_PERF_MONITOR_POS LV_ALIGN_RIGHT_MID
#elif defined(LV_PERF_MONITOR_ALIGN_CENTER)
#  define CONFIG_LV_USE_PERF_MONITOR_POS LV_ALIGN_CENTER
#endif

#ifdef CONFIG_LV_MEM_MONITOR_ALIGN_TOP_LEFT
#  define CONFIG_LV_USE_MEM_MONITOR_POS LV_ALIGN_TOP_LEFT
#elif defined(CONFIG_LV_USE_MEM_MONITOR_ALIGN_TOP_MID)
#  define CONFIG_LV_USE_MEM_MONITOR_POS LV_ALIGN_TOP_MID
#elif defined(CONFIG_LV_MEM_MONITOR_ALIGN_TOP_RIGHT)
#  define CONFIG_LV_USE_MEM_MONITOR_POS LV_ALIGN_TOP_RIGHT
#elif defined(CONFIG_LV_MEM_MONITOR_ALIGN_BOTTOM_LEFT)
#  define CONFIG_LV_USE_MEM_MONITOR_POS LV_ALIGN_BOTTOM_LEFT
#elif defined(CONFIG_LV_MEM_MONITOR_ALIGN_BOTTOM_MID)
#  define CONFIG_LV_USE_MEM_MONITOR_POS LV_ALIGN_BOTTOM_MID
#elif defined(CONFIG_LV_MEM_MONITOR_ALIGN_BOTTOM_RIGHT)
#  define CONFIG_LV_USE_MEM_MONITOR_POS LV_ALIGN_BOTTOM_RIGHT
#elif defined(CONFIG_LV_MEM_MONITOR_ALIGN_LEFT_MID)
#  define CONFIG_LV_USE_MEM_MONITOR_POS LV_ALIGN_LEFT_MID
#elif defined(CONFIG_LV_MEM_MONITOR_ALIGN_RIGHT_MID)
#  define CONFIG_LV_USE_MEM_MONITOR_POS LV_ALIGN_RIGHT_MID
#elif defined(CONFIG_LV_MEM_MONITOR_ALIGN_CENTER)
#  define CONFIG_LV_USE_MEM_MONITOR_POS LV_ALIGN_CENTER
#endif

/********************
 * FONT SELECTION
 *******************/

/**
 * NOTE: In Kconfig instead of `LV_DEFAULT_FONT`
 *       `LV_FONT_DEFAULT_<font_name>` is defined
 *       hence the large selection with if-s
 */

/*------------------
 * DEFAULT FONT
 *-----------------*/
#ifdef LV_FONT_DEFAULT_MONTSERRAT_8
#  define CONFIG_LV_FONT_DEFAULT &lv_font_montserrat_8
#elif defined(LV_FONT_DEFAULT_MONTSERRAT_10)
#  define CONFIG_LV_FONT_DEFAULT &lv_font_montserrat_10
#elif defined(LV_FONT_DEFAULT_MONTSERRAT_12)
#  define CONFIG_LV_FONT_DEFAULT &lv_font_montserrat_12
#elif defined(LV_FONT_DEFAULT_MONTSERRAT_14)
#  define CONFIG_LV_FONT_DEFAULT &lv_font_montserrat_14
#elif defined(LV_FONT_DEFAULT_MONTSERRAT_16)
#  define CONFIG_LV_FONT_DEFAULT &lv_font_montserrat_16
#elif defined(LV_FONT_DEFAULT_MONTSERRAT_18)
#  define CONFIG_LV_FONT_DEFAULT &lv_font_montserrat_18
#elif defined(LV_FONT_DEFAULT_MONTSERRAT_20)
#  define CONFIG_LV_FONT_DEFAULT &lv_font_montserrat_20
#elif defined(LV_FONT_DEFAULT_MONTSERRAT_22)
#  define CONFIG_LV_FONT_DEFAULT &lv_font_montserrat_22
#elif defined(LV_FONT_DEFAULT_MONTSERRAT_24)
#  define CONFIG_LV_FONT_DEFAULT &lv_font_montserrat_24
#elif defined(LV_FONT_DEFAULT_MONTSERRAT_26)
#  define CONFIG_LV_FONT_DEFAULT &lv_font_montserrat_26
#elif defined(LV_FONT_DEFAULT_MONTSERRAT_28)
#  define CONFIG_LV_FONT_DEFAULT &lv_font_montserrat_28
#elif defined(LV_FONT_DEFAULT_MONTSERRAT_30)
#  define CONFIG_LV_FONT_DEFAULT &lv_font_montserrat_30
#elif defined(LV_FONT_DEFAULT_MONTSERRAT_32)
#  define CONFIG_LV_FONT_DEFAULT &lv_font_montserrat_32
#elif defined(LV_FONT_DEFAULT_MONTSERRAT_34)
#  define CONFIG_LV_FONT_DEFAULT &lv_font_montserrat_34
#elif defined(LV_FONT_DEFAULT_MONTSERRAT_36)
#  define CONFIG_LV_FONT_DEFAULT &lv_font_montserrat_36
#elif defined(LV_FONT_DEFAULT_MONTSERRAT_38)
#  define CONFIG_LV_FONT_DEFAULT &lv_font_montserrat_38
#elif defined(LV_FONT_DEFAULT_MONTSERRAT_40)
#  define CONFIG_LV_FONT_DEFAULT &lv_font_montserrat_40
#elif defined(LV_FONT_DEFAULT_MONTSERRAT_42)
#  define CONFIG_LV_FONT_DEFAULT &lv_font_montserrat_42
#elif defined(LV_FONT_DEFAULT_MONTSERRAT_44)
#  define CONFIG_LV_FONT_DEFAULT &lv_font_montserrat_44
#elif defined(LV_FONT_DEFAULT_MONTSERRAT_46)
#  define CONFIG_LV_FONT_DEFAULT &lv_font_montserrat_46
#elif defined(LV_FONT_DEFAULT_MONTSERRAT_48)
#  define CONFIG_LV_FONT_DEFAULT &lv_font_montserrat_48
#elif defined(LV_FONT_DEFAULT_MONTSERRAT_12_SUBPX)
#  define CONFIG_LV_FONT_DEFAULT &lv_font_montserrat_12_subpx
#elif defined(LV_FONT_DEFAULT_MONTSERRAT_28_COMPRESSED)
#  define CONFIG_LV_FONT_DEFAULT &lv_font_montserrat_28_compressed
#elif defined(LV_FONT_DEFAULT_DEJAVU_16_PERSIAN_HEBREW)
#  define CONFIG_LV_FONT_DEFAULT &lv_font_dejavu_16_persian_hebrew
#elif defined(LV_FONT_DEFAULT_SIMSUN_16_CJK)
#  define CONFIG_LV_FONT_DEFAULT &lv_font_simsun_16_cjk
#elif defined(LV_FONT_DEFAULT_UNSCII_8)
#  define CONFIG_LV_FONT_DEFAULT &lv_font_unscii_8
#elif defined(LV_FONT_DEFAULT_UNSCII_16)
#  define CONFIG_LV_FONT_DEFAULT &lv_font_unscii_16
#endif

/*------------------
 * TEXT ENCODING
 *-----------------*/
#ifdef CONFIG_LV_TXT_ENC_UTF8
#  define CONFIG_LV_TXT_ENC LV_TXT_ENC_UTF8
#elif defined(CONFIG_LV_TXT_ENC_ASCII)
#  define CONFIG_LV_TXT_ENC LV_TXT_ENC_ASCII
#endif

/*------------------
 * BIDI DIRECTION
 *-----------------*/

#ifdef CONFIG_LV_BASE_DIR_LTR
#  define CONFIG_LV_BIDI_BASE_DIR_DEF LV_BASE_DIR_LTR
#elif defined(CONFIG_LV_BASE_DIR_RTL)
#  define CONFIG_LV_BIDI_BASE_DIR_DEF LV_BASE_DIR_RTL
#elif defined(CONFIG_LV_BASE_DIR_AUTO)
#  define CONFIG_LV_BIDI_BASE_DIR_DEF LV_BASE_DIR_AUTO
#endif

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_CONF_KCONFIG_H*/
