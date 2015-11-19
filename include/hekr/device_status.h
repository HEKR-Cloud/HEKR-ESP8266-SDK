#ifndef __DEVICE_STATUS_H__
#define __DEVICE_STATUS_H__

#include <esp_def.h>

typedef enum
{
	DEVICE_WLAN_CONNECTED = 0,		//设备连接上wifi
	DEVICE_WLAN_CONNECTING =2,		//正在连接wifi
	GOT_SERVER_IP =6,				//通过DNS服务成功获取的服务器IP
	LOGGED_IN_SERVER =7,			//成功登入服务器
	HEKR_CONFIG_RUNNING =11,		//一件配置模式正在运行
	SOFTAP_CONFIG_RUNNING =13,		//热点配置模式正在运行
	LOG_PRINT_ENABLE =16			//LOG输出开启
}device_status_type_t;

typedef void device_status_change_callback_t(device_status_type_t item,uint8 current_state);

void device_status_store(device_status_type_t item, uint8 current_state);

uint8 device_status_get(device_status_type_t item);

FUN_ATTRIBUTE inline
void device_status_led_task_install(uint32_t pin, uint32_t reverse);

void register_device_status_change_callback(device_status_change_callback_t *cb);

#endif