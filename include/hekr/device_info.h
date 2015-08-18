#ifndef __DEVICE_INFO_H__
#define __DEVICE_INFO_H__
#include <esp_def.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef struct {
	struct
	{
		int32_t mid;
		int32_t cid;
		int32_t pid;
	}id;
}product_info_t;

 
FUN_ATTRIBUTE char *get_tid(void);
FUN_ATTRIBUTE bool product_info_load(product_info_t *info);
FUN_ATTRIBUTE inline char *get_hekr_sdk_version(void);

#ifdef __cplusplus
}
#endif

#endif
