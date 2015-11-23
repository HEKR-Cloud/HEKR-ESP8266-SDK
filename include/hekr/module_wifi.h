#ifndef __MODULE_WIFI_H__
#define __MODULE_WIFI_H__
#include "esp_def.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
	uint8 ssid[32];
	uint8 ssid_len;
	uint8 password[64];
	uint8 ssid_hidden;	//hidden:0 不隐藏  1 隐藏 2 禁用  3 禁用10s后启用
}t_app_set_softap_configs;

typedef enum
{
	INIT_MODE_NORMAL_MODE = 0,
	INIT_MODE_DISCONN_CLOUD,
}wifi_init_set;

typedef enum
{
	WIFI_MODE_NULL = 0x00,
	WIFI_MODE_STATION = 0x01,
	WIFI_MODE_SOFTAP = 0x02,
	WIFI_MODE_STATIONAP = 0x03,
}wifi_mode_t;

typedef enum {
	STATE_STATION_IDLE = 0,
	STATE_STATION_CONNECTING,
	STATE_STATION_WRONG_PASSWORD,
	STATE_STATION_NO_AP_FOUND,
	STATE_STATION_CONNECT_FAIL,
	STATE_STATION_GOT_IP
}wifi_status_t;
typedef void (wifi_event_t)(void *arg);


struct wifi_event_callback
{
	wifi_event_t *idle;
	wifi_event_t *connected;
	wifi_event_t *connect_fail;
};

typedef enum
{
	EVENT_CONNECT_WIFI_FAIL = 0,	//配置失败，未能连接上Wi-Fi
	EVENT_HEKR_CONFIG_TIMEOUT,		//配置超时
	EVENT_HEKR_CONFIG_FINISH		//配置成功，将会自动去连接服务器
}config_event_t;

typedef void( *hekr_config_event_cb_t)(config_event_t event);


void wifi_config_reset(void);
void start_hekr_config(hekr_config_event_cb_t event_cb, size_t timeout);
void hekr_config_event_handle(config_event_t event);
void stop_hekr_config(void);

#ifdef __cplusplus
}
#endif

#endif