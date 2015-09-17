#HEKR SDK 使用说明

**v1.1.0 by [zengxuefeng@hekr.me](mailto:zengxuefeng@hekr.me "zengxuefeng@hekr.me")** 2015/9/17 16:51:59   

## 1-1 编译环境搭建

- 编译环境搭建，参照ESP官方资料（建议使用Linux平台）

## 2-1 编译固件

- 在SDK目录下执行`make app=FIRMWARETYPE flash=FLASHSIZE`
- 生成固件到`bin/upgrade/`目录下

### make参数说明

- 参数`FIRMWARETYPE` 选择编译生成固件类型，用于云端升级
- 参数`FLASHSIZE` Flash的大小 (单位`KiB`)

###示例

- `make app=1 flash=2048`  生成支持2048KiB大小FLASH `user1.bin`

###说明

- 生成烧录所需的固件请`user1.bin` ，`user2.bin` 云端升级时才需要 
## 3-1 烧录对应地址说明

<table>

<tr><th>文件</th><th>烧录地址(byte)</th><th>备注</th></tr>

<tr><th>boot_v1.2.bin</th><th>0x00000</th><th>bootload</th></tr>
<tr><th>esp_init_data_default.bin</th><th>0xFC000</th><th>存放RF的默认配置</th></tr>
<tr><th>user1.bin</th><th>0x01000</th><th>用户固件</th></tr>
<tr><th>SfsPart.bin</th><th>0x100000</th><th>文件系统</th></tr>
<tr><th>blank.bin</th><th>0x1FE000</th><th>用于擦除Wi-Fi相关设置</th></tr>

</table>

##4-1 烧录工具

- `Windows` 平台使用 `ESP_DOWNLOAD_TOOL` [官网链接](http://bbs.espressif.com/viewtopic.php?f=57&t=433) [备用下载地址](http://pan.baidu.com/s/1DfqJc)
- `Linux` 平台用`flashtool.py` 和 `debug.py`脚本 [链接](https://github.com/HEKR-Cloud/HEKR-ESP8266-SDK/tree/master/app)

##4-2 `ESP_DOWNLOAD_TOOL` 使用说明

1. 按照 `3-1` 设置好需要下载的文件和对应地址
2. `FLASH_SIZE` 选择对应`16Mbit`(16Mbit以上的FLASHZ设置保持和16Mbit相同)
3.  选择对应模块的COM口
4.  将模块GPIO0拉低，然后重启，模块将会进入下载模式。

##4-3 `flashtool.py` 脚本使用说明

#### 1-1 手动烧录

1. 执行 `./flashtool.py --port /dev/ttyUSB0 -b 921600  write_flash --flash_size 16m  0x01000 ./xxx.bin`
2. 将模块GPIO0拉低，然后重启，开始下载。

#### 1-2 自动烧录

`由脚本控制串口芯片的RTS和DTR,让ESP进入下载模式`

1. 需要硬件上短接串口模块的`RTS`和ESP模块的`RST`引脚，串口模块的`DTR`和ESP模块的`GPIO0`引脚

2. 执行 `./flashtool.py --port /dev/ttyUSB0 -b 921600  write_flash --flash_size 16m  0x01000 ./xxx.bin` 

#### 2-1 参数说明

- `/dev/ttyUSB0` 待下载的设备
- `921600`下载波特率
- `16m` FLASH大小，16m对应16Mbit Flash （16Mbit 以上的Flash也使用这个设置）
- `0x01000`烧录地址
- `./xxx.bin` 待烧录的文件

##4-3 `debug.py` 脚本使用说明

完成编译固件和下载固件

#### 参数

- `--all`完成编译固件并烧录所有固件（用于擦除原来的设置）
- `--onebin` 完成编译固件并只烧录用户固件（设置不会丢失）

#### 示例

`./debug.py --all`

## 5-1注意事项：
-	Flash 大小必须使用`2MiB`或以上
-	Flash 地址`0x100000`到`0x1FA000`被文件系统所用，用户不要往里面写数据