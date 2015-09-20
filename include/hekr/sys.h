#ifndef __SYS_H__
#define __SYS_H__
#include "esp_def.h"


typedef void (*hekr_system_init_done_cb_t)(void);
typedef void (callbcak_handle_t)(void *arg);

FUN_ATTRIBUTE  
uint8_t  check_wifi_config_exist(void);

FUN_ATTRIBUTE 
uint8_t register_key_intrrupt_handle
(
	size_t pin,
	GPIO_INT_TYPE intr_state,
	size_t long_press_time,
	callbcak_handle_t *short_press_handle,
	callbcak_handle_t *long_press_handle);

FUN_ATTRIBUTE
void start_update(char *bin_url);
#endif
