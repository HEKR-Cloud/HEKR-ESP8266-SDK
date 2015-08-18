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
	uint8 ssid_hidden;	//hidden:0 ������  1 ���� 2 ����  3 ����10s������
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
	EVENT_CONNECT_WIFI_FAIL = 0,	//����ʧ�ܣ�δ��������Wi-Fi
	EVENT_HEKR_CONFIG_TIMEOUT,		//���ó�ʱ
	EVENT_HEKR_CONFIG_FINISH		//���óɹ��������Զ�ȥ���ӷ�����
}config_event_t;

typedef void( *hekr_config_event_cb_t)(config_event_t event);


FUN_ATTRIBUTE void  wifi_softap_set(t_app_set_softap_configs *configs);
FUN_ATTRIBUTE void  wifi_softap_key_get(char *key);
FUN_ATTRIBUTE bool  wifi_get_mac_str(char *des, uint8_t if_index);
FUN_ATTRIBUTE void  wifi_station_set(char *ssid, char *password);
FUN_ATTRIBUTE void  gemini_network_init(wifi_init_set set);
FUN_ATTRIBUTE void  wifi_scanning();
FUN_ATTRIBUTE void wifi_config_reset(void);
FUN_ATTRIBUTE wifi_status_t  update_device_network_state(void);
FUN_ATTRIBUTE void  check_station_connect_and_connect_cloud(void);
FUN_ATTRIBUTE bool  gemini_wifi_mode_switch(wifi_mode_t opmode);
FUN_ATTRIBUTE void wifi_connect_state_check(void *arg);
FUN_ATTRIBUTE void inline wifi_event_callback_disable(struct wifi_event_callback *p);
FUN_ATTRIBUTE void  hekr_config_callback(wifi_station_config_t *config);
FUN_ATTRIBUTE void hekr_config_start(hekr_config_event_cb_t event_cb, size_t timeout);
FUN_ATTRIBUTE void hekr_config_stop(void);

#ifdef __cplusplus
}
#endif

#endif