#ifndef __CONN_CLOUD_H__
#define __CONN_CLOUD_H__
#include "esp_def.h"
#include "espconn.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	WIFI_DISCONNED = 0,		//Wi-Fi未连接
	NO_ACCESSKEY,			//设备没有accesskey
	DNS_ERROR,				//无法获取服务器ip
	DEVICE_LOGIN_ERROR,		//设备登入服务器失败
	DEVICE_LOGIN_SUCCESS,	//设备登入服务器成功
	DISCONNED_FROM_CLOUD	//设备与服务器连接断开
}cloud_conn_event_t;

typedef void(*cloud_conn_event_cb_t)(cloud_conn_event_t event);
typedef void(*recicve_server_data_cb_t)(void *data, size_t size);

FUN_ATTRIBUTE void  connect_server(cloud_conn_event_cb_t cb);
FUN_ATTRIBUTE void  disconnected_from_server(void);
FUN_ATTRIBUTE void  reconnect_cloud(void);
FUN_ATTRIBUTE uint8_t send_data_to_cloud(void *src, size_t size);
FUN_ATTRIBUTE void start_connect_cloud(cloud_conn_event_cb_t cb);
FUN_ATTRIBUTE void register_receive_server_data_callback(recicve_server_data_cb_t cb);

#ifdef __cplusplus
}
#endif

#endif