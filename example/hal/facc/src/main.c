#include "bf0_hal.h"
#include "stdio.h"
#include "string.h"
#include "rtthread.h"
#include "bf0_hal_facc.h"
#include "facc.h"
// #include "utest.h"

FACC_HandleTypeDef facc;
FACC_ConfigTypeDef *param;

uint8_t facc_output [1024];

/*********************************fir************************************* */
uint32_t fir_fir_param = 0x0;
uint8_t fir_fir_coef_b[] =
{
    0x30, 0xff, 0x9a, 0x0, 0xe7, 0x2, 0x15, 0x6, 0xe1, 0x9, 0xce, 0xd, 0x37, 0x11, 0x7c, 0x13,
    0x2e, 0x14, 0x2c, 0x13, 0xb1, 0x10, 0x3c, 0xd, 0x6a, 0x9, 0xcf, 0x5, 0xd0, 0x2, 0x9d, 0x0,
    0x35, 0xff,
};//Filtering coefficient
uint8_t __ALIGNED(4) fir_fir_input[] =
{
    0x0, 0x0, 0x60, 0x2e, 0xd6, 0x44, 0x73, 0x39, 0xb, 0x16, 0x6c, 0xf2, 0x67, 0xe6, 0xd0, 0xfb,
    0xbb, 0x28, 0x41, 0x55, 0x7e, 0x69, 0x87, 0x5b, 0x37, 0x35, 0x64, 0xe, 0xe5, 0xfe, 0x98, 0x10,
    0x9a, 0x39, 0xd, 0x62, 0x18, 0x72, 0xd9, 0x5f, 0x37, 0x35, 0x12, 0xa, 0x4b, 0xf6, 0xcc, 0x3,
    0xbb, 0x28, 0x45, 0x4d, 0x9a, 0x59, 0xe2, 0x43, 0xb, 0x16, 0xfe, 0xe7, 0xa3, 0xd1, 0xeb, 0xdc,
    0x0, 0x0, 0x15, 0x23, 0x5d, 0x2e, 0x2, 0x18, 0xf5, 0xe9, 0x1e, 0xbc, 0x66, 0xa6, 0xbb, 0xb2,
    0x45, 0xd7, 0x34, 0xfc, 0xb5, 0x9, 0xee, 0xf5, 0xc9, 0xca, 0x27, 0xa0, 0xe8, 0x8d, 0xf3, 0x9d,
    0x66, 0xc6, 0x68, 0xef, 0x1b, 0x1, 0x9c, 0xf1, 0xc9, 0xca, 0x79, 0xa4, 0x82, 0x96, 0xbf, 0xaa,
    0x45, 0xd7, 0x30, 0x4, 0x99, 0x19, 0x94, 0xd, 0xf5, 0xe9, 0x8d, 0xc6, 0x2a, 0xbb, 0xa0, 0xd1,
    0x0, 0x0, 0x60, 0x2e, 0xd6, 0x44, 0x73, 0x39, 0xb, 0x16, 0x6c, 0xf2, 0x67, 0xe6, 0xd0, 0xfb,
    0xbb, 0x28, 0x41, 0x55, 0x7e, 0x69, 0x87, 0x5b, 0x37, 0x35, 0x64, 0xe, 0xe5, 0xfe, 0x98, 0x10,
    0x9a, 0x39, 0xd, 0x62, 0x18, 0x72, 0xd9, 0x5f, 0x37, 0x35, 0x12, 0xa, 0x4b, 0xf6, 0xcc, 0x3,
    0xbb, 0x28, 0x45, 0x4d, 0x9a, 0x59, 0xe2, 0x43, 0xb, 0x16, 0xfe, 0xe7, 0xa3, 0xd1, 0xeb, 0xdc,
    0x0, 0x0, 0x15, 0x23, 0x5d, 0x2e, 0x2, 0x18, 0xf5, 0xe9, 0x1e, 0xbc, 0x66, 0xa6, 0xbb, 0xb2,
    0x45, 0xd7, 0x34, 0xfc, 0xb5, 0x9, 0xee, 0xf5, 0xc9, 0xca, 0x27, 0xa0, 0xe8, 0x8d, 0xf3, 0x9d,
    0x66, 0xc6, 0x68, 0xef, 0x1b, 0x1, 0x9c, 0xf1, 0xc9, 0xca, 0x79, 0xa4, 0x82, 0x96, 0xbf, 0xaa,
    0x45, 0xd7, 0x30, 0x4, 0x99, 0x19, 0x94, 0xd, 0xf5, 0xe9, 0x8d, 0xc6, 0x2a, 0xbb, 0xa0, 0xd1,
    0x0, 0x0, 0x60, 0x2e, 0xd6, 0x44, 0x73, 0x39, 0xb, 0x16, 0x6c, 0xf2, 0x67, 0xe6, 0xd0, 0xfb,
    0xbb, 0x28, 0x41, 0x55, 0x7e, 0x69, 0x87, 0x5b, 0x37, 0x35, 0x64, 0xe, 0xe5, 0xfe, 0x98, 0x10,
    0x9a, 0x39, 0xd, 0x62, 0x18, 0x72, 0xd9, 0x5f, 0x37, 0x35, 0x12, 0xa, 0x4b, 0xf6, 0xcc, 0x3,
    0xbb, 0x28, 0x45, 0x4d, 0x9a, 0x59, 0xe2, 0x43, 0xb, 0x16, 0xfe, 0xe7, 0xa3, 0xd1, 0xeb, 0xdc,
    0x0, 0x0, 0x15, 0x23, 0x5d, 0x2e, 0x2, 0x18, 0xf5, 0xe9, 0x1e, 0xbc, 0x66, 0xa6, 0xbb, 0xb2,
    0x45, 0xd7, 0x34, 0xfc, 0xb5, 0x9, 0xee, 0xf5, 0xc9, 0xca, 0x27, 0xa0, 0xe8, 0x8d, 0xf3, 0x9d,
    0x66, 0xc6, 0x68, 0xef, 0x1b, 0x1, 0x9c, 0xf1, 0xc9, 0xca, 0x79, 0xa4, 0x82, 0x96, 0xbf, 0xaa,
    0x45, 0xd7, 0x30, 0x4, 0x99, 0x19, 0x94, 0xd, 0xf5, 0xe9, 0x8d, 0xc6, 0x2a, 0xbb, 0xa0, 0xd1,
    0x0, 0x0, 0x60, 0x2e, 0xd6, 0x44, 0x73, 0x39, 0xb, 0x16, 0x6c, 0xf2, 0x67, 0xe6, 0xd0, 0xfb,
    0xbb, 0x28, 0x41, 0x55, 0x7e, 0x69, 0x87, 0x5b, 0x37, 0x35, 0x64, 0xe, 0xe5, 0xfe, 0x98, 0x10,
    0x9a, 0x39, 0xd, 0x62, 0x18, 0x72, 0xd9, 0x5f, 0x37, 0x35, 0x12, 0xa, 0x4b, 0xf6, 0xcc, 0x3,
    0xbb, 0x28, 0x45, 0x4d, 0x9a, 0x59, 0xe2, 0x43, 0xb, 0x16, 0xfe, 0xe7, 0xa3, 0xd1, 0xeb, 0xdc,
    0x0, 0x0, 0x15, 0x23, 0x5d, 0x2e, 0x2, 0x18, 0xf5, 0xe9, 0x1e, 0xbc, 0x66, 0xa6, 0xbb, 0xb2,
    0x45, 0xd7, 0x34, 0xfc, 0xb5, 0x9, 0xee, 0xf5, 0xc9, 0xca, 0x27, 0xa0, 0xe8, 0x8d, 0xf3, 0x9d,
    0x66, 0xc6, 0x68, 0xef, 0x1b, 0x1, 0x9c, 0xf1, 0xc9, 0xca, 0x79, 0xa4, 0x82, 0x96, 0xbf, 0xaa,
    0x45, 0xd7, 0x30, 0x4, 0x99, 0x19, 0x94, 0xd, 0xf5, 0xe9, 0x8d, 0xc6, 0x2a, 0xbb, 0xa0, 0xd1,
    0x0, 0x0, 0x60, 0x2e, 0xd6, 0x44, 0x73, 0x39, 0xb, 0x16, 0x6c, 0xf2, 0x67, 0xe6, 0xd0, 0xfb,
    0xbb, 0x28, 0x41, 0x55, 0x7e, 0x69, 0x87, 0x5b, 0x37, 0x35, 0x64, 0xe, 0xe5, 0xfe, 0x98, 0x10,
    0x9a, 0x39, 0xd, 0x62, 0x18, 0x72, 0xd9, 0x5f, 0x37, 0x35, 0x12, 0xa, 0x4b, 0xf6, 0xcc, 0x3,
    0xbb, 0x28, 0x45, 0x4d, 0x9a, 0x59, 0xe2, 0x43, 0xb, 0x16, 0xfe, 0xe7, 0xa3, 0xd1, 0xeb, 0xdc,
    0x0, 0x0, 0x15, 0x23, 0x5d, 0x2e, 0x2, 0x18, 0xf5, 0xe9, 0x1e, 0xbc, 0x66, 0xa6, 0xbb, 0xb2,
    0x45, 0xd7, 0x34, 0xfc, 0xb5, 0x9, 0xee, 0xf5, 0xc9, 0xca, 0x27, 0xa0, 0xe8, 0x8d, 0xf3, 0x9d,
    0x66, 0xc6, 0x68, 0xef, 0x1b, 0x1, 0x9c, 0xf1, 0xc9, 0xca, 0x79, 0xa4, 0x82, 0x96, 0xbf, 0xaa,
    0x45, 0xd7, 0x30, 0x4, 0x99, 0x19, 0x94, 0xd, 0xf5, 0xe9, 0x8d, 0xc6, 0x2a, 0xbb, 0xa0, 0xd1,
    0x0, 0x0, 0x60, 0x2e, 0xd6, 0x44, 0x73, 0x39, 0xb, 0x16, 0x6c, 0xf2, 0x67, 0xe6, 0xd0, 0xfb,
    0xbb, 0x28, 0x41, 0x55, 0x7e, 0x69, 0x87, 0x5b, 0x37, 0x35, 0x64, 0xe, 0xe5, 0xfe, 0x98, 0x10,
    0x9a, 0x39, 0xd, 0x62, 0x18, 0x72, 0xd9, 0x5f, 0x37, 0x35, 0x12, 0xa, 0x4b, 0xf6, 0xcc, 0x3,
    0xbb, 0x28, 0x45, 0x4d, 0x9a, 0x59, 0xe2, 0x43, 0xb, 0x16, 0xfe, 0xe7, 0xa3, 0xd1, 0xeb, 0xdc,
    0x0, 0x0, 0x15, 0x23, 0x5d, 0x2e, 0x2, 0x18, 0xf5, 0xe9, 0x1e, 0xbc, 0x66, 0xa6, 0xbb, 0xb2,
    0x45, 0xd7, 0x34, 0xfc, 0xb5, 0x9, 0xee, 0xf5, 0xc9, 0xca, 0x27, 0xa0, 0xe8, 0x8d, 0xf3, 0x9d,
    0x66, 0xc6, 0x68, 0xef, 0x1b, 0x1, 0x9c, 0xf1, 0xc9, 0xca, 0x79, 0xa4, 0x82, 0x96, 0xbf, 0xaa,
    0x45, 0xd7, 0x30, 0x4, 0x99, 0x19, 0x94, 0xd, 0xf5, 0xe9, 0x8d, 0xc6, 0x2a, 0xbb, 0xa0, 0xd1,
    0x0, 0x0, 0x60, 0x2e, 0xd6, 0x44, 0x73, 0x39, 0xb, 0x16, 0x6c, 0xf2, 0x67, 0xe6, 0xd0, 0xfb,
    0xbb, 0x28, 0x41, 0x55, 0x7e, 0x69, 0x87, 0x5b, 0x37, 0x35, 0x64, 0xe, 0xe5, 0xfe, 0x98, 0x10,
    0x9a, 0x39, 0xd, 0x62, 0x18, 0x72, 0xd9, 0x5f, 0x37, 0x35, 0x12, 0xa, 0x4b, 0xf6, 0xcc, 0x3,
    0xbb, 0x28, 0x45, 0x4d, 0x9a, 0x59, 0xe2, 0x43, 0xb, 0x16, 0xfe, 0xe7, 0xa3, 0xd1, 0xeb, 0xdc,
    0x0, 0x0, 0x15, 0x23, 0x5d, 0x2e, 0x2, 0x18, 0xf5, 0xe9, 0x1e, 0xbc, 0x66, 0xa6, 0xbb, 0xb2,
    0x45, 0xd7, 0x34, 0xfc, 0xb5, 0x9, 0xee, 0xf5, 0xc9, 0xca, 0x27, 0xa0, 0xe8, 0x8d, 0xf3, 0x9d,
    0x66, 0xc6, 0x68, 0xef, 0x1b, 0x1, 0x9c, 0xf1, 0xc9, 0xca, 0x79, 0xa4, 0x82, 0x96, 0xbf, 0xaa,
    0x45, 0xd7, 0x30, 0x4, 0x99, 0x19, 0x94, 0xd, 0xf5, 0xe9, 0x8d, 0xc6, 0x2a, 0xbb, 0xa0, 0xd1,
    0x0, 0x0, 0x60, 0x2e, 0xd6, 0x44, 0x73, 0x39, 0xb, 0x16, 0x6c, 0xf2, 0x67, 0xe6, 0xd0, 0xfb,
    0xbb, 0x28, 0x41, 0x55, 0x7e, 0x69, 0x87, 0x5b, 0x37, 0x35, 0x64, 0xe, 0xe5, 0xfe, 0x98, 0x10,
    0x9a, 0x39, 0xd, 0x62, 0x18, 0x72, 0xd9, 0x5f, 0x37, 0x35, 0x12, 0xa, 0x4b, 0xf6, 0xcc, 0x3,
    0xbb, 0x28, 0x45, 0x4d, 0x9a, 0x59, 0xe2, 0x43, 0xb, 0x16, 0xfe, 0xe7, 0xa3, 0xd1, 0xeb, 0xdc,
    0x0, 0x0, 0x15, 0x23, 0x5d, 0x2e, 0x2, 0x18, 0xf5, 0xe9, 0x1e, 0xbc, 0x66, 0xa6, 0xbb, 0xb2,
    0x45, 0xd7, 0x34, 0xfc, 0xb5, 0x9, 0xee, 0xf5, 0xc9, 0xca, 0x27, 0xa0, 0xe8, 0x8d, 0xf3, 0x9d,
    0x66, 0xc6, 0x68, 0xef, 0x1b, 0x1, 0x9c, 0xf1, 0xc9, 0xca, 0x79, 0xa4, 0x82, 0x96, 0xbf, 0xaa,
    0x45, 0xd7, 0x30, 0x4, 0x99, 0x19, 0x94, 0xd, 0xf5, 0xe9, 0x8d, 0xc6, 0x2a, 0xbb, 0xa0, 0xd1,
};
/*To validate result*/
uint8_t fir_fir_output[] =
{
    0x0, 0x0, 0xb4, 0xff, 0xc7, 0xff, 0x2, 0x1, 0xe4, 0x3, 0x57, 0x8, 0xa4, 0xd, 0xbd, 0x12,
    0xb5, 0x16, 0x2f, 0x19, 0x85, 0x1a, 0xa4, 0x1b, 0x91, 0x1d, 0xf0, 0x20, 0xb8, 0x25, 0x3b, 0x2b,
    0x87, 0x30, 0xd8, 0x34, 0x80, 0x38, 0xa0, 0x3b, 0x58, 0x3e, 0xb1, 0x40, 0x91, 0x42, 0xc9, 0x43,
    0x2e, 0x44, 0xb2, 0x43, 0x68, 0x42, 0x7e, 0x40, 0x20, 0x3e, 0x64, 0x3b, 0x3b, 0x38, 0x84, 0x34,
    0x20, 0x30, 0xb, 0x2b, 0x66, 0x25, 0x69, 0x1f, 0x49, 0x19, 0x25, 0x13, 0xf8, 0xc, 0xa7, 0x6,
    0x1b, 0x0, 0x54, 0xf9, 0x78, 0xf2, 0xc0, 0xeb, 0x66, 0xe5, 0x87, 0xdf, 0x1f, 0xda, 0x11, 0xd5,
    0x41, 0xd0, 0xad, 0xcb, 0x73, 0xc7, 0xc8, 0xc3, 0xde, 0xc0, 0xc8, 0xbe, 0x7a, 0xbd, 0xcd, 0xbc,
    0x9a, 0xbc, 0xd3, 0xbc, 0x8b, 0xbd, 0xea, 0xbe, 0x15, 0xc1, 0x16, 0xc4, 0xd0, 0xc7, 0x12, 0xcc,
    0xa8, 0xd0, 0x79, 0xd5, 0x8c, 0xda, 0x0, 0xe0, 0xed, 0xe5, 0x55, 0xec, 0x14, 0xf3, 0xef, 0xf9,
    0xad, 0x0, 0x30, 0x7, 0x7b, 0xd, 0xa8, 0x13, 0xd0, 0x19, 0xf2, 0x1f, 0xec, 0x25, 0x85, 0x2b,
    0x87, 0x30, 0xd8, 0x34, 0x80, 0x38, 0xa0, 0x3b, 0x58, 0x3e, 0xb1, 0x40, 0x91, 0x42, 0xc9, 0x43,
    0x2e, 0x44, 0xb2, 0x43, 0x68, 0x42, 0x7e, 0x40, 0x20, 0x3e, 0x64, 0x3b, 0x3b, 0x38, 0x84, 0x34,
    0x20, 0x30, 0xb, 0x2b, 0x66, 0x25, 0x69, 0x1f, 0x49, 0x19, 0x25, 0x13, 0xf8, 0xc, 0xa7, 0x6,
    0x1b, 0x0, 0x54, 0xf9, 0x78, 0xf2, 0xc0, 0xeb, 0x66, 0xe5, 0x87, 0xdf, 0x1f, 0xda, 0x11, 0xd5,
    0x41, 0xd0, 0xad, 0xcb, 0x73, 0xc7, 0xc8, 0xc3, 0xde, 0xc0, 0xc8, 0xbe, 0x7a, 0xbd, 0xcd, 0xbc,
    0x9a, 0xbc, 0xd3, 0xbc, 0x8b, 0xbd, 0xea, 0xbe, 0x15, 0xc1, 0x16, 0xc4, 0xd0, 0xc7, 0x12, 0xcc,
    0xa8, 0xd0, 0x79, 0xd5, 0x8c, 0xda, 0x0, 0xe0, 0xed, 0xe5, 0x55, 0xec, 0x14, 0xf3, 0xef, 0xf9,
    0xad, 0x0, 0x30, 0x7, 0x7b, 0xd, 0xa8, 0x13, 0xd0, 0x19, 0xf2, 0x1f, 0xec, 0x25, 0x85, 0x2b,
    0x87, 0x30, 0xd8, 0x34, 0x80, 0x38, 0xa0, 0x3b, 0x58, 0x3e, 0xb1, 0x40, 0x91, 0x42, 0xc9, 0x43,
    0x2e, 0x44, 0xb2, 0x43, 0x68, 0x42, 0x7e, 0x40, 0x20, 0x3e, 0x64, 0x3b, 0x3b, 0x38, 0x84, 0x34,
    0x20, 0x30, 0xb, 0x2b, 0x66, 0x25, 0x69, 0x1f, 0x49, 0x19, 0x25, 0x13, 0xf8, 0xc, 0xa7, 0x6,
    0x1b, 0x0, 0x54, 0xf9, 0x78, 0xf2, 0xc0, 0xeb, 0x66, 0xe5, 0x87, 0xdf, 0x1f, 0xda, 0x11, 0xd5,
    0x41, 0xd0, 0xad, 0xcb, 0x73, 0xc7, 0xc8, 0xc3, 0xde, 0xc0, 0xc8, 0xbe, 0x7a, 0xbd, 0xcd, 0xbc,
    0x9a, 0xbc, 0xd3, 0xbc, 0x8b, 0xbd, 0xea, 0xbe, 0x15, 0xc1, 0x16, 0xc4, 0xd0, 0xc7, 0x12, 0xcc,
    0xa8, 0xd0, 0x79, 0xd5, 0x8c, 0xda, 0x0, 0xe0, 0xed, 0xe5, 0x55, 0xec, 0x14, 0xf3, 0xef, 0xf9,
    0xad, 0x0, 0x30, 0x7, 0x7b, 0xd, 0xa8, 0x13, 0xd0, 0x19, 0xf2, 0x1f, 0xec, 0x25, 0x85, 0x2b,
    0x87, 0x30, 0xd8, 0x34, 0x80, 0x38, 0xa0, 0x3b, 0x58, 0x3e, 0xb1, 0x40, 0x91, 0x42, 0xc9, 0x43,
    0x2e, 0x44, 0xb2, 0x43, 0x68, 0x42, 0x7e, 0x40, 0x20, 0x3e, 0x64, 0x3b, 0x3b, 0x38, 0x84, 0x34,
    0x20, 0x30, 0xb, 0x2b, 0x66, 0x25, 0x69, 0x1f, 0x49, 0x19, 0x25, 0x13, 0xf8, 0xc, 0xa7, 0x6,
    0x1b, 0x0, 0x54, 0xf9, 0x78, 0xf2, 0xc0, 0xeb, 0x66, 0xe5, 0x87, 0xdf, 0x1f, 0xda, 0x11, 0xd5,
    0x41, 0xd0, 0xad, 0xcb, 0x73, 0xc7, 0xc8, 0xc3, 0xde, 0xc0, 0xc8, 0xbe, 0x7a, 0xbd, 0xcd, 0xbc,
    0x9a, 0xbc, 0xd3, 0xbc, 0x8b, 0xbd, 0xea, 0xbe, 0x15, 0xc1, 0x16, 0xc4, 0xd0, 0xc7, 0x12, 0xcc,
    0xa8, 0xd0, 0x79, 0xd5, 0x8c, 0xda, 0x0, 0xe0, 0xed, 0xe5, 0x55, 0xec, 0x14, 0xf3, 0xef, 0xf9,
    0xad, 0x0, 0x30, 0x7, 0x7b, 0xd, 0xa8, 0x13, 0xd0, 0x19, 0xf2, 0x1f, 0xec, 0x25, 0x85, 0x2b,
    0x87, 0x30, 0xd8, 0x34, 0x80, 0x38, 0xa0, 0x3b, 0x58, 0x3e, 0xb1, 0x40, 0x91, 0x42, 0xc9, 0x43,
    0x2e, 0x44, 0xb2, 0x43, 0x68, 0x42, 0x7e, 0x40, 0x20, 0x3e, 0x64, 0x3b, 0x3b, 0x38, 0x84, 0x34,
    0x20, 0x30, 0xb, 0x2b, 0x66, 0x25, 0x69, 0x1f, 0x49, 0x19, 0x25, 0x13, 0xf8, 0xc, 0xa7, 0x6,
    0x1b, 0x0, 0x54, 0xf9, 0x78, 0xf2, 0xc0, 0xeb, 0x66, 0xe5, 0x87, 0xdf, 0x1f, 0xda, 0x11, 0xd5,
    0x41, 0xd0, 0xad, 0xcb, 0x73, 0xc7, 0xc8, 0xc3, 0xde, 0xc0, 0xc8, 0xbe, 0x7a, 0xbd, 0xcd, 0xbc,
    0x9a, 0xbc, 0xd3, 0xbc, 0x8b, 0xbd, 0xea, 0xbe, 0x15, 0xc1, 0x16, 0xc4, 0xd0, 0xc7, 0x12, 0xcc,
    0xa8, 0xd0, 0x79, 0xd5, 0x8c, 0xda, 0x0, 0xe0, 0xed, 0xe5, 0x55, 0xec, 0x14, 0xf3, 0xef, 0xf9,
    0xad, 0x0, 0x30, 0x7, 0x7b, 0xd, 0xa8, 0x13, 0xd0, 0x19, 0xf2, 0x1f, 0xec, 0x25, 0x85, 0x2b,
    0x87, 0x30, 0xd8, 0x34, 0x80, 0x38, 0xa0, 0x3b, 0x58, 0x3e, 0xb1, 0x40, 0x91, 0x42, 0xc9, 0x43,
    0x2e, 0x44, 0xb2, 0x43, 0x68, 0x42, 0x7e, 0x40, 0x20, 0x3e, 0x64, 0x3b, 0x3b, 0x38, 0x84, 0x34,
    0x20, 0x30, 0xb, 0x2b, 0x66, 0x25, 0x69, 0x1f, 0x49, 0x19, 0x25, 0x13, 0xf8, 0xc, 0xa7, 0x6,
    0x1b, 0x0, 0x54, 0xf9, 0x78, 0xf2, 0xc0, 0xeb, 0x66, 0xe5, 0x87, 0xdf, 0x1f, 0xda, 0x11, 0xd5,
    0x41, 0xd0, 0xad, 0xcb, 0x73, 0xc7, 0xc8, 0xc3, 0xde, 0xc0, 0xc8, 0xbe, 0x7a, 0xbd, 0xcd, 0xbc,
    0x9a, 0xbc, 0xd3, 0xbc, 0x8b, 0xbd, 0xea, 0xbe, 0x15, 0xc1, 0x16, 0xc4, 0xd0, 0xc7, 0x12, 0xcc,
    0xa8, 0xd0, 0x79, 0xd5, 0x8c, 0xda, 0x0, 0xe0, 0xed, 0xe5, 0x55, 0xec, 0x14, 0xf3, 0xef, 0xf9,
    0xad, 0x0, 0x30, 0x7, 0x7b, 0xd, 0xa8, 0x13, 0xd0, 0x19, 0xf2, 0x1f, 0xec, 0x25, 0x85, 0x2b,
    0x87, 0x30, 0xd8, 0x34, 0x80, 0x38, 0xa0, 0x3b, 0x58, 0x3e, 0xb1, 0x40, 0x91, 0x42, 0xc9, 0x43,
    0x2e, 0x44, 0xb2, 0x43, 0x68, 0x42, 0x7e, 0x40, 0x20, 0x3e, 0x64, 0x3b, 0x3b, 0x38, 0x84, 0x34,
    0x20, 0x30, 0xb, 0x2b, 0x66, 0x25, 0x69, 0x1f, 0x49, 0x19, 0x25, 0x13, 0xf8, 0xc, 0xa7, 0x6,
    0x1b, 0x0, 0x54, 0xf9, 0x78, 0xf2, 0xc0, 0xeb, 0x66, 0xe5, 0x87, 0xdf, 0x1f, 0xda, 0x11, 0xd5,
    0x41, 0xd0, 0xad, 0xcb, 0x73, 0xc7, 0xc8, 0xc3, 0xde, 0xc0, 0xc8, 0xbe, 0x7a, 0xbd, 0xcd, 0xbc,
    0x9a, 0xbc, 0xd3, 0xbc, 0x8b, 0xbd, 0xea, 0xbe, 0x15, 0xc1, 0x16, 0xc4, 0xd0, 0xc7, 0x12, 0xcc,
    0xa8, 0xd0, 0x79, 0xd5, 0x8c, 0xda, 0x0, 0xe0, 0xed, 0xe5, 0x55, 0xec, 0x14, 0xf3, 0xef, 0xf9,
    0xad, 0x0, 0x30, 0x7, 0x7b, 0xd, 0xa8, 0x13, 0xd0, 0x19, 0xf2, 0x1f, 0xec, 0x25, 0x85, 0x2b,
    0x87, 0x30, 0xd8, 0x34, 0x80, 0x38, 0xa0, 0x3b, 0x58, 0x3e, 0xb1, 0x40, 0x91, 0x42, 0xc9, 0x43,
    0x2e, 0x44, 0xb2, 0x43, 0x68, 0x42, 0x7e, 0x40, 0x20, 0x3e, 0x64, 0x3b, 0x3b, 0x38, 0x84, 0x34,
    0x20, 0x30, 0xb, 0x2b, 0x66, 0x25, 0x69, 0x1f, 0x49, 0x19, 0x25, 0x13, 0xf8, 0xc, 0xa7, 0x6,
    0x1b, 0x0, 0x54, 0xf9, 0x78, 0xf2, 0xc0, 0xeb, 0x66, 0xe5, 0x87, 0xdf, 0x1f, 0xda, 0x11, 0xd5,
    0x41, 0xd0, 0xad, 0xcb, 0x73, 0xc7, 0xc8, 0xc3, 0xde, 0xc0, 0xc8, 0xbe, 0x7a, 0xbd, 0xcd, 0xbc,
    0x9a, 0xbc, 0xd3, 0xbc, 0x8b, 0xbd, 0xea, 0xbe, 0x15, 0xc1, 0x16, 0xc4, 0xd0, 0xc7, 0x12, 0xcc,
};
static struct rt_semaphore sem_facc;
#define INT_WAIT_TIME 1000 //Interrupt waiting time
void facc_cbk(struct __FACC_HandleTypeDef *facc)
{
    rt_sem_release(&sem_facc);
}

