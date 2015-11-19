#HEKR ESP8266 SDK

**by [zengxuefeng@hekr.me](mailto:zengxuefeng@hekr.me "zengxuefeng@hekr.me")** 

-  [API手册](https://github.com/HEKR-Cloud/HEKR-ESP8266-SDK/raw/master/document/ESP8266_SDK_API.pdf)
-  [快速入门手册](https://github.com/HEKR-Cloud/HEKR-ESP8266-SDK/raw/master/document/ESP8266%E5%BF%AB%E9%80%9F%E5%85%A5%E9%97%A8%E6%89%8B%E5%86%8C.pdf)
- [SDK示例代码](https://github.com/HEKR-Cloud/HEKR-ESP8266-SDK/blob/master/examples)

##Change Log

2015/11/19 20:31:51 

1. 更新OTA：支持APP 进行OTA、对OTA加入多重校验机制稳定性大幅度提高
2. 同步更新ESP官方SDK1.4.0
3. hekr_config性能和稳定性大幅度提高
4. 更新虚拟机

2015/10/9 15:08:58 

1. 修复OTA升级过程中按键中断导致重启的问题
2. HEKR_CONFIG 相关API更名

2015/9/30 18:24:31 

1. 加入[快速入门手册](https://github.com/HEKR-Cloud/HEKR-ESP8266-SDK/blob/master/document/ESP8266%E5%BF%AB%E9%80%9F%E5%85%A5%E9%97%A8%E6%89%8B%E5%86%8C.pdf) 
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