#ifndef __CONN_CLOUD_H__
#define __CONN_CLOUD_H__
#include "esp_def.h"
#include "espconn.h"


typedef enum {
	CLOUD_EVEN_WIFI_DISCONNED = 0,		//Wi-Fi未连接
	CLOUD_EVEN_NO_ACCESSKEY,			//设备没有accesskey
	CLOUD_EVEN_DNS_ERROR,				//无法获取服务器ip
	CLOUD_EVEN_DEVICE_LOGIN_ERROR,		//设备登入服务器失败
	CLOUD_EVEN_DEVICE_LOGIN_SUCCESS,	//设备登入服务器成功
	CLOUD_EVEN_DISCONNED_FROM_CLOUD,	//设备与服务器连接断开
	CLOUD_EVEN_CONNECT_CLOUD_DISABLE	//设备连接服务器已被禁用
}cloud_conn_event_t;

typedef void(*cloud_conn_event_cb_t)(cloud_conn_event_t event);
typedef void(*recicve_server_data_cb_t)(void *data, size_t size);


void  connect_server(cloud_conn_event_cb_t cb);
void  disconnect_from_server(void);
void  reconnect_cloud(void);
uint8_t send_message_to_remote(char *tid, void *data, size_t size);
void register_receive_server_data_callback(recicve_server_data_cb_t cb);
#endif