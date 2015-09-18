#HEKR SDK 使用说明

**v1.0.0 by [xuefeng.zeng@hekr.me](mailto:xuefeng.zeng@hekr.me "xuefeng.zeng@hekr.me")** 2015/8/18 17:40:40  

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
## 3-1 烧录说明

<table>

<tr><th>文件</th><th>烧录地址(byte)</th><th>备注</th></tr>

<tr><th>boot_v1.2.bin</th><th>0x00000</th><th>bootload</th></tr>
<tr><th>esp_init_data_default.bin</th><th>0xFC000</th><th>存放RF的默认配置</th></tr>
<tr><th>user1.bin</th><th>0x01000</th><th>用户固件</th></tr>
<tr><th>SfsPart.bin</th><th>0x100000</th><th>文件系统</th></tr>
<tr><th>blank.bin</th><th>0x1FE000</th><th>用于擦除Wi-Fi相关设置</th></tr>

</table>

###注意：
-	Flash 大小必须使用`2MiB`或以上
-	Flash 地址`0x100000`到`0x1FA000`被文件系统所用，用户不要往里面写数据