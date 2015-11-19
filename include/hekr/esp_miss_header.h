#ifndef __ESP_MISS_HEADER_H__
#include "user_config.h"
#include <c_types.h>
#include <os_type.h>

/*stdlib api declaration*/
int atoi(const char *nptr);
void os_printf_plus(const char *, ...);
void *ets_memcpy(void *dest, const void *src, size_t n);
void *ets_memset(void *s, int ch, size_t n);
int ets_memcmp(const void *buf1, const void *buf2, unsigned int count);
int ets_strcmp(const char *s1, const char *s2);
int ets_strncmp(const char * str1, const char * str2, size_t num);
int ets_sprintf(char *buffer, const char *format,...);
const char * ets_strstr(const char * str1, const char * str2);
unsigned int ets_strlen(const char *s);
void srand(unsigned int seed);
int rand(void);

/*interrupt api declaration*/
void ets_isr_mask(uint32_t);
void ets_isr_unmask(uint32_t);
void ets_isr_attach(uint32_t, void(*fun)(void *), void *);

/*esp mem api*/
void *pvPortMalloc(unsigned int, const char *, size_t);
void *pvPortZalloc(unsigned int, const char *, size_t);
void *pvPortRealloc(void *, unsigned int, const char *, size_t);
void vPortFree(void *, const char *, size_t);

/*tiemr api declaration*/
void ets_timer_arm_new(ETSTimer *ptimer, uint32_t milliseconds, bool repeat_flag, uint32_t);
void ets_timer_disarm(ETSTimer *ptimer);
void ets_timer_setfn(ETSTimer *ptimer, ETSTimerFunc *pfunction, void *parg);
void ets_delay_us(uint32_t);
#endif