# HEKR ESP8266 SDK 接口说明
**v1.0.7 by [zengxuefeng@hekr.me](mailto:zengxuefeng@hekr.me "zengxuefeng@hekr.me")** 2015/9/22 20:33:28 
## 1-1 HekrConfig (Wi-Fi一键配置)

	void hekr_config_start(hekr_config_event_cb_t event_cb, size_t timeout)

### 参数

- `event_cb` HekrConfig事件回调函数
- `timeout` 配置超时时间 (单位：`毫秒`)

### 返回值

- `无`

### 头文件

- `#include <module_wifi.h>`

### 参数类型定义

	typedef enum
	{
		EVENT_CONNECT_WIFI_FAIL = 0,	//配置失败，未能连接上Wi-Fi
		EVENT_HEKR_CONFIG_TIMEOUT,		//配置超时
		EVENT_HEKR_CONFIG_FINISH		//配置成功，将会自动去连接服务器
	}config_event_t;

	typedef void( *hekr_config_event_cb_t)(config_event_t event);


### 说明

- 上电的时候，如果FLASH中没有Wi-Fi配置信息会自动进入配置模式。


## 1-2 取消Wi-Fi 一键配置

	void hekr_config_stop(void)

### 参数

- `无`

### 返回值

- `无`

## 1-3 获取设备状态

	uint8 device_status_get(device_status_type_t item)

### 参数

- `item` 设备状态项

###返回值

- `1` 设备状态项值为1
- `0` 设备状态项值为0

###头文件

- `include<device_status.h>`

###参数类型定义

	typedef enum
	{
		DEVICE_WLAN_CONNECTED = 0,
		DEVICE_WLAN_IDLE,
		DEVICE_WLAN_CONNECTING,
		DEVICE_WLAN_CONNECT_TIMEOUT,
		DEVICE_WLAN_PASSWOR_WRONG,
		DEVICE_WLAN_AP_CANNOT_FIND,
		GOT_SERVER_IP,
		LOGGED_IN_SERVER,
		UART0_INTR,
		COMMAND_CONFIRM,
		CONNECT_CLOUD_DISABLE,
		HEKR_CONFIG_RUNNING,
		SOFTAP_CONFIG_RUNNING,
		ACCESSKEY_SET_ENABLE,
		ACCESSKEY_SET_FINISH,
		LOG_PRINT_ENABLE,
		CLOUD_SEND_QUEUE_FINISH,
		VM_EVAL_QUEUE_FINISH,
		VM_EVAL_PORT_LAN,
		VM_EVAL_PORT_UART0,
		VM_EVAL_PORT_CLOUD,
		VM_EVAL_PORT_INTERNAL
	}device_status_type_t;

## 1-4 注册设备状态改变时的回调函数

	void register_device_status_change_callback(device_status_change_callback_t *cb)

### 参数

- `cb` 设备状态改变时的回调函数

###返回值

- `无`

###头文件

- `include<device_status.h>`

###参数类型定义

	typedef void device_status_change_callback_t(device_status_type_t item,uint8 current_state)

## 1-5 启用设备状态指示引脚

	void device_status_led_task_install(uint32_t pin, uint32_t reverse)

### 参数

- `pin` 设备状态指示引脚led1
- `reverse` 设备状态指示引脚led2，与led1电平状态相反。通常不需要设置，即值为0

###返回值

- `无`

###头文件

- `include<device_status.h>`

###说明

- 该函数启用led引脚用来指示设备当前状态，不同状态时led闪烁频率不一致。
- 不同状态对应闪烁频率关系：`HEKR_CONFIG_RUNNING时ON-1.5s,OFF-1.5s`; `LOGGED_IN_SERVER时ON-0.1s,OFF-5s`; `GOT_SERVER_IP时ON-0.1s,OFF-1s`; `DEVICE_WLAN_CONNECTED时ON-0.1s,OFF-0.5s`;

##2-1 连接服务器

	void connect_server(cloud_conn_event_cb_t cb)

### 参数

- `cb` 与服务器连接事件回调函数

### 返回值

- `无`

### 头文件

- `#include <module_wifi.h>`

### 参数类型定义


	typedef enum {
		WIFI_DISCONNED = 0,		//Wi-Fi未连接
		NO_ACCESSKEY,			//设备没有accesskey
		DNS_ERROR,				//无法获取服务器IP
		DEVICE_LOGIN_ERROR,		//设备登入服务器失败
		DEVICE_LOGIN_SUCCESS,	//设备登入服务器成功
		DISCONNED_FROM_CLOUD	//设备与服务器连接断开
	}cloud_conn_event_t;

	typedef void(*cloud_conn_event_cb_t)(cloud_conn_event_t event);

## 2-2 断开与服务器的连接

	void disconnected_from_server(void)

### 参数

- `无`

### 返回值

- `无`

## 2-3 向远程终端发送消息

	uint8_t send_message_to_remote(char *tid, void *data, size_t size)

### 说明

- 给远端终端单播或者组播消息，当`tid==NULL`时为组播。
- 目前只支持组播

