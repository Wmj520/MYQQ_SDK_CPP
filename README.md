# MYQQ_SDK_CPP

MYQQ_SDK_CPP封装了提供给MQ的DLL接口相关的底层逻辑，为插件编程者提供更现代的C++接口。

### 目录

[TOC]



### Demo

```c++
#include <MQconfig.h>
#include <MQCore/MQHeader.h>
#include <GlobalVar.h>
using namespace MQ;
void processEvent(const NormalEvent& e)
{
	MQEventCheck(e.eventType, MQ::MQEventEnum::消息类型_好友)
	{
		if (e.botQQ == e.activeQQ)return;
		MQ::FrameAPI::OutPut("fun");
		MQ::MessageAPI::SendMsg(e.botQQ, msgType::好友, "", e.activeQQ, e.msg);
		//MQ::MessageAPI::SendMsg(e.botQQ, msgType::群, e.sourceId, "", e.msg);
	}
}
MQ_REGISTER_EVENT
{
	if (EventContInit)return;	
	//注册事件处理函数1,优先级20000
	MQ::reg_Event(processEvent, 20000);
	//注册事件处理函数2,优先级10000
	MQ::reg_Event([](const NormalEvent& e) {
		MQEventCheck(e.eventType, MQ::MQEventEnum::消息类型_好友)
		{
			if (e.botQQ == e.activeQQ)return;
			MQ::FrameAPI::OutPut("lambda");
			MQ::MessageAPI::SendMsg(e.botQQ, msgType::好友, "", e.activeQQ, e.msg);
			//阻止后续该事件处理函数执行,低优先级处理函数无权拒绝
			e.eventBlock();
		}
	}, 10000);
	//注册事件处理函数3,优先级1
	MQ::reg_Event([](const NormalEvent& e) {
		MQEventCheck(e.eventType, MQ::MQEventEnum::消息类型_本插件载入)
		{

		}
		}, 10000);
	//注册设置窗口,优先级为默认30000
	MQ::reg_Setting([](const auto& e) {
		MessageBoxA(nullptr, "Text", "Caption", 0);
		});
	EventContInit = true;
}
```

### 简介

系统载入函数-用户载入函数-用户事件处理函数
