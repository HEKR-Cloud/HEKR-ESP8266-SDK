#include <hekr/esp_def.h>
#include <osapi.h>
#include <hekr/uart.h>

void hekr_main(void)
{
	uart_init(9600, 9600);
	os_printf("\n\n system run !! \n\n");
	os_printf("ver=%s\n",get_hekr_sdk_version());
}
