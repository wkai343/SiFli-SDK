
#ifndef APP_ALGO_ALGO_H
#define APP_ALGO_ALGO_H


#include <stdbool.h>
#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
    SPORT_TYPE_NORMAL = 0x00,       // 日常
    SPORT_TYPE_RUNNING = 0x01,      // 跑步
    SPORT_TYPE_RIDE_BIKE = 0X02,    // 骑行
    SPORT_TYPE_JUMP_ROPE = 0X03,    // 跳绳
    SPORT_TYPE_SWIMMING = 0X04,     // 游泳
    SPORT_TYPE_BADMINTON = 0X05,    // 羽毛球
    SPORT_TYPE_TABLE_TENNIS = 0X06, // 乒乓球
    SPORT_TYPE_TENNIS = 0X07,       // 网球
    SPORT_TYPE_CLIMBING = 0X08,     // 爬山
    SPORT_TYPE_WALKING = 0X09,      // 徒步
    SPORT_TYPE_BASKETBALL = 0X0A,   // 篮球
    SPORT_TYPE_FOOTBALL = 0X0B,     // 足球
    SPORT_TYPE_BASEBALL = 0X0C,     // 棒球
    SPORT_TYPE_VOLLEYBALL = 0X0D,   // 排球
    SPORT_TYPE_CRICKET = 0X0E,      // 板球
    SPORT_TYPE_RUGBY = 0X0F,        // 橄榄球
    SPORT_TYPE_HOCKEY = 0X10,       // 曲棍球
    SPORT_TYPE_DANCE = 0X11,        // 跳舞
    SPORT_TYPE_SPINNING = 0X12,     // 动感单车
    SPORT_TYPE_YOGA = 0X13,         // 瑜伽
    SPORT_TYPE_SIT_UP = 0X14,       // 仰卧起坐
    SPORT_TYPE_TREADMILL = 0X15,    // 跑步机
    SPORT_TYPE_GYMNASTICS = 0X16,   // 体操
    SPORT_TYPE_BOATING = 0X17,      // 划船
    SPORT_TYPE_JUMPING_JACK = 0X18, // 开合跳
    SPORT_TYPE_FREE_TRAINING = 0X19,// 自由训练
} AlgoSportMode_t;
//未出现在上表中的运动形式均先以跑步输入


typedef struct
{
    int32_t x;
    int32_t y;
    int32_t z;
} AlgoAxesData_t;

typedef struct
{
    int32_t         hrData;
    int32_t         reliability;
} AlgoOutputData_t;

typedef struct
{
    AlgoAxesData_t  axes;
    int32_t         ppgSample;
    int32_t         envSample;
} AlgoInputData_t;

void Algo_Init(void);
void Algo_Input(AlgoInputData_t *pInputData, int32_t gaptime, AlgoSportMode_t sportMode, int16_t surfaceRecogMode, int16_t opticalAidMode);
void Algo_Output(AlgoOutputData_t *pOutputData);
void Algo_Version(char *pVersionOutput);
void send_hr_data2_hcpu(uint16_t start, uint16_t end);
uint8_t vc32s_get_hr_value(void);
uint8_t vc32s_get_spo2_value(void);
uint8_t vc32s_get_wear_status(void);

#ifdef __cplusplus
}
#endif
#endif /* APP_ALGO_ALGO_H_ */



