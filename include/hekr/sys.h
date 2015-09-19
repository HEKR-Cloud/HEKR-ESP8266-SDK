#ifndef __SYS_H__
#define __SYS_H__
#include "esp_def.h"


typedef void (*hekr_system_init_done_cb_t)(void);
typedef void (callbcak_handle_t)(void *arg);

void inline product_func_init(void);
char * FUN_ATTRIBUTE get_product_state(void);
void FUN_ATTRIBUTE product_power_control(uint8 power);
FUN_ATTRIBUTE inline 
uint8_t  check_wifi_config_exist(void);

FUN_ATTRIBUTE 
uint8_t register_key_intrrupt_handle
(
	size_t pin,
	GPIO_INT_TYPE intr_state,
	size_t long_press_time,
	callbcak_handle_t *short_press_handle,
	callbcak_handle_t *long_press_handle);
#endif
