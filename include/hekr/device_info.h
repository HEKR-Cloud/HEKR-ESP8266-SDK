#ifndef __DEVICE_INFO_H__
#define __DEVICE_INFO_H__
#include <esp_def.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef struct
{
	int32_t mid;
	int32_t pid;
	int32_t cid;
}device_id_t;

typedef struct {
	device_id_t id;
}product_info_t;

 
 
char *get_tid(void);

bool product_info_load(product_info_t *info);

void set_device_id(device_id_t id);
 
char *get_hekr_sdk_version(void);

#ifdef __cplusplus
}
#endif

#endif
