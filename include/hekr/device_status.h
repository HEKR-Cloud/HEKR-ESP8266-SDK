#ifndef __DEVICE_STATUS_H__
#define __DEVICE_STATUS_H__

#include <esp_def.h>
#include <module_gpio.h>
#include "../product/product_config.h"

/*DEV STATE DISPLAY DEFINE */
#ifndef NETWORK_STATE_LED_ON_FUNC	
#define NETWORK_STATE_LED_ON_FUNC	gpio_output(4,1);
#define NETWORK_STATE_LED_OFF_FUNC	gpio_output(4,0);
#endif
/*END DEFINE */



typedef enum
{
	DEVICE_WLAN_CONNECTED = 0,
	DEVICE_WLAN_IDLE,
	DEVICE_WLAN_CONNECTING,
	DEVICE_WLAN_CONNECT_TIMEOUT,
	DEVICE_WLAN_PASSWOR_WRONG,
	DEVICE_WLAN_AP_CANNOT_FIND,
	GOT_SERVER_IP,
	LOGGED_IN_SERVER,
	UART0_INTR,
	COMMAND_CONFIRM,
	CONNECT_CLOUD_DISABLE,
	HEKR_CONFIG_RUNNING,
	SOFTAP_CONFIG_RUNNING,
	ACCESSKEY_SET_ENABLE,
	ACCESSKEY_SET_FINISH,
	LOG_PRINT_ENABLE,
	CLOUD_SEND_QUEUE_FINISH,
	VM_EVAL_QUEUE_FINISH,
	VM_EVAL_PORT_LAN,
	VM_EVAL_PORT_UART0,
	VM_EVAL_PORT_CLOUD,
	VM_EVAL_PORT_INTERNAL
}device_status_type_t;

typedef void device_status_change_callback_t(device_status_type_t item,uint8 current_state);

extern device_status_change_callback_t *g_device_status_change_callback;

void device_status_store(device_status_type_t item, uint8 current_state);
uint8 device_status_get(device_status_type_t item);
void inline cloud_connect_state_task_install(void);

#endif