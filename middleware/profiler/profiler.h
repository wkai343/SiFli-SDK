/*
 * SPDX-FileCopyrightText: 2019-2022 SiFli Technologies(Nanjing) Co., Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _PROFILER_H_
#define _PROFILER_H_


/**
 * @defgroup profiler Profiler
 * @brief Profiler
 *
 * @{
 */


#include <rtthread.h>
#include "stdbool.h"


#ifndef CONFIG_MAX_NUMBER_OF_CUSTOM_EVENTS
    /** Maximum number of custom events. */
    #define CONFIG_MAX_NUMBER_OF_CUSTOM_EVENTS 0
#endif

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Set of flags for enabling/disabling profiling for given event types.
 */
extern uint32_t profiler_enabled_events;


/** @brief Number of event types registered in the Profiler.
 */
extern uint8_t profiler_num_events;


/** @brief Data types for profiling.
 */
enum profiler_arg
{
    PROFILER_ARG_U8,
    PROFILER_ARG_S8,
    PROFILER_ARG_U16,
    PROFILER_ARG_S16,
    PROFILER_ARG_U32,
    PROFILER_ARG_S32,
    PROFILER_ARG_STRING,
    PROFILER_ARG_TIMESTAMP
};


/** @brief Buffer required for data that is sent with the event.
 */
struct log_event_buf
{
#ifdef USING_PROFILER
    /** Pointer to the end of the payload. */
    uint8_t *payload;
    /** Array where the payload is located before it is sent. */
    uint8_t payload_start[CONFIG_PROFILER_CUSTOM_EVENT_BUF_LEN];
#endif
};


/** @brief Initialize the Profiler.
 *
 * @retval 0 If the operation was successful.
 */
#ifdef USING_PROFILER
int profiler_init(void);
#else
static inline int profiler_init(void)
{
    return 0;
}
#endif


/** @brief Terminate the Profiler.
 */
#ifdef USING_PROFILER
void profiler_term(void);
#else
static inline void profiler_term(void) {}
#endif

/** @brief Retrieve the description of an event type.
 *
 * @param profiler_event_id Event ID.
 *
 * @return Event description.
 */
#ifdef USING_PROFILER
const char *profiler_get_event_descr(size_t profiler_event_id);
#else
static inline const char *profiler_get_event_descr(size_t profiler_event_id)
{
    return NULL;
}
#endif

/** @brief Check if profiling is enabled for a given event type.
 *
 * @param profiler_event_id Event ID.
 *
 * @return Logical value indicating if the event type is currently profiled.
 */
static inline bool is_profiling_enabled(size_t profiler_event_id)
{
#ifdef USING_PROFILER
    RT_ASSERT(profiler_event_id < CONFIG_MAX_NUMBER_OF_CUSTOM_EVENTS);
    return true;//(profiler_enabled_events & BIT(profiler_event_id)) != 0;
#else
    return false;
#endif
}

/** @brief Register an event type.
 *
 * @warning This function is thread-safe, but not safe to use in
 * interrupts.
 *
 * @param name Name of the event type.
 * @param args Names of data values sent with the event.
 * @param arg_types Types of data values sent with the event.
 * @param arg_cnt Number of data values sent with the event.
 *
 * @return ID assigned to the event type.
 */
#ifdef USING_PROFILER
uint16_t profiler_register_event_type(const char *name, const char **args,
                                      const enum profiler_arg *arg_types,
                                      uint8_t arg_cnt);
#else
static inline uint16_t profiler_register_event_type(const char *name,
        const char **args, const enum profiler_arg *arg_types,
        uint8_t arg_cnt)
{
    return 0;
}
#endif


/** @brief Initialize a buffer for the data of an event.
 *
 * @param buf Pointer to the data buffer.
 */
#ifdef USING_PROFILER
void profiler_log_start(struct log_event_buf *buf);
#else
static inline void profiler_log_start(struct log_event_buf *buf) {}
#endif


/** @brief Encode and add data to a buffer.
 *
 * @warning The buffer must be initialized with @ref profiler_log_start
 *          before calling this function.
 *
 * @param data Data to add to the buffer.
 * @param buf Pointer to the data buffer.
 */
#ifdef USING_PROFILER
void profiler_log_encode_u32(struct log_event_buf *buf, uint32_t data);
#else
static inline void profiler_log_encode_u32(struct log_event_buf *buf,
        uint32_t data) {}
#endif


/** @brief Encode and add the event's address in memory to the buffer.
 *
 * This information is used for event identification.
 *
 * @warning The buffer must be initialized with @ref profiler_log_start
 *          before calling this function.
 *
 * @param buf Pointer to the data buffer.
 * @param mem_address Memory address to encode.
 */
#ifdef USING_PROFILER
void profiler_log_add_mem_address(struct log_event_buf *buf,
                                  const void *mem_address);
#else
static inline void profiler_log_add_mem_address(struct log_event_buf *buf,
        const void *mem_address) {}
#endif


/** @brief Encode and add string data to the buffer.
 *
 *
 * @warning The buffer must be initialized with @ref profiler_log_start
 *          before calling this function.
 *
 * @param buf Pointer to the data buffer.
 * @param s string data
 */
#ifdef USING_PROFILER
    void profiler_log_add_string(struct log_event_buf *buf, const char *s);
#else
    #define profiler_log_add_string(buf, s)
#endif



/** @brief Send data from the buffer to the host.
 *
 * This function only sends data that is already stored in the buffer.
 * Use @ref profiler_log_encode_u32 or @ref profiler_log_add_mem_address
 * to add data to the buffer.
 *
 * @param event_type_id Event type ID as assigned to the event type
 *                      when it is registered.
 * @param buf Pointer to the data buffer.
 */
#ifdef USING_PROFILER
void profiler_log_send(struct log_event_buf *buf, uint16_t event_type_id);
#else
static inline void profiler_log_send(struct log_event_buf *buf,
                                     uint16_t event_type_id) {}
#endif

#ifdef USING_PROFILER
    void profiler_log_event_execution(uint16_t event_id, bool start);
#else
    #define profiler_log_event_execution(event_id, start)
#endif



/**
 * @}
 */

#ifdef __cplusplus
}
#endif
#endif /* _PROFILER_H_ */
