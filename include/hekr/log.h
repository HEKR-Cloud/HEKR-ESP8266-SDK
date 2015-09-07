#ifndef __LOG_H__
#define __LOG_H__

#include <esp_def.h>

#ifdef __cplusplus
extern "C" {
#endif

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