void FACC1_IRQHandler()                         // Interrupt handler for FACC1
{
    HAL_FACC_IRQHandler(&facc);
}
void facc_init(FACC_HandleTypeDef *facc_handle)
{
    facc_handle->Instance = hwp_facc1;
    HAL_RCC_EnableModule(RCC_MOD_FACC1);//Start FACC1,Make sure FACC1 is enabled
    facc_handle->CpltCallback = facc_cbk; //Set the callback function
    rt_sem_init(&sem_facc, "sem_facc", 0, RT_IPC_FLAG_FIFO); //Initialize the semaphore
    if (HAL_FACC_Init(facc_handle) != HAL_OK)
    {
        rt_kprintf("FACC init failed!\n");
    }

    param = (FACC_ConfigTypeDef *) &fir_fir_param;
    HAL_FACC_Config(facc_handle, param);//
    HAL_FACC_SetCoeff(facc_handle, fir_fir_coef_b, (uint16_t) sizeof(fir_fir_coef_b), NULL, 0, 0); //Input the waveform array and perform algorithmic filtering
    NVIC_EnableIRQ(FACC1_IRQn); //Start the FACC interrupt
    HAL_FACC_Start_IT(facc_handle, fir_fir_input, facc_output, (uint16_t) sizeof(fir_fir_input));
    if (rt_sem_take(&sem_facc, INT_WAIT_TIME) != RT_EOK) //Wait for the interrupt signal
    {
        rt_kprintf("FACC interrupt timeout!\n");
    }

    NVIC_DisableIRQ(FACC1_IRQn);

    if (rt_memcmp(facc_output, fir_fir_output, sizeof(fir_fir_output)) == 0)
    {
        rt_kprintf("FACC_OK \n");
    }
    else
    {
        rt_kprintf("FACC_fail \n");
    }

    rt_kprintf("\n");
    rt_sem_detach(&sem_facc);
    memset(&sem_facc, 0, sizeof(sem_facc));

    HAL_FACC_DeInit(facc_handle);
}

int main(void)
{
    rt_kprintf("Start facc!\n");
    facc_init(&facc);
    while (1)
    {

        rt_thread_mdelay(5000);
    }
    return 0;
}