#ifndef __ESP_DEF_H__
#define __ESP_DEF_H__
#include <c_types.h>
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
#if defined(__USEVS__)
#define FUN_ATTRIBUTE
#define VAR_ATTRIBUTE
#define inline

#elif defined(__ESP8266__)
#define FUN_ATTRIBUTE __attribute__((section(".irom0.text")))
#define VAR_ATTRIBUTE __attribute__((section(".irom.text")))
#endif
/*END*/



#define LISP_RET_STR_SIZE 256
#define CLEAN_LISP_RET_STR memset(g_lisp_ret, 0, strlen(g_lisp_ret))

#define		FLASH_SIZE		2048
#if (FLASH_SIZE==1024)
#define DEVNAME "ESP_1M_"
#elif (FLASH_SIZE==2048)
#define DEVNAME "ESP_2M_"
#endif
#define		TIDSIZE		sizeof(""DEVNAME"XXXXXXXXXXXX")


#define malloc		os_malloc 
#define memcpy		os_memcpy
#define memset		os_memset
#define memcmp		os_memcmp
#define strcmp		os_strcmp
#define free		os_free
#define strncmp		os_strncmp
#define sprintf		os_sprintf
#define printf		os_printf

#define int8_t	int8	
#define uint8_t	 uint8
#define uint16_t uint16
#define uint32_t uint32


/*string struct define*/

typedef enum
{
	DYNAMIC_PARAM_TYPE_NULL=0,
	DYNAMIC_PARAM_TYPE_RAW,
	DYNAMIC_PARAM_TYPE_STRING,
	DYNAMIC_PARAM_TYPE_INT,
}dynamic_param_type_t;

typedef struct dynamic_param_s {
	dynamic_param_type_t type;
	union
	{
		int32_t value_int;
		struct
		{
			uint8_t *src;
			size_t len;
		}value_str,value_raw;
	}u;
}dynamic_param_t;

/*string struct end define*/

typedef struct {
	struct MyStruct
	{
		int32_t mid;
		int32_t cid;
		int32_t pid;
	}id;
}product_info_t;

typedef void (call_bcak_func_t)(void *arg);
 
char * FUN_ATTRIBUTE get_tid(void);
FUN_ATTRIBUTE dynamic_param_t *device_detail_get(void);
dynamic_param_t * FUN_ATTRIBUTE device_info_all_get(void);
inline void dynamic_param_destory(dynamic_param_t *p);
inline dynamic_param_t *dynamic_param_new(dynamic_param_type_t type, const void *src, size_t size);
inline dynamic_param_t *device_param_get(dynamic_param_type_t type, const char *path);
FUN_ATTRIBUTE bool product_info_load(product_info_t *info);
FUN_ATTRIBUTE inline char *get_hekr_sdk_version(void);

#ifdef __cplusplus
}
#endif

#endif