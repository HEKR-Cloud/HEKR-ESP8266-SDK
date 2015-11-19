#ifndef __ESP_DEF_H__
#define __ESP_DEF_H__
#include "esp_miss_header.h"
#include <ets_sys.h>
#include <os_type.h>
#include <mem.h>
#include <osapi.h>
#include <user_interface.h>
#include <user_esp_platform.h>
#include <smartconfig.h>

#ifdef __cplusplus
extern "C" {
#endif

/*PLATFORM DEFINE */
#if defined(__ESP8266__)
#define FUN_ATTRIBUTE __attribute__((section(".irom0.text")))
#define VAR_ATTRIBUTE __attribute__((section(".irom.text")))
#else
#define FUN_ATTRIBUTE 
#define VAR_ATTRIBUTE 	
#endif
/*END*/




#define malloc		os_malloc
#define zalloc		os_zalloc
#define memcpy		os_memcpy
#define memset		os_memset
#define memcmp		os_memcmp
#define strcmp		os_strcmp
#define free		os_free
#define strncmp		os_strncmp
#define sprintf		os_sprintf
#define printf		os_printf


#ifdef __cplusplus
}
#endif

#endif