#pragma once

#ifndef __MQ_EVENT__
#define __MQ_EVENT__
#include <MQCore/MQType.h>

#define EVENT(ReturnType, Name, Size) __pragma(comment(linker, "/EXPORT:" #Name "=_" #Name "@" #Size))\
 extern "C" ReturnType __stdcall Name

#define __MQEVENT(__Event, __EventData)\
		void reg_##__Event(const std::function<void(__EventData)>& _Callback, const uint16_t& priority = 30000);\
		void clr_##__Event(void);


#ifndef _MQ_EVENT_DEFINE_
namespace MQ
{
	namespace Enum
	{
		enum class EventRet : Integer
		{
			消息处理_忽略 = 0,
			消息处理_继续 = 1,
			消息处理_拦截 = 2,
			事件处理_同意 = 10,
			事件处理_拒绝 = 20
		};
		enum class MQEventEnum : Integer
		{
			消息类型_未定义 = -1,
			消息类型_好友 = 1,
			消息类型_群 = 2,
			消息类型_讨论组 = 3,
			消息类型_群临时会话 = 4,
			消息类型_讨论组临时会话 = 5,
			消息类型_在线临时会话 = 6,
			消息类型_被单向添加好友 = 1000,
			消息类型_被请求添加好友 = 1001,
			消息类型_好友状态改变 = 1002,
			消息类型_被删除好友 = 1003,
			消息类型_好友签名变更 = 1004,
			消息类型_说说被评论 = 1005,
			消息类型_好友正在输入 = 1006,
			消息类型_好友今天首次发起会话 = 1007,
			消息类型_被好友抖动 = 1008,
			消息类型_好友文件接收 = 1009,
			消息类型_好友视频接收 = 1010,
			消息类型_被同意加为好友 = 1011,
			消息类型_被拒绝加为好友 = 1012,
			消息类型_某人申请加入群 = 2001,
			消息类型_某人被邀请加入群 = 2002,
			消息类型_某人已被邀请入群 = 20021,
			消息类型_我被邀请加入群 = 2003,
			消息类型_某人被批准加入了群 = 2005,
			消息类型_某人退出群 = 2006,
			消息类型_某人被管理移除群 = 2007,
			消息类型_某群被解散 = 2008,
			消息类型_某人成为管理 = 2009,
			消息类型_某人被取消管理 = 2010,
			消息类型_群名片变动 = 2011,
			消息类型_群名变动 = 2012,
			消息类型_群公告变动 = 2013,
			消息类型_对象被禁言 = 2014,
			消息类型_对象被解除禁言 = 2015,
			消息类型_群管开启全群禁言 = 2016,
			消息类型_群管关闭全群禁言 = 2017,
			消息类型_群管开启匿名聊天 = 2018,
			消息类型_群管关闭匿名聊天 = 2019,
			消息类型_好友撤回消息 = 13002,
			消息类型_群撤回消息 = 2020,
			消息类型_群文件接收 = 2021,
			消息类型_群视频接收 = 2022,
			消息类型_好友语音接收 = 3001,
			消息类型_群语音接收 = 3002,
			消息类型_群消息被设置为精华 = 3003,
			消息类型_群消息被取消精华 = 3004,
			消息类型_框架加载完成 = 10000,
			消息类型_框架即将重启 = 10001,
			消息类型_添加了一个新的帐号 = 11000,
			消息类型_QQ登录完成 = 11001,
			消息类型_QQ被手动离线 = 11002,
			消息类型_QQ被强制离线 = 11003,
			消息类型_QQ长时间无响应或掉线 = 11004,
			消息类型_本插件载入 = 12000, //返回20可拒绝加载 其他返回值均视为允许
			消息类型_插件被启用 = 12001, //返回20可拒绝启用 其他返回值均视为允许启用
			消息类型_插件被禁用 = 12002, //无权拒绝
			消息类型_插件被点击 = 12003, //点击方式参考子类型 1 = 左键单击 2 = 右键单击 3 = 左键双击
			消息类型_收到财付通转账 = 80001,
			消息类型_收到群聊红包 = 80002,
			消息类型_收到私聊红包 = 80003,
			消息类型_群聊红包被领取 = 80012,
			消息类型_私聊红包被领取 = 80013,
			消息类型_机器人发出消息 = 80004,
			消息类型_其他设备上线 = 13000,
			消息类型_其他设备下线 = 13001
		};
		enum msgType :Integer
		{
			好友 = 1, 群 = 2, 讨论组 = 3,
			群临时会话 = 4, 讨论组临时会话 = 5, 在线临时会话 = 6
		};
	}

