/**********************************************************************************************//**
 * @file	user_main.c
 *
 * HEKR ESP8266 TEST CASE
 * 
 **************************************************************************************************/

#include <esp_def.h>
#include <conn_cloud.h>
#include <module_wifi.h>
#include <log.h>
#include <uart.h>


void test_hekr_config(config_event_t event)
{
	os_printf("event =%d\n",event);
}

void debug_print_hex(uint8_t *data, size_t size)
{
	size_t i;
	for ( i = 0; i<size; i++)
	{
		os_printf("%2X", data[i]);
	}
	os_printf("\n");
}

void cloud_data_test(void *arg, size_t size)
{
	debug_print_hex((uint8_t *)arg, size);
	if (((uint8_t *)arg)[0] == 0x01)
	{
		hekr_config_stop();
	}
	uint8_t test[] = { 0x56,0x48,0x34,0x98 };
	switch (((uint8_t *)arg)[0])
	{
	case 0x01:
		send_message_to_remote(NULL, test, sizeof(test));
		break;
	case 0x02:
		hekr_config_stop();
		break;
	case 0x03:
		hekr_config_start(test_hekr_config, 50 * 1000);
		break;
	default:
		break;
	}
	
}

void uart_test(uint8_t data)
{
	os_printf("%02X", data);
	if (data == 0x01)
	{
		hekr_config_stop();
	}
}

FUN_ATTRIBUTE void system_init_done(void)
{
	hekr_config_start(test_hekr_config, 5*60 * 1000);
}

void hekr_main(void)
{
	uart_init(BIT_RATE_9600, BIT_RATE_9600);
	system_log_set(PORT_UART1);
	os_printf("\n\nsystem run !! \n\n");
	os_printf("sdk ver=%s\n", get_hekr_sdk_version());
	register_uart_data_received_callback(uart_test);
	register_receive_server_data_callback(cloud_data_test);
	register_hekr_system_init_done_callback(system_init_done);
}