### 参数

- `tid` 终端ID号
- `data` 待发送的数据
- `size` 数据的大小 （单位：`字节`）

### 返回值

- `1` 成功
- `0` 失败

##2-4 注册收到服务器数据的回调函数

	void register_receive_server_data_callback(recicve_server_data_cb_t cb)

### 参数

- `cb` 收到服务器数据的回调函数

### 返回值

- `无`

### 头文件

- `#include <conn_cloud.h>`

### 参数类型定义

	typedef void(*recicve_server_data_cb_t)(void *data, size_t size);

## 2-5 启动升级

	void start_update(char *bin_dir)

### 参数

- `bin_dir` 待升级固件的http地址

### 返回值

- `无`

###头文件

- `<module_upgrade.h>`

## 2-6 检查Flash中是否存在AP信息

	uint8_t  check_wifi_config_exist(void)

### 参数

- `无`

### 返回值

- `1` 存在
- `0` 不存在

###头文件

- `<module_wifi.h>`

###说明

- 如果设备连接过AP，那么AP信息会保存到flash中，再次启动时会自动连接AP。

##3-1 注册串口收到数据的回调函数

	void register_uart_data_received_callback(uart_data_received_cb_t *cb)

### 参数

- `cb` 串口回调函数

### 返回值

- `无`

### 头文件

- `#include <uart.h>`

### 参数类型定义

	typedef void(uart_data_received_cb_t)(uint8_t data);

##3-2 注册按键中断

	uint8_t register_key_intrrupt_handle(
		size_t pin,
		GPIO_INT_TYPE intr_state,
		size_t long_press_time,
		callbcak_handle_t *short_press_handle,
		callbcak_handle_t *long_press_handle)

### 参数

- `pin` 按键引脚
- `intr_state` 中断类型
- `long_press_time` 长按所需时间，单位为ms
- `short_press_handle` 短按回调函数
- `long_press_handle` 长按回调函数

### 返回值

- `1` 注册成功
- `0` 注册失败

### 头文件

- `#include <module_key.h>`

### 示例

	register_key_intrrupt_handle
		(
			13,
			GPIO_PIN_INTR_NEGEDGE,
			3000,
			(callbcak_handle_t *)&plug_power_change,
			(callbcak_handle_t *)&wifi_config_reset
		);

- 说明 ：注册`GPIO13`引脚拉低`3000ms`执行`wifi_config_reset()`,短于`3000ms`执行`plug_power_change()`


###参数类型定义

	typedef enum {
	    GPIO_PIN_INTR_DISABLE = 0,	//中断禁止
	    GPIO_PIN_INTR_POSEDGE = 1,	//上升沿触发
	    GPIO_PIN_INTR_NEGEDGE = 2,	//下降沿触发
	    GPIO_PIN_INTR_ANYEGDE = 3,	//上升沿或下降沿触发
	    GPIO_PIN_INTR_LOLEVEL = 4,	//低电平触发
	    GPIO_PIN_INTR_HILEVEL = 5	//高电平触发
	} GPIO_INT_TYPE;

	typedef void (callbcak_handle_t)(vcboid *arg);

##3-4 设置gpio上拉使能

	void gpio_pullup_set(uint8 gpio, uint8  enable)

### 参数

- `gpio` gpio引脚
- `enable` 使能，非0表示使能，0表示禁用

### 返回值

- `无`

### 头文件

- `#include <module_gpio.h>`

## 4-1获取SDK版本号

	char *get_hekr_sdk_version(void)

### 参数

- `无`

### 返回值

- 类型 `字符串`
- 值 `版本号`

### 头文件

- `#include <device_info.h>`

## 4-2 系统日志
	
	void system_log_set(log_port_t port)

### 参数

- `port` 设置输出端口，可选参数`PORT_UART0` 、`PORT_UART1` 、`PORT_NULL`

### 返回值

- `无`

### 参数类型定义

	typedef enum
	{
		PORT_UART0 = 0, //通过uart0输出
		PORT_UART1,		//通过uart1输出
		PORT_NULL		//不输出
	}log_port_t;

### 头文件

- `#include <log.h>`

### 说明

- 日志输出会占用资源，生成固件建议关闭


## 5-1 用户函数执行入口

	void hekr_main(void)

### 说明

- 该函数在设备启动过程执行，初始化的函数放在此处执行。
- 执行时间长的任务不要放在此处执行

### 示例

	void hekr_main(void)
	{
		/*通过串口GPIO2输出信息*/
		/*波特率9600 8位数据位 1位停止位*/	
		uart_init(BIT_RATE_9600, BIT_RATE_9600);
		os_printf("\n\nsystem run !! \n\n");
		os_printf("hekr sdk ver:%s\n", get_hekr_sdk_version());
	}

### 参数

- `无`

### 返回值

- `无`

### 头文件

- `无` 该函数用户自己定义
## 备注

**基于ESP8266 SDK 1.1.2开发， [ESP8266 通用API请参考 ESP官方文档](http://bbs.espressif.com/download/file.php?id=557)**