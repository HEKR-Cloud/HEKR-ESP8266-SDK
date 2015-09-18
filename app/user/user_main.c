/**********************************************************************************************//**
 * @file	user_main.c
 *						  by www.hekr.me
 * HEKR ESP8266 SMART PLUG DEMO 
 * 氦氪智能插座示例代码
 *
 * 说明：
 *		通过app控制模块的GPIO14引脚的高低电平
 *
 **************************************************************************************************/

#include <esp_def.h>
#include <conn_cloud.h>
#include <module_wifi.h>
#include <module_gpio.h>
#include <log.h>
#include <uart.h>
#include <iotss.h>
#include "demo_plug.h"


char * FUN_ATTRIBUTE get_plug_state(void)
{
#define MSG "(state \"power\" 256)"
	uint8 state = GPIO_INPUT_GET(GPIO_ID_PIN(PLUG_POWR_PIN));
	char *msg = (char *)os_zalloc(sizeof(MSG));
	if (msg == NULL)
		return NULL;
	sprintf(msg, "(state \"power\" %u)", state);
	return msg;

}

void FUN_ATTRIBUTE product_power_control(uint8 power)
{

	gpio_output(PLUG_POWR_PIN, power);
	char *msg = get_plug_state();
	if (msg == NULL)
	{
		os_printf("get_product_state error");
		goto fail;
	}
	send_data_to_cloud(msg, strlen(msg));
	free(msg);
done:
	return;
fail:
	return;
}


static void FUNC_MODIFIER bind_controlpower(iotss_native_proc_args_t *args)
{
	iotss_native_proc_arg_t *arg_t = iotss_native_proc_args_get_arg(args);
	product_power_control(arg_t->u.value_int);
	if (arg_t != NULL)
		iotss_native_proc_arg_destroy(arg_t);
}


static iotss_static_bindings_item_t tbl_static_bindings[] =
{
	IOTSS_STATIC_BINDINGS_ITEM("controlpower", bind_controlpower, 1, 1, "i"),
	IOTSS_STATIC_BINDINGS_ITEM_FINAL

};

int FUNC_MODIFIER iotss_bind_demo_plug(iotss_vm_t *vm)
{
	int ret = 0;

	/* Bind static bindings */
	if (iotss_vm_bind_static_bindings_from_items(vm, \
		"static-bindings-std", \
		tbl_static_bindings) != 0)
	{
		ret = -1; goto fail;
	}

fail:
	return ret;
}


FUN_ATTRIBUTE void device_id_set(void)
{
	g_product_info.id.mid = PLUG_MID;
	g_product_info.id.pid = PLUG_PID;
	g_product_info.id.cid = PLUG_CID;

}


FUN_ATTRIBUTE void system_init_done(void)
{
	device_id_set();
	iotss_bind_demo_plug(g_vm);
	if (check_wifi_config_exist() == 0)
		hekr_config_start(NULL, 5 * 60 * 1000);
}

FUN_ATTRIBUTE void hekr_main(void)
{
	uart_init(0, BIT_RATE_9600);
	system_log_set(PORT_UART1);
	os_printf("\n\nsystem run !! \n\n");
	os_printf("sdk ver=%s\n", get_hekr_sdk_version());
	register_hekr_system_init_done_callback(system_init_done);
	os_printf("Demo plug\n");

}
