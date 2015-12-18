/**********************************************************************************************//**
 * @file	user_main.c
 *
 * HEKR 串口-云端 数据透传 示例代码
 *
 *								      www.hekr.me
 *
 **************************************************************************************************/

#include <esp_def.h>
#include <conn_cloud.h>
#include <module_wifi.h>
#include <log.h>
#include <uart.h>
#include <sys.h>
#include <iotss.h>
#include <device_info.h>

#define TIMER_REGISTER(P_TIMER,FUNC,PARAM,TIME,CYCLE)	do \
														{ \
															os_timer_disarm(P_TIMER); \
															os_timer_setfn(P_TIMER, (os_timer_func_t *)FUNC, PARAM); \
														}while(0)
#define TIMER_START(P_TIMER,TIME,CYCLE)	do \
														{ \
															os_timer_arm(P_TIMER, TIME, CYCLE); \
														}while(0)

#define UART_DATA_BUF_LEN			256	//byte
#define UART_DATA_PACKAGE_TIME_OUT	100	//ms

typedef struct {
	uint8_t buf[UART_DATA_BUF_LEN];
	size_t size;
}uart_data_t;

uart_data_t *uart_data = NULL;

void  uart_data_handler(iotss_native_proc_args_t *args);

FUN_ATTRIBUTE
int  iotss_bind_uartdata(iotss_vm_t *vm)
{
	static iotss_static_bindings_item_t tbl_static_bindings[] =
	{
		IOTSS_STATIC_BINDINGS_ITEM("uartdata", &uart_data_handler, 1, 1, "s"),
		IOTSS_STATIC_BINDINGS_ITEM_FINAL

	};

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
void hekr_config_callback(config_event_t event)
{
	os_printf("event =%d\n", event);
}



/*
* @功能：收到云端数据，并从串口0发送出去
*/
FUN_ATTRIBUTE  inline
static void cloud_data_callbcak(void *data, size_t size)
{
	uart0_tx_buffer(data, size);
}

FUN_ATTRIBUTE
static void send_uartdata_to_cloud(void *arg)
{
	ETS_UART_INTR_DISABLE();
	uart_data_t **data = arg;
	send_uart_data_to_remote((*data)->buf, (*data)->size);
	(*data)->size = 0;
	ETS_UART_INTR_ENABLE();
}


/*
 * @功能：将串口0收到的数据进行打包发送给云端
 */

void uart_data_callbcak(uint8_t data)
{
	static ETSTimer timer;
	if (uart_data == NULL)
	{
		uart_data = malloc(sizeof(uart_data_t));
		if (uart_data == NULL) { return; }
		uart_data->size = 0;
		TIMER_REGISTER(&timer, send_uartdata_to_cloud, &uart_data, UART_DATA_PACKAGE_TIME_OUT, 0);
	}

	uart_data->buf[uart_data->size++] = data;
	if (uart_data->size >= UART_DATA_BUF_LEN)
	{
		os_timer_disarm(&timer);
		send_uartdata_to_cloud(uart_data);
	}
	TIMER_START(&timer, UART_DATA_PACKAGE_TIME_OUT, 0);
}

FUN_ATTRIBUTE
static void device_id_set(void)
{
	device_id_t id = { 0,0,0 };
	set_device_id(id);
}


FUN_ATTRIBUTE
void system_init_done(void)
{
	debug_print("system_init_done");
	/*设置设备id*/
	device_id_set();
	/*判断wifi设置是否存在*/
	if (check_wifi_config_exist() == 0)
		start_hekr_config(&hekr_config_event_handle, 5 * 60 * 1000);
	/*uartdata bind*/
	iotss_bind_uartdata(g_vm);

	/*version*/
	USER_VERSION_TO_STR(version);
	os_printf("user version=%s", version);
}

FUN_ATTRIBUTE
void  hardware_init(void)
{
	/*注册状态指示灯*/
	device_status_led_task_install(BIT4 | BIT14, 0);

	/*注册按键中断*/
	register_key_intrrupt_handle
		(
			13,
			GPIO_PIN_INTR_NEGEDGE,
			3000,
			NULL,
			(callbcak_t *)&wifi_config_reset
			);
}


/*
 *  程序入口
 */
FUN_ATTRIBUTE
void hekr_main(void)
{
	SET_USER_VERSION(3, 0, 65, 0);
	uart_init(BIT_RATE_9600, BIT_RATE_9600);
	/*设置日志从UART1输出 ---硬件上请连接GPIO2 */
	system_log_set(PORT_UART1);
	os_printf("\n\nsystem run !! \n\n");
	os_printf("sdk ver=%s\n", get_hekr_sdk_version());
	hardware_init();
	register_uart_data_received_callback(uart_data_callbcak);
	register_receive_server_data_callback(cloud_data_callbcak);
	register_hekr_system_init_done_callback(system_init_done);
}
