#ifdef __has_include
    #if __has_include("lvgl.h")
        #ifndef LV_LVGL_H_INCLUDE_SIMPLE
            #define LV_LVGL_H_INCLUDE_SIMPLE
        #endif
    #endif
#endif

#if defined(LV_LVGL_H_INCLUDE_SIMPLE)
    #include "lvgl.h"
#else
    #include "lvgl/lvgl.h"
#endif


#ifndef LV_ATTRIBUTE_MEM_ALIGN
#define LV_ATTRIBUTE_MEM_ALIGN
#endif

#ifndef LV_ATTRIBUTE_IMG_GAME_MINESWEEPER_IMG_FLAG_BIG
#define LV_ATTRIBUTE_IMG_GAME_MINESWEEPER_IMG_FLAG_BIG
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_GAME_MINESWEEPER_IMG_FLAG_BIG uint8_t game_minesweeper_img_flag_big_map[] = {
#if LV_COLOR_DEPTH == 1 || LV_COLOR_DEPTH == 8
  /*Pixel format: Red: 3 bit, Green: 3 bit, Blue: 2 bit*/
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdb, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdb, 0xb6, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdb, 0x6d, 0x6e, 
  0xff, 0xff, 0xff, 0xb7, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xd7, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xb6, 0x6e, 0x92, 
  0xff, 0xff, 0xff, 0xdb, 0xdb, 0xdb, 0xdb, 0xdf, 0xdf, 0xee, 0xe0, 0xd6, 0xdf, 0xdb, 0xdb, 0xdb, 0xff, 0xb7, 0x6e, 0x92, 
  0xff, 0xff, 0xff, 0xdb, 0xdb, 0xdb, 0xdf, 0xd6, 0xed, 0xe0, 0xe0, 0xd6, 0xdf, 0xdb, 0xdb, 0xdb, 0xff, 0xb7, 0x6e, 0x92, 
  0xff, 0xff, 0xff, 0xdb, 0xdf, 0xd6, 0xed, 0xe0, 0xe0, 0xe0, 0xe0, 0xd6, 0xdf, 0xdb, 0xdb, 0xdb, 0xff, 0xb7, 0x6e, 0x92, 
  0xff, 0xff, 0xff, 0xdb, 0xdb, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xd6, 0xdf, 0xdb, 0xdb, 0xdb, 0xff, 0xb7, 0x6e, 0x92, 
  0xff, 0xff, 0xff, 0xdb, 0xdb, 0xf2, 0xe5, 0xe0, 0xe0, 0xe0, 0xe0, 0xd6, 0xdf, 0xdb, 0xdb, 0xdb, 0xff, 0xb7, 0x6e, 0x92, 
  0xff, 0xff, 0xff, 0xdb, 0xdb, 0xdb, 0xdf, 0xee, 0xe9, 0xe0, 0xe0, 0xf6, 0xdf, 0xdb, 0xdb, 0xdb, 0xff, 0xb7, 0x6e, 0x92, 
  0xff, 0xff, 0xff, 0xdb, 0xdb, 0xdb, 0xdb, 0xdf, 0xdf, 0xa9, 0x60, 0xb6, 0xdf, 0xdb, 0xdb, 0xdb, 0xff, 0xb7, 0x6e, 0x92, 
  0xff, 0xff, 0xff, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xff, 0x72, 0x00, 0xb6, 0xff, 0xdb, 0xdb, 0xdb, 0xff, 0xb7, 0x6e, 0x92, 
  0xff, 0xff, 0xff, 0xdb, 0xdb, 0xff, 0xff, 0xff, 0xff, 0x92, 0x00, 0xb7, 0xff, 0xff, 0xff, 0xdb, 0xdb, 0xb7, 0x6e, 0x92, 
  0xff, 0xff, 0xff, 0xdb, 0xdb, 0x92, 0x92, 0x92, 0x92, 0x49, 0x00, 0x6d, 0x92, 0x92, 0x92, 0xdb, 0xff, 0xb7, 0x6e, 0x92, 
  0xff, 0xff, 0xff, 0xdb, 0xb6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb6, 0xff, 0xb7, 0x6e, 0x92, 
  0xff, 0xff, 0xff, 0xdb, 0xb6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb6, 0xff, 0xb7, 0x6e, 0x92, 
  0xff, 0xff, 0xff, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xff, 0xb7, 0x6e, 0x92, 
  0xff, 0xff, 0xdb, 0xb6, 0xb7, 0xb7, 0xb7, 0xb7, 0xb7, 0xb7, 0xb7, 0xb7, 0xb7, 0xb7, 0xb7, 0xb7, 0xb7, 0xb6, 0x92, 0x92, 
  0xff, 0xdb, 0x6d, 0x6e, 0x6e, 0x6e, 0x6e, 0x6e, 0x6e, 0x6e, 0x6e, 0x6e, 0x6e, 0x6e, 0x6e, 0x6e, 0x6e, 0x92, 0x92, 0x92, 
  0xdb, 0xb6, 0x6e, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x6d, 
#endif
#if LV_COLOR_DEPTH == 16 && LV_COLOR_16_SWAP == 0
  /*Pixel format: Red: 5 bit, Green: 6 bit, Blue: 5 bit*/
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x5d, 0xef, 0x38, 0xc6, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xb6, 0xb5, 0xb3, 0x9c, 
  0xff, 0xff, 0xff, 0xff, 0x5d, 0xef, 0xba, 0xd6, 0xdb, 0xde, 0xdb, 0xde, 0xdb, 0xde, 0xdb, 0xde, 0xdb, 0xde, 0xfb, 0xde, 0x1c, 0xdf, 0xfb, 0xde, 0xdb, 0xde, 0xdb, 0xde, 0xdb, 0xde, 0xdb, 0xde, 0x3c, 0xe7, 0xb7, 0xbd, 0xcb, 0x5a, 0x8e, 0x73, 
  0xff, 0xff, 0xff, 0xff, 0xbb, 0xde, 0x76, 0xb5, 0xd7, 0xbd, 0xd7, 0xbd, 0xd7, 0xbd, 0xd7, 0xbd, 0x18, 0xbe, 0xf8, 0xbd, 0x76, 0xbd, 0xb7, 0xbd, 0xd7, 0xbd, 0xd7, 0xbd, 0xd7, 0xbd, 0xd7, 0xbd, 0x59, 0xce, 0x92, 0x94, 0x4d, 0x6b, 0x51, 0x8c, 
  0xff, 0xff, 0xff, 0xff, 0xdb, 0xde, 0xd7, 0xbd, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0xfb, 0xbe, 0x1c, 0xbf, 0x0c, 0xe3, 0x61, 0xf8, 0xf3, 0xd4, 0x9a, 0xbe, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x9a, 0xd6, 0x55, 0xad, 0x6e, 0x73, 0x30, 0x84, 
  0xff, 0xff, 0xff, 0xff, 0xdb, 0xde, 0xd7, 0xbd, 0xf8, 0xc5, 0x79, 0xc6, 0x3c, 0xbf, 0xb3, 0xd4, 0xcb, 0xe2, 0x00, 0xf8, 0x00, 0xf8, 0xd3, 0xd4, 0xba, 0xbe, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x9a, 0xd6, 0x35, 0xad, 0x6d, 0x6b, 0x30, 0x84, 
  0xff, 0xff, 0xff, 0xff, 0xdb, 0xde, 0xd7, 0xbd, 0xba, 0xbe, 0xd3, 0xd4, 0xaa, 0xe2, 0x00, 0xf8, 0x00, 0xf8, 0x00, 0xf8, 0x00, 0xf8, 0xd3, 0xd4, 0x9a, 0xbe, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x9a, 0xd6, 0x35, 0xad, 0x6d, 0x6b, 0x30, 0x84, 
  0xff, 0xff, 0xff, 0xff, 0xdb, 0xde, 0x39, 0xb6, 0x96, 0xcd, 0x62, 0xf8, 0x00, 0xf8, 0x00, 0xf8, 0x00, 0xf8, 0x00, 0xf8, 0x00, 0xf8, 0xd3, 0xd4, 0x9a, 0xbe, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x9a, 0xd6, 0x35, 0xad, 0x6d, 0x6b, 0x30, 0x84, 
  0xff, 0xff, 0xff, 0xff, 0xdb, 0xde, 0xd7, 0xbd, 0x7a, 0xc6, 0xae, 0xdb, 0x66, 0xf1, 0x00, 0xf8, 0x00, 0xf8, 0x00, 0xf8, 0x00, 0xf8, 0xd3, 0xd4, 0x9a, 0xbe, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x9a, 0xd6, 0x35, 0xad, 0x6d, 0x6b, 0x30, 0x84, 
  0xff, 0xff, 0xff, 0xff, 0xdb, 0xde, 0xd7, 0xbd, 0x18, 0xc6, 0x59, 0xc6, 0xdb, 0xbe, 0x8e, 0xdb, 0xa6, 0xe9, 0x00, 0xf8, 0x00, 0xf8, 0xd3, 0xdc, 0x9a, 0xbe, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x9a, 0xd6, 0x35, 0xad, 0x6d, 0x6b, 0x30, 0x84, 
  0xff, 0xff, 0xff, 0xff, 0xdb, 0xde, 0xd7, 0xbd, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x1c, 0xbf, 0xdb, 0xd6, 0x49, 0xaa, 0x00, 0x68, 0xd3, 0xb4, 0x9a, 0xce, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x9a, 0xd6, 0x35, 0xad, 0x6d, 0x6b, 0x30, 0x84, 
  0xff, 0xff, 0xff, 0xff, 0xdb, 0xde, 0xd7, 0xbd, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x3d, 0xe7, 0x31, 0x64, 0x00, 0x00, 0xd3, 0x94, 0x9a, 0xde, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x9a, 0xd6, 0x35, 0xad, 0x6d, 0x6b, 0x30, 0x84, 
  0xff, 0xff, 0xff, 0xff, 0xdb, 0xde, 0xb7, 0xbd, 0x39, 0xce, 0xfb, 0xde, 0xfb, 0xde, 0xfb, 0xde, 0xdf, 0xff, 0x31, 0x8c, 0x00, 0x00, 0x96, 0xb5, 0x9e, 0xf7, 0xfb, 0xde, 0xfb, 0xde, 0x39, 0xce, 0x9a, 0xd6, 0x35, 0xad, 0x6d, 0x6b, 0x30, 0x84, 
  0xff, 0xff, 0xff, 0xff, 0xdb, 0xde, 0x18, 0xc6, 0x96, 0xb5, 0xaf, 0x7b, 0xaf, 0x7b, 0xaf, 0x7b, 0x31, 0x8c, 0x49, 0x4a, 0x00, 0x00, 0xec, 0x62, 0x10, 0x84, 0xaf, 0x7b, 0xaf, 0x7b, 0x96, 0xb5, 0xdb, 0xde, 0x35, 0xad, 0x6d, 0x6b, 0x30, 0x84, 
  0xff, 0xff, 0xff, 0xff, 0xdb, 0xde, 0x79, 0xce, 0xb2, 0x94, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x92, 0x94, 0x3d, 0xef, 0x35, 0xad, 0x6d, 0x6b, 0x30, 0x84, 
  0xff, 0xff, 0xff, 0xff, 0xdb, 0xde, 0x59, 0xce, 0xf3, 0x9c, 0x61, 0x08, 0x61, 0x08, 0x61, 0x08, 0x61, 0x08, 0x61, 0x08, 0x61, 0x08, 0x61, 0x08, 0x61, 0x08, 0x61, 0x08, 0x61, 0x08, 0xd3, 0x9c, 0x1c, 0xe7, 0x34, 0xa5, 0x6d, 0x6b, 0x30, 0x84, 
  0xff, 0xff, 0xff, 0xff, 0x5d, 0xef, 0x59, 0xce, 0x9a, 0xd6, 0x39, 0xce, 0x39, 0xce, 0x39, 0xce, 0x39, 0xce, 0x39, 0xce, 0x39, 0xce, 0x39, 0xce, 0x39, 0xce, 0x39, 0xce, 0x39, 0xce, 0x7a, 0xd6, 0x3d, 0xef, 0x76, 0xb5, 0x4d, 0x6b, 0x30, 0x84, 
  0xff, 0xff, 0xff, 0xff, 0xb6, 0xb5, 0x92, 0x94, 0x55, 0xad, 0x75, 0xad, 0x75, 0xad, 0x75, 0xad, 0x75, 0xad, 0x75, 0xad, 0x75, 0xad, 0x75, 0xad, 0x75, 0xad, 0x75, 0xad, 0x75, 0xad, 0x35, 0xad, 0x76, 0xb5, 0xb3, 0x9c, 0xae, 0x73, 0x31, 0x8c, 
  0x3c, 0xe7, 0xb7, 0xbd, 0xcb, 0x5a, 0x2d, 0x6b, 0x6d, 0x6b, 0x6d, 0x6b, 0x6d, 0x6b, 0x6d, 0x6b, 0x6d, 0x6b, 0x6d, 0x6b, 0x6d, 0x6b, 0x6d, 0x6b, 0x6d, 0x6b, 0x6d, 0x6b, 0x6d, 0x6b, 0x6d, 0x6b, 0x4d, 0x6b, 0xae, 0x73, 0x51, 0x8c, 0xcf, 0x7b, 
  0x39, 0xce, 0xb3, 0x9c, 0x8e, 0x73, 0x51, 0x8c, 0x30, 0x84, 0x30, 0x84, 0x30, 0x84, 0x30, 0x84, 0x30, 0x84, 0x30, 0x84, 0x30, 0x84, 0x30, 0x84, 0x30, 0x84, 0x30, 0x84, 0x30, 0x84, 0x30, 0x84, 0x30, 0x84, 0x31, 0x8c, 0xcf, 0x7b, 0xcb, 0x5a, 
#endif
#if LV_COLOR_DEPTH == 16 && LV_COLOR_16_SWAP != 0
  /*Pixel format: Red: 5 bit, Green: 6 bit, Blue: 5 bit BUT the 2 bytes are swapped*/
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xef, 0x5d, 0xc6, 0x38, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xb5, 0xb6, 0x9c, 0xb3, 
  0xff, 0xff, 0xff, 0xff, 0xef, 0x5d, 0xd6, 0xba, 0xde, 0xdb, 0xde, 0xdb, 0xde, 0xdb, 0xde, 0xdb, 0xde, 0xdb, 0xde, 0xfb, 0xdf, 0x1c, 0xde, 0xfb, 0xde, 0xdb, 0xde, 0xdb, 0xde, 0xdb, 0xde, 0xdb, 0xe7, 0x3c, 0xbd, 0xb7, 0x5a, 0xcb, 0x73, 0x8e, 
  0xff, 0xff, 0xff, 0xff, 0xde, 0xbb, 0xb5, 0x76, 0xbd, 0xd7, 0xbd, 0xd7, 0xbd, 0xd7, 0xbd, 0xd7, 0xbe, 0x18, 0xbd, 0xf8, 0xbd, 0x76, 0xbd, 0xb7, 0xbd, 0xd7, 0xbd, 0xd7, 0xbd, 0xd7, 0xbd, 0xd7, 0xce, 0x59, 0x94, 0x92, 0x6b, 0x4d, 0x8c, 0x51, 
  0xff, 0xff, 0xff, 0xff, 0xde, 0xdb, 0xbd, 0xd7, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0xbe, 0xfb, 0xbf, 0x1c, 0xe3, 0x0c, 0xf8, 0x61, 0xd4, 0xf3, 0xbe, 0x9a, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0xd6, 0x9a, 0xad, 0x55, 0x73, 0x6e, 0x84, 0x30, 
  0xff, 0xff, 0xff, 0xff, 0xde, 0xdb, 0xbd, 0xd7, 0xc5, 0xf8, 0xc6, 0x79, 0xbf, 0x3c, 0xd4, 0xb3, 0xe2, 0xcb, 0xf8, 0x00, 0xf8, 0x00, 0xd4, 0xd3, 0xbe, 0xba, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0xd6, 0x9a, 0xad, 0x35, 0x6b, 0x6d, 0x84, 0x30, 
  0xff, 0xff, 0xff, 0xff, 0xde, 0xdb, 0xbd, 0xd7, 0xbe, 0xba, 0xd4, 0xd3, 0xe2, 0xaa, 0xf8, 0x00, 0xf8, 0x00, 0xf8, 0x00, 0xf8, 0x00, 0xd4, 0xd3, 0xbe, 0x9a, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0xd6, 0x9a, 0xad, 0x35, 0x6b, 0x6d, 0x84, 0x30, 
  0xff, 0xff, 0xff, 0xff, 0xde, 0xdb, 0xb6, 0x39, 0xcd, 0x96, 0xf8, 0x62, 0xf8, 0x00, 0xf8, 0x00, 0xf8, 0x00, 0xf8, 0x00, 0xf8, 0x00, 0xd4, 0xd3, 0xbe, 0x9a, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0xd6, 0x9a, 0xad, 0x35, 0x6b, 0x6d, 0x84, 0x30, 
  0xff, 0xff, 0xff, 0xff, 0xde, 0xdb, 0xbd, 0xd7, 0xc6, 0x7a, 0xdb, 0xae, 0xf1, 0x66, 0xf8, 0x00, 0xf8, 0x00, 0xf8, 0x00, 0xf8, 0x00, 0xd4, 0xd3, 0xbe, 0x9a, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0xd6, 0x9a, 0xad, 0x35, 0x6b, 0x6d, 0x84, 0x30, 
  0xff, 0xff, 0xff, 0xff, 0xde, 0xdb, 0xbd, 0xd7, 0xc6, 0x18, 0xc6, 0x59, 0xbe, 0xdb, 0xdb, 0x8e, 0xe9, 0xa6, 0xf8, 0x00, 0xf8, 0x00, 0xdc, 0xd3, 0xbe, 0x9a, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0xd6, 0x9a, 0xad, 0x35, 0x6b, 0x6d, 0x84, 0x30, 
  0xff, 0xff, 0xff, 0xff, 0xde, 0xdb, 0xbd, 0xd7, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0xbf, 0x1c, 0xd6, 0xdb, 0xaa, 0x49, 0x68, 0x00, 0xb4, 0xd3, 0xce, 0x9a, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0xd6, 0x9a, 0xad, 0x35, 0x6b, 0x6d, 0x84, 0x30, 
  0xff, 0xff, 0xff, 0xff, 0xde, 0xdb, 0xbd, 0xd7, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0xe7, 0x3d, 0x64, 0x31, 0x00, 0x00, 0x94, 0xd3, 0xde, 0x9a, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0xd6, 0x9a, 0xad, 0x35, 0x6b, 0x6d, 0x84, 0x30, 
  0xff, 0xff, 0xff, 0xff, 0xde, 0xdb, 0xbd, 0xb7, 0xce, 0x39, 0xde, 0xfb, 0xde, 0xfb, 0xde, 0xfb, 0xff, 0xdf, 0x8c, 0x31, 0x00, 0x00, 0xb5, 0x96, 0xf7, 0x9e, 0xde, 0xfb, 0xde, 0xfb, 0xce, 0x39, 0xd6, 0x9a, 0xad, 0x35, 0x6b, 0x6d, 0x84, 0x30, 
  0xff, 0xff, 0xff, 0xff, 0xde, 0xdb, 0xc6, 0x18, 0xb5, 0x96, 0x7b, 0xaf, 0x7b, 0xaf, 0x7b, 0xaf, 0x8c, 0x31, 0x4a, 0x49, 0x00, 0x00, 0x62, 0xec, 0x84, 0x10, 0x7b, 0xaf, 0x7b, 0xaf, 0xb5, 0x96, 0xde, 0xdb, 0xad, 0x35, 0x6b, 0x6d, 0x84, 0x30, 
  0xff, 0xff, 0xff, 0xff, 0xde, 0xdb, 0xce, 0x79, 0x94, 0xb2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x94, 0x92, 0xef, 0x3d, 0xad, 0x35, 0x6b, 0x6d, 0x84, 0x30, 
  0xff, 0xff, 0xff, 0xff, 0xde, 0xdb, 0xce, 0x59, 0x9c, 0xf3, 0x08, 0x61, 0x08, 0x61, 0x08, 0x61, 0x08, 0x61, 0x08, 0x61, 0x08, 0x61, 0x08, 0x61, 0x08, 0x61, 0x08, 0x61, 0x08, 0x61, 0x9c, 0xd3, 0xe7, 0x1c, 0xa5, 0x34, 0x6b, 0x6d, 0x84, 0x30, 
  0xff, 0xff, 0xff, 0xff, 0xef, 0x5d, 0xce, 0x59, 0xd6, 0x9a, 0xce, 0x39, 0xce, 0x39, 0xce, 0x39, 0xce, 0x39, 0xce, 0x39, 0xce, 0x39, 0xce, 0x39, 0xce, 0x39, 0xce, 0x39, 0xce, 0x39, 0xd6, 0x7a, 0xef, 0x3d, 0xb5, 0x76, 0x6b, 0x4d, 0x84, 0x30, 
  0xff, 0xff, 0xff, 0xff, 0xb5, 0xb6, 0x94, 0x92, 0xad, 0x55, 0xad, 0x75, 0xad, 0x75, 0xad, 0x75, 0xad, 0x75, 0xad, 0x75, 0xad, 0x75, 0xad, 0x75, 0xad, 0x75, 0xad, 0x75, 0xad, 0x75, 0xad, 0x35, 0xb5, 0x76, 0x9c, 0xb3, 0x73, 0xae, 0x8c, 0x31, 
  0xe7, 0x3c, 0xbd, 0xb7, 0x5a, 0xcb, 0x6b, 0x2d, 0x6b, 0x6d, 0x6b, 0x6d, 0x6b, 0x6d, 0x6b, 0x6d, 0x6b, 0x6d, 0x6b, 0x6d, 0x6b, 0x6d, 0x6b, 0x6d, 0x6b, 0x6d, 0x6b, 0x6d, 0x6b, 0x6d, 0x6b, 0x6d, 0x6b, 0x4d, 0x73, 0xae, 0x8c, 0x51, 0x7b, 0xcf, 
  0xce, 0x39, 0x9c, 0xb3, 0x73, 0x8e, 0x8c, 0x51, 0x84, 0x30, 0x84, 0x30, 0x84, 0x30, 0x84, 0x30, 0x84, 0x30, 0x84, 0x30, 0x84, 0x30, 0x84, 0x30, 0x84, 0x30, 0x84, 0x30, 0x84, 0x30, 0x84, 0x30, 0x84, 0x30, 0x8c, 0x31, 0x7b, 0xcf, 0x5a, 0xcb, 
#endif
#if LV_COLOR_DEPTH == 32
  /*Pixel format: Fix 0xFF: 8 bit, Red: 8 bit, Green: 8 bit, Blue: 8 bit*/
  0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe7, 0xe7, 0xe7, 0xff, 0xc2, 0xc2, 0xc2, 0xff, 
  0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xb3, 0xb3, 0xb3, 0xff, 0x94, 0x94, 0x94, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe8, 0xe8, 0xe8, 0xff, 0xd3, 0xd3, 0xd3, 0xff, 0xd9, 0xd9, 0xd9, 0xff, 0xd9, 0xd9, 0xd9, 0xff, 0xd9, 0xd9, 0xd9, 0xff, 0xd9, 0xd9, 0xd9, 0xff, 0xd8, 0xd8, 0xd9, 0xff, 0xdb, 0xdb, 0xd8, 0xff, 0xdf, 0xdf, 0xd7, 0xff, 0xda, 0xda, 0xd8, 0xff, 0xd8, 0xd8, 0xd9, 0xff, 0xd9, 0xd9, 0xd9, 0xff, 0xd9, 0xd9, 0xd9, 0xff, 0xd9, 0xd9, 0xd9, 0xff, 0xe2, 0xe2, 0xe2, 0xff, 0xb5, 0xb5, 0xb5, 0xff, 0x57, 0x57, 0x57, 0xff, 0x6f, 0x6f, 0x6f, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xd4, 0xd4, 0xd4, 0xff, 0xad, 0xad, 0xad, 0xff, 0xb7, 0xb7, 0xb7, 0xff, 0xb7, 0xb7, 0xb7, 0xff, 0xb7, 0xb7, 0xb7, 0xff, 0xb6, 0xb6, 0xb8, 0xff, 0xbf, 0xbf, 0xb5, 0xff, 0xbd, 0xbd, 0xb5, 0xff, 0xac, 0xac, 0xbb, 0xff, 0xb5, 0xb5, 0xb8, 0xff, 0xb8, 0xb8, 0xb7, 0xff, 0xb7, 0xb7, 0xb7, 0xff, 0xb7, 0xb7, 0xb7, 0xff, 0xb6, 0xb6, 0xb6, 0xff, 0xc9, 0xc9, 0xc9, 0xff, 0x91, 0x91, 0x91, 0xff, 0x66, 0x66, 0x66, 0xff, 0x88, 0x88, 0x88, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xd9, 0xd9, 0xd9, 0xff, 0xb7, 0xb7, 0xb7, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xbe, 0xbe, 0xc1, 0xff, 0xdb, 0xdb, 0xb7, 0xff, 0xe1, 0xe1, 0xb5, 0xff, 0x61, 0x61, 0xdf, 0xff, 0x0b, 0x0b, 0xfb, 0xff, 0x9b, 0x9b, 0xcc, 0xff, 0xd0, 0xd0, 0xba, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xbf, 0xbf, 0xbf, 0xff, 0xd0, 0xd0, 0xd0, 0xff, 0xa6, 0xa6, 0xa6, 0xff, 0x6c, 0x6c, 0x6c, 0xff, 0x83, 0x83, 0x83, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xd9, 0xd9, 0xd9, 0xff, 0xb7, 0xb7, 0xb7, 0xff, 0xbc, 0xbc, 0xc1, 0xff, 0xcb, 0xcb, 0xbc, 0xff, 0xe3, 0xe3, 0xb4, 0xff, 0x95, 0x95, 0xce, 0xff, 0x59, 0x59, 0xe2, 0xff, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0x98, 0x98, 0xcd, 0xff, 0xd2, 0xd2, 0xba, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xbf, 0xbf, 0xbf, 0xff, 0xd0, 0xd0, 0xd0, 0xff, 0xa4, 0xa4, 0xa4, 0xff, 0x6b, 0x6b, 0x6b, 0xff, 0x83, 0x83, 0x83, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xd9, 0xd9, 0xd9, 0xff, 0xb6, 0xb6, 0xb7, 0xff, 0xd3, 0xd3, 0xba, 0xff, 0x97, 0x97, 0xcd, 0xff, 0x53, 0x53, 0xe3, 0xff, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0x99, 0x99, 0xcd, 0xff, 0xd1, 0xd1, 0xba, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xbf, 0xbf, 0xbf, 0xff, 0xd0, 0xd0, 0xd0, 0xff, 0xa4, 0xa4, 0xa4, 0xff, 0x6b, 0x6b, 0x6b, 0xff, 0x83, 0x83, 0x83, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xd9, 0xd9, 0xd9, 0xff, 0xc4, 0xc4, 0xb3, 0xff, 0xb0, 0xb0, 0xc5, 0xff, 0x0d, 0x0d, 0xfb, 0xff, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0x99, 0x99, 0xcd, 0xff, 0xd1, 0xd1, 0xba, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xbf, 0xbf, 0xbf, 0xff, 0xd0, 0xd0, 0xd0, 0xff, 0xa4, 0xa4, 0xa4, 0xff, 0x6b, 0x6b, 0x6b, 0xff, 0x83, 0x83, 0x83, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xd9, 0xd9, 0xd9, 0xff, 0xb9, 0xb9, 0xb6, 0xff, 0xcc, 0xcc, 0xbc, 0xff, 0x73, 0x73, 0xd9, 0xff, 0x2c, 0x2c, 0xf1, 0xff, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0x99, 0x99, 0xcd, 0xff, 0xd1, 0xd1, 0xba, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xbf, 0xbf, 0xbf, 0xff, 0xd0, 0xd0, 0xd0, 0xff, 0xa4, 0xa4, 0xa4, 0xff, 0x6b, 0x6b, 0x6b, 0xff, 0x83, 0x83, 0x83, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xd9, 0xd9, 0xd9, 0xff, 0xb6, 0xb6, 0xb7, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xc9, 0xc9, 0xbd, 0xff, 0xd8, 0xd8, 0xb8, 0xff, 0x6f, 0x6f, 0xda, 0xff, 0x33, 0x33, 0xe9, 0xff, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0x99, 0x99, 0xd4, 0xff, 0xd1, 0xd1, 0xb7, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xbf, 0xbf, 0xbf, 0xff, 0xd0, 0xd0, 0xd0, 0xff, 0xa4, 0xa4, 0xa4, 0xff, 0x6b, 0x6b, 0x6b, 0xff, 0x83, 0x83, 0x83, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xd9, 0xd9, 0xd9, 0xff, 0xb7, 0xb7, 0xb7, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xbe, 0xbe, 0xc1, 0xff, 0xdf, 0xdf, 0xb6, 0xff, 0xd7, 0xd7, 0xce, 0xff, 0x46, 0x46, 0xab, 0xff, 0x00, 0x00, 0x65, 0xff, 0x99, 0x99, 0xae, 0xff, 0xd1, 0xd1, 0xc8, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xbf, 0xbf, 0xbf, 0xff, 0xd0, 0xd0, 0xd0, 0xff, 0xa4, 0xa4, 0xa4, 0xff, 0x6b, 0x6b, 0x6b, 0xff, 0x83, 0x83, 0x83, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xd9, 0xd9, 0xd9, 0xff, 0xb7, 0xb7, 0xb7, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xbe, 0xbe, 0xc1, 0xff, 0xe4, 0xe4, 0xdd, 0xff, 0x84, 0x84, 0x61, 0xff, 0x00, 0x00, 0x00, 0xff, 0x99, 0x99, 0x92, 0xff, 0xd1, 0xd1, 0xd4, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xbf, 0xbf, 0xbf, 0xff, 0xd0, 0xd0, 0xd0, 0xff, 0xa4, 0xa4, 0xa4, 0xff, 0x6b, 0x6b, 0x6b, 0xff, 0x83, 0x83, 0x83, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xd9, 0xd9, 0xd9, 0xff, 0xb5, 0xb5, 0xb5, 0xff, 0xc5, 0xc5, 0xc5, 0xff, 0xdb, 0xdb, 0xdb, 0xff, 0xdb, 0xdb, 0xdb, 0xff, 0xdb, 0xdb, 0xdb, 0xff, 0xf9, 0xf9, 0xf9, 0xff, 0x84, 0x84, 0x84, 0xff, 0x00, 0x00, 0x00, 0xff, 0xae, 0xae, 0xae, 0xff, 0xee, 0xee, 0xee, 0xff, 0xdb, 0xdb, 0xdb, 0xff, 0xdb, 0xdb, 0xdb, 0xff, 0xc4, 0xc4, 0xc4, 0xff, 0xce, 0xce, 0xce, 0xff, 0xa4, 0xa4, 0xa4, 0xff, 0x6b, 0x6b, 0x6b, 0xff, 0x83, 0x83, 0x83, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xd9, 0xd9, 0xd9, 0xff, 0xbe, 0xbe, 0xbe, 0xff, 0xb1, 0xb1, 0xb1, 0xff, 0x74, 0x74, 0x74, 0xff, 0x74, 0x74, 0x74, 0xff, 0x74, 0x74, 0x74, 0xff, 0x85, 0x85, 0x85, 0xff, 0x46, 0x46, 0x46, 0xff, 0x00, 0x00, 0x00, 0xff, 0x5d, 0x5d, 0x5d, 0xff, 0x7f, 0x7f, 0x7f, 0xff, 0x74, 0x74, 0x74, 0xff, 0x74, 0x74, 0x74, 0xff, 0xb0, 0xb0, 0xb0, 0xff, 0xd7, 0xd7, 0xd7, 0xff, 0xa4, 0xa4, 0xa4, 0xff, 0x6b, 0x6b, 0x6b, 0xff, 0x83, 0x83, 0x83, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xd9, 0xd9, 0xd9, 0xff, 0xcb, 0xcb, 0xcb, 0xff, 0x92, 0x92, 0x92, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x91, 0x91, 0x91, 0xff, 0xe4, 0xe4, 0xe4, 0xff, 0xa4, 0xa4, 0xa4, 0xff, 0x6b, 0x6b, 0x6b, 0xff, 0x83, 0x83, 0x83, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xd9, 0xd9, 0xd9, 0xff, 0xc6, 0xc6, 0xc6, 0xff, 0x9a, 0x9a, 0x9a, 0xff, 0x0a, 0x0a, 0x0a, 0xff, 0x0a, 0x0a, 0x0a, 0xff, 0x0a, 0x0a, 0x0a, 0xff, 0x0a, 0x0a, 0x0a, 0xff, 0x0a, 0x0a, 0x0a, 0xff, 0x0a, 0x0a, 0x0a, 0xff, 0x0a, 0x0a, 0x0a, 0xff, 0x0a, 0x0a, 0x0a, 0xff, 0x0a, 0x0a, 0x0a, 0xff, 0x0a, 0x0a, 0x0a, 0xff, 0x99, 0x99, 0x99, 0xff, 0xdf, 0xdf, 0xdf, 0xff, 0xa3, 0xa3, 0xa3, 0xff, 0x6b, 0x6b, 0x6b, 0xff, 0x83, 0x83, 0x83, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe7, 0xe7, 0xe7, 0xff, 0xc9, 0xc9, 0xc9, 0xff, 0xce, 0xce, 0xce, 0xff, 0xc5, 0xc5, 0xc5, 0xff, 0xc5, 0xc5, 0xc5, 0xff, 0xc5, 0xc5, 0xc5, 0xff, 0xc5, 0xc5, 0xc5, 0xff, 0xc5, 0xc5, 0xc5, 0xff, 0xc5, 0xc5, 0xc5, 0xff, 0xc5, 0xc5, 0xc5, 0xff, 0xc5, 0xc5, 0xc5, 0xff, 0xc5, 0xc5, 0xc5, 0xff, 0xc5, 0xc5, 0xc5, 0xff, 0xcc, 0xcc, 0xcc, 0xff, 0xe4, 0xe4, 0xe4, 0xff, 0xad, 0xad, 0xad, 0xff, 0x67, 0x67, 0x67, 0xff, 0x83, 0x83, 0x83, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xb3, 0xb3, 0xb3, 0xff, 0x91, 0x91, 0x91, 0xff, 0xa7, 0xa7, 0xa7, 0xff, 0xaa, 0xaa, 0xaa, 0xff, 0xaa, 0xaa, 0xaa, 0xff, 0xaa, 0xaa, 0xaa, 0xff, 0xaa, 0xaa, 0xaa, 0xff, 0xaa, 0xaa, 0xaa, 0xff, 0xaa, 0xaa, 0xaa, 0xff, 0xaa, 0xaa, 0xaa, 0xff, 0xaa, 0xaa, 0xaa, 0xff, 0xaa, 0xaa, 0xaa, 0xff, 0xaa, 0xaa, 0xaa, 0xff, 0xa5, 0xa5, 0xa5, 0xff, 0xac, 0xac, 0xac, 0xff, 0x94, 0x94, 0x94, 0xff, 0x73, 0x73, 0x73, 0xff, 0x84, 0x84, 0x84, 0xff, 
  0xe2, 0xe2, 0xe2, 0xff, 0xb5, 0xb5, 0xb5, 0xff, 0x57, 0x57, 0x57, 0xff, 0x65, 0x65, 0x65, 0xff, 0x6b, 0x6b, 0x6b, 0xff, 0x6b, 0x6b, 0x6b, 0xff, 0x6b, 0x6b, 0x6b, 0xff, 0x6b, 0x6b, 0x6b, 0xff, 0x6b, 0x6b, 0x6b, 0xff, 0x6b, 0x6b, 0x6b, 0xff, 0x6b, 0x6b, 0x6b, 0xff, 0x6b, 0x6b, 0x6b, 0xff, 0x6b, 0x6b, 0x6b, 0xff, 0x6b, 0x6b, 0x6b, 0xff, 0x6b, 0x6b, 0x6b, 0xff, 0x6b, 0x6b, 0x6b, 0xff, 0x67, 0x67, 0x67, 0xff, 0x73, 0x73, 0x73, 0xff, 0x86, 0x86, 0x86, 0xff, 0x78, 0x78, 0x78, 0xff, 
  0xc4, 0xc4, 0xc4, 0xff, 0x94, 0x94, 0x94, 0xff, 0x6f, 0x6f, 0x6f, 0xff, 0x88, 0x88, 0x88, 0xff, 0x82, 0x82, 0x82, 0xff, 0x83, 0x83, 0x83, 0xff, 0x83, 0x83, 0x83, 0xff, 0x83, 0x83, 0x83, 0xff, 0x83, 0x83, 0x83, 0xff, 0x83, 0x83, 0x83, 0xff, 0x83, 0x83, 0x83, 0xff, 0x83, 0x83, 0x83, 0xff, 0x83, 0x83, 0x83, 0xff, 0x83, 0x83, 0x83, 0xff, 0x83, 0x83, 0x83, 0xff, 0x83, 0x83, 0x83, 0xff, 0x83, 0x83, 0x83, 0xff, 0x84, 0x84, 0x84, 0xff, 0x78, 0x78, 0x78, 0xff, 0x58, 0x58, 0x58, 0xff, 
#endif
};

const lv_img_dsc_t game_minesweeper_img_flag_big = {
  .header.cf = LV_IMG_CF_TRUE_COLOR,
  .header.always_zero = 0,
  .header.reserved = 0,
  .header.w = 20,
  .header.h = 20,
  .data_size = 400 * LV_COLOR_SIZE / 8,
  .data = game_minesweeper_img_flag_big_map,
};
