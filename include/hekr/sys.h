#ifndef __SYS_H__
#define __SYS_H__
#include "esp_def.h"
#include <gpio.h>

/*set user version*/
#define SET_USER_VERSION(num1,num2,num3,num4)	set_user_verison((num1<<24)|(num2<<16)|(num3<<8)|num4)
#define PRINT_USER_VERSION(printf_func)		do { \
													uint32_t verison = get_user_firmware_version(); \
													printf_func("%u.%u.%u.%u",((uint8_t *)&verison)[3],\
														((uint8_t *)&verison)[2], \
														((uint8_t *)&verison)[1], \
														((uint8_t *)&verison)[0]);\
												}while(0)
#define USER_VERSION_TO_STR(NAME)	char NAME[13]; \
									do{uint32_t verison = get_user_firmware_version(); \
									sprintf(NAME,"%u.%u.%u.%u",((uint8_t *)&verison)[3],\
										((uint8_t *)&verison)[2], \
										((uint8_t *)&verison)[1], \
										((uint8_t *)&verison)[0]);}while(0)

typedef void (*hekr_system_init_done_cb_t)(void);
typedef void (callbcak_t)(void *arg);

enum module_flag
{
	MODULE_PLUG = BIT(0),
	MODULE_UART_PASS = BIT(1),
	MODULE_ALL = MODULE_PLUG | MODULE_UART_PASS
};

uint8_t  check_wifi_config_exist(void);

uint32_t get_user_firmware_version(void);
void set_user_verison(uint32_t verison);

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
