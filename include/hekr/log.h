#ifndef __LOG_H__
#define __LOG_H__

#include <esp_def.h>

#ifdef __cplusplus
extern "C" {
#endif

/*DEFINE LOG FOR VS*/
#if defined(__USEVS__)
#define debug_print(format, ...)
	/*DEFINE LOG FOR ESP*/
#elif defined(__ESP8266__)

#define debug_print(format, args...) \
do{ \
		os_printf("[log]%s:%d: ", __FILE__, __LINE__); \
		os_printf(format,##args); \
		os_printf("\n"); \
} while (0)
#endif
/*DEFIEN FOR ESP END*/

typedef enum
{
	PORT_UART0 = 0, //通过uart0输出
	PORT_UART1,		//通过uart1输出
	PORT_NULL		//不输出
}log_port_t;

FUN_ATTRIBUTE  void system_log_set(log_port_t port);

#ifdef __cplusplus
}
#endif

#endif