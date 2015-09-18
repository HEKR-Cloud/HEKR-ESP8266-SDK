#ifndef __DEMO_PLUG_H__
#define __DEMO_PLUG_H__

#include <device_info.h>

/*DEMO PLUG*/
#define PRODUCT_FIRMWARE_VERSION	"1"
#define MNAME	"DEMO_PLUG"
#define PLUG_MID		20
#define PLUG_PID		11
#define PLUG_CID		50

/*product pin define*/
#define PLUG_POWR_PIN					14

extern product_info_t g_product_info;

char * FUN_ATTRIBUTE get_product_state(void);
void FUN_ATTRIBUTE product_power_control(uint8 power);

#endif