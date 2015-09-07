#ifndef __SYS_H__
#define __SYS_H__
#include "esp_def.h"


typedef void (*hekr_system_init_done_cb_t)(void);

void inline product_func_init(void);
char * FUN_ATTRIBUTE get_product_state(void);
void FUN_ATTRIBUTE product_power_control(uint8 power);
#endif
