# BT music sink relay示例

源码路径：example/bt/music_sink_with_relay

{#Platform_music_sink}
## 支持的平台
<!-- 支持哪些板子和芯片平台 -->
+ eh-lb52J


## 概述
<!-- 例程简介 -->
本例程演示在music_sink基础上，需要两个板子下载该工程，实现两个设备同时播放手机音乐


## 例程的使用
<!-- 说明如何使用例程，比如连接哪些硬件管脚观察波形，编译和烧写可以引用相关文档。
对于rt_device的例程，还需要把本例程用到的配置开关列出来，比如PWM例程用到了PWM1，需要在onchip菜单里使能PWM1 -->
例程分为两部分:
1. 一部分是和手机之间操作，与music_sink相同，工程开机会打开蓝牙的Inquiry scan和psage scan，用手机等A2DP source设备可以搜索到本机并发起连接，连上以后即可播放手机音乐。
2. 另外一部分是两个板子之间的操作，两个板子需要完成配对才能实现音乐的转发。同时有且只有一个板子能够与手机相连，没有连接手机的板子，会收到转发的音乐信息。
2.1 被手机连上的板子会被配置成relay src角色，否则可以通过finsh命令music set_role x来设置角色。(1是relay sink;2是relay src)。但需要保证relay src是和手机连接的板子。
如果正在配对或配对已经完成，设置角色会失败；可以通过music get_role来检查当前角色。只有src和sink才能进行配对。
2.2 当两个板子角色确定好后，通过music pair来进行配对，配对成功会看到"A2DP relay paired! Role is x"的log
2.3 通过music unpair来取消两个板子之间配对。
2.4 在两个板子没有配对之前，可以通过music set_chnl x(0代表src左声道/sinky右声道，1代表src右声道/sink左声道，2代表两边都播放左声道)来设定两个板子的声道。
3. 本机的蓝牙名称默认是sifli_music_sink。


### 硬件需求
运行该例程前，需要准备：
+ 两块本例程支持的开发板（[支持的平台](#Platform_music_sink)）。
+ 喇叭。

### menuconfig配置

1. 使能AUDIO CODEC 和 AUDIO PROC：
![AUDIO CODEC & PROC](./assets/mc_audcodec_audprc.png)
2. 使能AUDIO(`AUDIO`)：
![AUDIO](./assets/mc_audio.png)
3. 使能AUDIO MANAGER.(`AUDIO_USING_MANAGER`)
![AUDIO_USING_MANAGER](./assets/mc_audio_manager.png)
4. 使能蓝牙(`BLUETOOTH`)：
![BLUETOOTH](./assets/mc_bluetooth.png)
5. 使能A2DP SNK和AVRCP：
![A2DP SNK & AVRCP](./assets/mc_bt_a2dp_avrcp.png)
6. 使能BT connection manager：
![BT CM](./assets/mc_bt_cm.png)
7. 使能NVDS
![NVDS](./assets/mc_bt_nvds.png)


### 编译和烧录
切换到例程project目录，运行scons命令执行编译：
```c
> scons --board=eh-lb525 -j32
```
切换到例程`project/build_xx`目录，运行`uart_download.bat`，按提示选择端口即可进行下载：
```c
$ ./uart_download.bat

     Uart Download

please input the serial port num:5
```
关于编译、下载的详细步骤，请参考[快速入门](/quickstart/get-started.md)的相关介绍。

## 例程的预期结果
<!-- 说明例程运行结果，比如哪几个灯会亮，会打印哪些log，以便用户判断例程是否正常运行，运行结果可以结合代码分步骤说明 -->
例程启动后：
能够实现手机音乐的转发，转发设备之间声音同步且无卡顿

## 异常诊断


## 参考文档
<!-- 对于rt_device的示例，rt-thread官网文档提供的较详细说明，可以在这里添加网页链接，例如，参考RT-Thread的[RTC文档](https://www.rt-thread.org/document/site/#/rt-thread-version/rt-thread-standard/programming-manual/device/rtc/rtc) -->

## 更新记录
|版本 |日期   |发布说明 |
|:---|:---|:---|
|0.0.1 |01/2025 |初始版本 |
| | | |
| | | |
