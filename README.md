# MYQQ_SDK_CPP_Ver1.9.2

MYQQ_SDK_CPP封装了提供给MQ的DLL接口相关的底层逻辑，为插件编程者提供更现代的C++接口。

### 目录

[TOC]



### Demo

```c++
#include <MQconfig.h>
#include <MQCore/MQHeader.h>
#include <GlobalVar.h>
using namespace MQ;
//MQ::Api		MQ 提供的api函数接口
//MQ::Enum		MQ 事件常量
//MQ::Event		MQ 注册事件回调函数
//MQ::Logging	MQ 日志
//MQ::Type		MQ 相关数据封装
//MQ::文本代码	MQ 文本代码
void processEvent(const Event::NormalEvent& e)
{
	MQEventCheck(e.eventType, Enum::MQEventEnum::消息类型_好友)
	{
		if (e.botQQ == e.activeQQ)return;
		//日志输出 fun
		Api::FrameAPI::OutPut("fun");
		//日志输出[info]fun
		Logging::info("fun");
		//复读
		Api::MessageAPI::SendMsg(e.botQQ, Enum::msgType::好友, "", e.activeQQ, e.msg);
		//MQ::MessageAPI::SendMsg(e.botQQ, msgType::群, e.sourceId, "", e.msg);
	}
}
/*
* 插件入口
* 请在该宏(MQ_REGISTER_EVENT)的作用域内注册回调函数
* 在静态成员初始化、插件系统载入事件之后，插件用户载入事件发生之前被执行,用于配置SDK和注册事件回调
*/
MQ_REGISTER_EVENT
{
	if (EventContInit)return;
	//注册事件回调函数1,优先级20000
	Event::reg_Event(processEvent, 20000);
	//注册事件回调函数2,优先级10000
	Event::reg_Event([](const Event::NormalEvent& e) {
		MQEventCheck(e.eventType, Enum::MQEventEnum::消息类型_好友)
		{
			if (e.botQQ == e.activeQQ)return;
			Api::FrameAPI::OutPut("lambda");
			Api::MessageAPI::SendMsg(e.botQQ, Enum::msgType::好友, "", e.activeQQ, MQ::文本代码::对象QQ() + ":" + e.msg);
			//阻止后续该事件回调函数执行,低优先级回调函数无权拒绝
			e.eventBlock();
		}
	}, 10000);
	//注册事件回调函数3,优先级15000
	Event::reg_Event([](const Event::NormalEvent& e) {
		MQEventCheck(e.eventType, Enum::MQEventEnum::消息类型_本插件载入)
		{
			//设置事件返回值为忽略,若高优先级回调函数已阻塞则无法修改阻塞状态
			e.retIgnore();
		}
		}, 15000);
	//注册设置窗口,优先级为默认30000
	Event::reg_Setting([](const auto& e) {
		MessageBoxA(nullptr, "Text", "Caption", 0);
		});
	EventContInit = true;
}
```

### 简介

- `MQ::Api` 命名空间封装了MQ提供的大部分api接口，现更新到MyQQ `1.9.2` 版本
- `MQ::文本代码` 命名空间提供了快速构造MQ文本代码的接口
- `MQ::Enum`命名空间封装了MQ相关常量 `MQEventEnum` 、事件返回值 `EventRet`、消息来源类型 `msgType`
- `MQ::Event` 命名空间提供了注册MQ各事件回调函数接口，如` reg_Event`，并且封装了MQ各事件的数据类，如 `NomarlEvent` 等，将在事件回调函数中传入
- `MQ::Type` 命名空间提供了相关数据类，如 `GroupInfo`、`GroupNotice`、`GroupMember` 等
- ......

### 预备

本项目使用 [Visual Studio](https://visualstudio.microsoft.com/zh-hans/) 构建，请确保安装了 **Visual Studio 2019** ，并勾选「使用 C++ 的桌面开发」，安装了 **MSVC v142**、**Windows 10 SDK** 组件。

若已安装 **Visual Studio 2019**，请直接打开目录下的 **[MYQQ_SDK_CPP.sln](MYQQ_SDK_CPP.sln)** 文件。

### 修改插件信息

请在 [`MQHeader.h`](include/MQcore/MQHeader.h) 文件修改插件相关的 `Id` 、`Author`、`Desc` 、`Version` 信息，并将项目重命名为你的插件名，并且该项需要与 `PluginId` 宏一致，否则插件将会载入失败。

### 编写插件

移除 [`main/MQdemo.cpp`](main/MQdemo.cpp) 或在其基础上修改，实现自己的功能。

具体API函数和事件函数请在命名空间 `MQ` 内查找。

若有未添加的MQ api函数请自行添加，`MyQQApi.dll` 载入句柄为`MQHModule` 。

### 生成项目

在 **Visual Studio** 使用快捷键 **Ctrl + Alt + F7** 生成项目，生成的 **dll文件** 将放在文件夹 **[out](out) **下。

然后只需要将生成的 **dll文件** 拷贝到 **MyQQ\plugin** 文件夹下，然后打开 **MyQQ.exe** ，在 **插件管理** 启用插件即可。

### 注意事项

- 该SDK运行需安装 Visual C++ 可再发行软件包，请提醒用户安装，下载地址见 [最新支持的 Visual C++ 下载](https://support.microsoft.com/zh-cn/help/2977003/the-latest-supported-visual-c-downloads)。

### 问题反馈

如果使用该sdk过程中遇到任何问题、Bug，或有其它意见或建议，欢迎提 [issue](https://github.com/Wmj520/MYQQ_SDK_CPP/issues) ，或者加 **QQ2216193879** 交流讨论。
