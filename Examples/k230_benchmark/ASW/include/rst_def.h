#ifndef __RST_DEF_H__
#define __RST_DEF_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "rst_cfg.h"

#define BOARD_CLOCK_FREQUENCY 24000000

#if RST_USING_RTTHREAD
    #include <rtthread.h>
    #define RST_WAIT_FOREVER    RT_WAITING_FOREVER
    #define RST_PRINT           rt_kprintf
#elif RST_USING_FREERTOS
    #include <FreeRTOS.h>
    #include <task.h>
    #define RST_WAIT_FOREVER    portMAX_DELAY
    #define RST_PRINT(...)      do {                        \
                                    taskENTER_CRITICAL();   \
                                    printf(__VA_ARGS__);    \
                                    taskEXIT_CRITICAL();    \
                                } while(0);
#elif RST_USING_LITEOS_M
    #include <los_task.h>
    #define RST_WAIT_FOREVER    LOS_WAIT_FOREVER
    #define RST_PRINT           printf
#elif RST_USING_TOBUDOS
    #include <tos_k.h>
    #define RST_WAIT_FOREVER    TOS_TIME_FOREVER
    #define RST_PRINT           printf
#elif RST_USING_TENONOS
#include <uk/print.h>
#define RST_WAIT_FOREVER 0xFFFFFFFF
#define RST_PRINT printf
#elif RST_USING_ZEPHYR
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#define RST_WAIT_FOREVER 0xFFFFFFFF
#define RST_PRINT printk
#elif RST_USING_XMEN
//#include <zephyr/kernel.h>
//#include <zephyr/sys/printk.h>
#define RST_WAIT_FOREVER 0xFFFFFFFF
#define RST_PRINT printf
#else


#endif

typedef enum {
    RST_OK = 0,                 /**< There is no error */
    RST_ERROR,                  /**< A generic error happens */
    RST_FULL,                   /**< The resource is full */
    RST_EMPTY,                  /**< The resource is empty */
    RST_NOMEM,                  /**< No memory */
    RST_INVAL,                  /**< Invalid argument */
} rst_status;

/**
 * debug API
 */
#ifndef RST_PRINT_TAG
    #define RST_PRINT_TAG       "RST"
#endif

#if RST_LOGE_EN
    #define RST_LOGE(fmt, ...)           RST_PRINT("\033[31;22m[E/%s](%s:%d) ", RST_PRINT_TAG, __FUNCTION__, __LINE__); \
                                    RST_PRINT(fmt, ##__VA_ARGS__); \
                                    RST_PRINT("\033[0m\r\n")
#else
    #define RST_LOGE(...)
#endif

#if RST_LOGI_EN
#define RST_LOGI(fmt, ...)                                                     \
	RST_PRINT("[I/%s](%s:%d) ", RST_PRINT_TAG, __FUNCTION__, __LINE__);    \
	RST_PRINT(fmt, ##__VA_ARGS__);                                         \
	RST_PRINT("\r\n")
#else
    #define RST_LOGI(...)
#endif

#if RST_LOGD_EN
    #define RST_LOGD(fmt, ...)           RST_PRINT("[D/%s](%s:%d) ", RST_PRINT_TAG, __FUNCTION__, __LINE__); \
                                    RST_PRINT(fmt, ##__VA_ARGS__); \
                                    RST_PRINT("\r\n")
#else
    #define RST_LOGD(...)
#endif


#define RST_PRINT_TIME(message, total_time, iterations, loop_overhead,         \
		       overhead)                                               \
	RST_LOGD("total_time: %ld %s", rst_time_to_ns(total_time),             \
		 rst_time_unit);                                               \
	RST_LOGD("iterations: %d", iterations);                                \
	RST_LOGD("loop_overhead: %ld %s", rst_time_to_ns(loop_overhead),       \
		 rst_time_unit);                                               \
	RST_LOGD("overhead: %ld %s", rst_time_to_ns(overhead), rst_time_unit); \
	RST_PRINT("\033[32;22m%s - %ld %s\033[0m\r\n", (message),              \
		  rst_time_to_ns(                                              \
		      ((((total_time) - (loop_overhead)) / ((iterations)))     \
		       - (overhead))),                                         \
		  rst_time_unit);


#ifdef CONFIG_TIME_USE_64BIT
typedef uint64_t rst_time_t;
#else
typedef uint32_t rst_time_t;
#endif

#ifdef __cplusplus
}
#endif

#endif
