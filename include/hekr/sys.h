#ifndef __SYS_H__
#define __SYS_H__
#include "esp_def.h"
#include <gpio.h>

typedef void (*hekr_system_init_done_cb_t)(void);
typedef void (callbcak_t)(void *arg);

uint8_t  check_wifi_config_exist(void);

uint8_t register_key_intrrupt_handle
(
	size_t pin,
	GPIO_INT_TYPE intr_state,
	size_t long_press_time,
	callbcak_t *short_press_handle,
	callbcak_t *long_press_handle);

bool start_update(char *URL, char *MD5, char firmware_type);
void register_hekr_system_init_done_callback(hekr_system_init_done_cb_t handle);
#endif
