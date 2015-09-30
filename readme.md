#HEKR ESP8266 SDK

**by [zengxuefeng@hekr.me](mailto:zengxuefeng@hekr.me "zengxuefeng@hekr.me")**  2015/9/30 18:26:25  

- API见目录 [`document/esp8266_sdk_api.md`](https://github.com/HEKR-Cloud/HEKR-ESP8266-SDK/blob/master/document/ESP8266_SDK_API.md) 
- 快速入门 [`document/esp8266_sdk_user_manual.md`](https://github.com/HEKR-Cloud/HEKR-ESP8266-SDK/blob/master/document/ESP8266快速入门手册.pdf)
- SDK示例代码 [`app/user/user_main.c`](https://github.com/HEKR-Cloud/HEKR-ESP8266-SDK/blob/master/examples)

##Change Log

2015/9/30 18:24:31 

1. 加入快速入门文档
2. 添加示例代码文件夹[`examples`](https://github.com/HEKR-Cloud/HEKR-ESP8266-SDK/tree/master/examples)

2015/9/23 17:30:55 

1. 添加按键短按长按事件注册函数
2. 添加设备状态获取接口
3. 添加状态指示灯注册函数
4. 修改升级接口

2015/9/20 10:30:39 

1. 更新了智能插座示例代码，带长按进入配置模式功能。
2. Lisp升级接口更新为`(dev.upgrade [tid] [url])`
3. 更新底层升级接口