	namespace Event
	{
		class Event
		{
		public:
			void eventBlock()const { EventContinue = false; }
			bool eventContinue(void)const { return this->EventContinue; }
		protected:
			std::time_t EventTime;
			mutable std::atomic_bool EventContinue = true;
			Event() : EventTime(std::time(0)) {}
		};
		class UserEvent : public Event
		{
		public:
			mutable Enum::EventRet operation;
			UserEvent() : Event(), operation(Enum::EventRet::消息处理_忽略) {}
			virtual ~UserEvent() {}
			void retIgnore(void)const
			{
				if (!retBlocked())
					this->operation = Enum::EventRet::消息处理_忽略;
			}
			void retContinue(void)const
			{
				if (!retBlocked())
					this->operation = Enum::EventRet::消息处理_继续;
			}
			void retBlock(void)const
			{
				this->operation = Enum::EventRet::消息处理_拦截;
			}
			bool retBlocked(void)const
			{
				return this->operation == Enum::EventRet::消息处理_拦截;
			}
		};
		template<class _OpTy = Enum::EventRet>
		class SysEvent : public Event
		{
		public:
			mutable _OpTy operation;
			SysEvent() : Event() {}
			virtual ~SysEvent() {}
			void block(const _OpTy& _str)const
			{
				operation = _str;
			}
		};
		struct SettingEvent : public SysEvent<Enum::EventRet> {
			SettingEvent() : SysEvent<Enum::EventRet>() {
				this->operation = Enum::EventRet::消息处理_忽略;
			}
		};
		struct EndEvent : public SysEvent<Enum::EventRet> {
			EndEvent() {
				this->operation = Enum::EventRet::消息处理_忽略;
			}
		};
		struct NormalEvent : public UserEvent
		{
			Str botQQ;
			Integer eventType;
			Integer extraType;
			Str sourceId;
			Str activeQQ;
			Str passiveQQ;
			Str msg;
			Str msgNum;
			Str msgId;
			Str rawMsg;
			char* retText;
			NormalEvent(Text botQQ, Integer eventType, Integer extraType, Text sourceId, Text activeQQ, Text passiveQQ,
				Text msg, Text msgNum, Text msgId, Text rawMsg, char* retText) :botQQ(botQQ), eventType(eventType), extraType(extraType), sourceId(sourceId), activeQQ(activeQQ),
				passiveQQ(passiveQQ), msg(msg), msgNum(msgNum), msgId(msgId), rawMsg(rawMsg), retText(retText)
			{}
		};
		struct MessageEvent : public UserEvent
		{
			Text botQQ; Integer msgType;  Text rawText; Text cookies; Text sessionKey; Text clientKey;
			MessageEvent(Text botQQ, Integer msgType, Text rawText, Text cookies, Text sessionKey, Text clientKey)
				:botQQ(botQQ), msgType(msgType), rawText(rawText), cookies(cookies), sessionKey(sessionKey), clientKey(clientKey)
			{}
		};


		__MQEVENT(Setting, SettingEvent const&)
		__MQEVENT(End, EndEvent const&)
		__MQEVENT(Event, NormalEvent const&)
		__MQEVENT(Message, MessageEvent const&)
	}
	

}

#define MQEventCheck(_EventType, _Event) if(static_cast<Integer>(_Event) == _EventType)
#endif // !_MQ_EVENT_DEFINE_

void CallingConvention __Init(void);
void CallingConvention __UnInit(void);
#define OutTime(num) if (num < (InitTime - clock()) / CLK_TCK) 
void init();
#define MQ_REGISTER_EVENT						\
	void init()
#undef __MQEVENT
#endif // !__MQ_EVENT__

