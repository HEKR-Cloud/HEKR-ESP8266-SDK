#ifndef __GPIO_API_H__
#define __GPIO_API_H__
#include <esp_def.h>
#include "gpio.h"
void gpio_output(unsigned int gpio, unsigned int  value);
char gpio_input(unsigned int gpio);
void gpio_interrupt_register(
	void(*fun)(void *agrv),
	void *argv,
	unsigned char gpio,
	GPIO_INT_TYPE intr_state);
typedef void tvFunvp(void *);
char gpio_input_with_init(unsigned int gpio);
void FUN_ATTRIBUTE gpio_pullup_set(uint8 gpio, uint8  enable);
#endif