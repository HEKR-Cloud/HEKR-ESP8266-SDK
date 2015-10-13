#ifndef __DEMO_PLUG_H__
#define __DEMO_PLUG_H__


/*DEMO PLUG*/
#define PRODUCT_FIRMWARE_VERSION	"1"
#define MNAME	"DEMO_PLUG"
#define PLUG_MID		16
#define PLUG_PID		1
#define PLUG_CID		50

/*product pin define*/
#define PLUG_POWR_PIN	14
#define PLUG_KEY_PIN	12  


char * FUN_ATTRIBUTE get_product_state(void);
void FUN_ATTRIBUTE product_power_control(uint8 power);

#endif