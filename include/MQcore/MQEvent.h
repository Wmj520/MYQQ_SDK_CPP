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
			��Ϣ����_���� = 0,
			��Ϣ����_���� = 1,
			��Ϣ����_���� = 2,
			�¼�����_ͬ�� = 10,
			�¼�����_�ܾ� = 20
		};
		enum class MQEventEnum : Integer
		{
			��Ϣ����_δ���� = -1,
			��Ϣ����_���� = 1,
			��Ϣ����_Ⱥ = 2,
			��Ϣ����_������ = 3,
			��Ϣ����_Ⱥ��ʱ�Ự = 4,
			��Ϣ����_��������ʱ�Ự = 5,
			��Ϣ����_������ʱ�Ự = 6,
			��Ϣ����_��������Ӻ��� = 1000,
			��Ϣ����_��������Ӻ��� = 1001,
			��Ϣ����_����״̬�ı� = 1002,
			��Ϣ����_��ɾ������ = 1003,
			��Ϣ����_����ǩ����� = 1004,
			��Ϣ����_˵˵������ = 1005,
			��Ϣ����_������������ = 1006,
			��Ϣ����_���ѽ����״η���Ự = 1007,
			��Ϣ����_�����Ѷ��� = 1008,
			��Ϣ����_�����ļ����� = 1009,
			��Ϣ����_������Ƶ���� = 1010,
			��Ϣ����_��ͬ���Ϊ���� = 1011,
			��Ϣ����_���ܾ���Ϊ���� = 1012,
			��Ϣ����_ĳ���������Ⱥ = 2001,
			��Ϣ����_ĳ�˱��������Ⱥ = 2002,
			��Ϣ����_ĳ���ѱ�������Ⱥ = 20021,
			��Ϣ����_�ұ��������Ⱥ = 2003,
			��Ϣ����_ĳ�˱���׼������Ⱥ = 2005,
			��Ϣ����_ĳ���˳�Ⱥ = 2006,
			��Ϣ����_ĳ�˱������Ƴ�Ⱥ = 2007,
			��Ϣ����_ĳȺ����ɢ = 2008,
			��Ϣ����_ĳ�˳�Ϊ���� = 2009,
			��Ϣ����_ĳ�˱�ȡ������ = 2010,
			��Ϣ����_Ⱥ��Ƭ�䶯 = 2011,
			��Ϣ����_Ⱥ���䶯 = 2012,
			��Ϣ����_Ⱥ����䶯 = 2013,
			��Ϣ����_���󱻽��� = 2014,
			��Ϣ����_���󱻽������ = 2015,
			��Ϣ����_Ⱥ�ܿ���ȫȺ���� = 2016,
			��Ϣ����_Ⱥ�ܹر�ȫȺ���� = 2017,
			��Ϣ����_Ⱥ�ܿ����������� = 2018,
			��Ϣ����_Ⱥ�ܹر��������� = 2019,
			��Ϣ����_���ѳ�����Ϣ = 13002,
			��Ϣ����_Ⱥ������Ϣ = 2020,
			��Ϣ����_Ⱥ�ļ����� = 2021,
			��Ϣ����_Ⱥ��Ƶ���� = 2022,
			��Ϣ����_������������ = 3001,
			��Ϣ����_Ⱥ�������� = 3002,
			��Ϣ����_Ⱥ��Ϣ������Ϊ���� = 3003,
			��Ϣ����_Ⱥ��Ϣ��ȡ������ = 3004,
			��Ϣ����_��ܼ������ = 10000,
			��Ϣ����_��ܼ������� = 10001,
			��Ϣ����_�����һ���µ��ʺ� = 11000,
			��Ϣ����_QQ��¼��� = 11001,
			��Ϣ����_QQ���ֶ����� = 11002,
			��Ϣ����_QQ��ǿ������ = 11003,
			��Ϣ����_QQ��ʱ������Ӧ����� = 11004,
			��Ϣ����_��������� = 12000, //����20�ɾܾ����� ��������ֵ����Ϊ����
			��Ϣ����_��������� = 12001, //����20�ɾܾ����� ��������ֵ����Ϊ��������
			��Ϣ����_��������� = 12002, //��Ȩ�ܾ�
			��Ϣ����_�������� = 12003, //�����ʽ�ο������� 1 = ������� 2 = �Ҽ����� 3 = ���˫��
			��Ϣ����_�յ��Ƹ�ͨת�� = 80001,
			��Ϣ����_�յ�Ⱥ�ĺ�� = 80002,
			��Ϣ����_�յ�˽�ĺ�� = 80003,
			��Ϣ����_Ⱥ�ĺ������ȡ = 80012,
			��Ϣ����_˽�ĺ������ȡ = 80013,
			��Ϣ����_�����˷�����Ϣ = 80004,
			��Ϣ����_�����豸���� = 13000,
			��Ϣ����_�����豸���� = 13001
		};
		enum msgType :Integer
		{
			���� = 1, Ⱥ = 2, ������ = 3,
			Ⱥ��ʱ�Ự = 4, ��������ʱ�Ự = 5, ������ʱ�Ự = 6
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
			UserEvent() : Event(), operation(Enum::EventRet::��Ϣ����_����) {}
			virtual ~UserEvent() {}
			void retIgnore(void)const
			{
				if (!retBlocked())
					this->operation = Enum::EventRet::��Ϣ����_����;
			}
			void retContinue(void)const
			{
				if (!retBlocked())
					this->operation = Enum::EventRet::��Ϣ����_����;
			}
			void retBlock(void)const
			{
				this->operation = Enum::EventRet::��Ϣ����_����;
			}
			bool retBlocked(void)const
			{
				return this->operation == Enum::EventRet::��Ϣ����_����;
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
				this->operation = Enum::EventRet::��Ϣ����_����;
			}
		};
		struct EndEvent : public SysEvent<Enum::EventRet> {
			EndEvent() {
				this->operation = Enum::EventRet::��Ϣ����_����;
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

