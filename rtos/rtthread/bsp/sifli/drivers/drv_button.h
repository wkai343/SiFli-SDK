/*
 * SPDX-FileCopyrightText: 2019-2022 SiFli Technologies(Nanjing) Co., Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef DRV_BUTTON_H
#define DRV_BUTTON_H

#define BTN_NAME_MAX  8

/*
 The button debounce time is 40ms, the recommended calling period is 20ms.
 It is considered valid only if the 40ms state is continuously detected, including bounce and press.
*/

//#define CONTINUOS_TRIGGER               //Whether to support continuous triggering, do not detect single-click and long-press if you send even

/* Whether to support click and double-click while there is a trigger,
 if you choose to enable the macro definition, single-click double-clickback,
 but click will delay the response.Because it must be judged whether a
 double click is triggered after clicking, the delay time is the double-click
 interval BUTTON_DOUBLE_TIME.If you do not enable this macro definition,
 it is recommended that there is only one click/double click in the project.
 Otherwise, a click will be triggered when the response is double-clicked.
 Because the double click must be generated after one press and release.
*/

//#define SINGLE_AND_DOUBLE_TRIGGER

/* Whether long-press release is supported or not. If this macro definition is turned on, a long press is triggered after a long press release.
    Otherwise, long press is triggered for a long time, the trigger period is determined by BUTTON_LONG_CYCLE*/
//#define LONG_FREE_TRIGGER

#ifndef  BUTTON_DEBOUNCE_TIME
    #define BUTTON_DEBOUNCE_TIME   2   /// Debounce time  (n-1)*call cycle
#endif

#ifndef  BUTTON_CONTINUOS_CYCLE
    #define BUTTON_CONTINUOS_CYCLE  1  /// Double-click the trigger cycle time  (n-1)*call cycle
#endif

#ifndef  BUTTON_LONG_CYCLE
    #define BUTTON_LONG_CYCLE       1  /// Long press trigger cycle time   (n-1)*call cycle
#endif

#ifndef  BUTTON_DOUBLE_TIME
    #define BUTTON_DOUBLE_TIME      15 /// Double click interval  (n-1)*call cycle  Recommended at 200-600ms
#endif

#ifndef BUTTON_LONG_TIME
    #define BUTTON_LONG_TIME       50  /// For n seconds ((n-1)*call cycle)ms, think long press event
#endif

#define TRIGGER_CB(event)   \
        if(btn->cbk_func) \
          btn->cbk_func(btn,event)

struct button;

typedef enum
{
    BUTTON_DOWM = 0,
    BUTTON_UP,
    BUTTON_DOUBLE,
    BUTTON_LONG,
    BUTTON_LONG_FREE,
    BUTTON_CONTINUOS,
    BUTTON_CONTINUOS_FREE,
    NONE_TRIGGER
} button_event;
typedef void (*button_cbk)(struct button *, button_event); //The button triggers the callback function and needs to be implemented by the user.

/**
  Each button corresponds to a global structure variable.
  Its member variables are necessary to implement filtering and multiple button states.
*/
typedef struct button
{
    rt_slist_t *next;
    char name[BTN_NAME_MAX];                      /**< Button name */
    rt_uint8_t btn_state              :   4;      /**< The current state of the button (pressed or bounced) */
    rt_uint8_t btn_last_state         :   4;      /**< The last button state used to determine the double click */
    rt_uint8_t btn_trigger_level      :   2;      /**< Button trigger level */
    rt_uint8_t btn_last_level         :   2;      /**< Button current level */

    rt_uint8_t btn_trigger_evt;                   /**< Button trigger event, click, double click, long press, etc. */
    rt_uint8_t btn_cycle;                         /**< Continuous button cycle */
    rt_uint8_t btn_count;                         /**< Timing */
    rt_uint8_t btn_debounce;                      /**< Debounce time */
    rt_uint8_t btn_long_time;                     /**< Button press duration */

    rt_uint8_t (*read_btn_level)(void);           /**< Read the button level function, you need to implement */
    button_cbk cbk_func;                          /**< Callback functions*/
} button_t;

/* Function declaration for external calls */
void button_create(const char *name,
                   button_t *btn,
                   rt_uint8_t(*read_btn_level)(void),
                   rt_uint8_t btn_trigger_level);

void button_regcbk(button_t *btn, button_cbk callback);
void button_process(void);
void button_delete(button_t *btn);

#endif

