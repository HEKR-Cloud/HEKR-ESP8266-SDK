/**********************************************************************************************//**
 * @file	user_main.c
 *						  by www.hekr.me
 * HEKR ESP8266 SMART PLUG DEMO 
 * 氦氪智能插座示例代码
 *
 * 说明：
 *		通过app控制模块的GPIO14引脚的高低电平
 *		按键引脚为GPIO12：长按为 恢复出厂配置 短按为：翻转GPIO14电平
 *
 **************************************************************************************************/

#include <c_types.h>
#include <esp_def.h>
#include <conn_cloud.h>
#include <module_wifi.h>
#include <module_gpio.h>
#include <sys.h>
#include <log.h>
#include <uart.h>
#include <iotss.h>
#include <device_info.h>
#include "demo_plug.h"

FUN_ATTRIBUTE
char * get_plug_state(void)
{
#define MSG "(state \"power\" 256 \"timer\" 4294967296 \"timertodo\" 256\")"
	uint8 state = GPIO_INPUT_GET(GPIO_ID_PIN(PLUG_POWR_PIN));
	char *msg = (char *)os_zalloc(sizeof(MSG));
	if (msg == NULL)
	{
		return NULL;
	}
	sprintf(msg, "(state \"power\" %u \"timer\" 0 \"timertodo\" 0)", state);	

	return msg;
}

FUN_ATTRIBUTE
void  product_power_control(uint8 power)
{
	gpio_output(PLUG_POWR_PIN, power);
	char *msg = get_plug_state();
	if (msg == NULL)
	{
		os_printf("get_product_state error");
		return;
	}
	send_data_to_cloud(msg, strlen(msg));
	free(msg);

	return;
}

FUN_ATTRIBUTE
static void bind_controlpower(iotss_native_proc_args_t *args)
{
	iotss_native_proc_arg_t *arg_t = iotss_native_proc_args_get_arg(args);
	product_power_control(arg_t->u.value_int);
	if (arg_t != NULL)
		iotss_native_proc_arg_destroy(arg_t);
}

FUN_ATTRIBUTE 
void plug_power_change(void)
{
	uint8 pin_state = GPIO_INPUT_GET(GPIO_ID_PIN(PLUG_POWR_PIN));
	product_power_control(!pin_state);
}


static iotss_static_bindings_item_t tbl_static_bindings[] =
{
	IOTSS_STATIC_BINDINGS_ITEM("controlpower", bind_controlpower, 1, 1, "i"),
	IOTSS_STATIC_BINDINGS_ITEM_FINAL
};

FUNC_MODIFIER
int  iotss_bind_demo_plug(iotss_vm_t *vm)
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


FUN_ATTRIBUTE 
void device_id_set(void)
{
	device_id_t id = { PLUG_MID ,PLUG_PID ,PLUG_CID };
	set_device_id(id);
}


FUN_ATTRIBUTE 
void system_init_done(void)
{
	/*设置设备id*/
	device_id_set();
	/*虚拟机扩展接口*/
	iotss_bind_demo_plug(g_vm);
	/*判断wifi设置是否存在*/
	if (check_wifi_config_exist() == 0)
		start_hekr_config(NULL, 5 * 60 * 1000);
}

void inline plug_hardware_init(void)
{
	/*注册状态指示灯*/
	device_status_led_task_install(BIT4, 0);

	/*注册按键中断*/
	register_key_intrrupt_handle
		(
			PLUG_KEY_PIN,
			GPIO_PIN_INTR_NEGEDGE,
			3000,
			(callbcak_t *)&plug_power_change,
			(callbcak_t *)&wifi_config_reset
		);
}

/**
 * 用户程序入口  
 */

FUN_ATTRIBUTE 
void hekr_main(void)
{
	uart_init(0, BIT_RATE_9600);
	system_log_set(PORT_UART1);
	os_printf("sdk ver=%s\n", get_hekr_sdk_version());
	os_printf("Demo plug\n");

	/*注册系统初始化完成之后的回调*/
	register_hekr_system_init_done_callback(system_init_done);
	plug_hardware_init();
}
