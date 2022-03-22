#include <MQconfig.h>
#include <MQCore/MQHeader.h>
#include <GlobalVar.h>
using namespace MQ;
//MQ::Api		MQ �ṩ��api�����ӿ�
//MQ::Enum		MQ �¼�����
//MQ::Event		MQ ע���¼��ص�����
//MQ::Logging	MQ ��־
//MQ::Type		MQ ������ݷ�װ
//MQ::�ı�����	MQ �ı�����
void processEvent(const Event::NormalEvent& e)
{
	MQEventCheck(e.eventType, Enum::MQEventEnum::��Ϣ����_����)
	{
		if (e.botQQ == e.activeQQ)return;
		//��־��� fun
		MQ::Api::FrameAPI::OutPut("fun");
		//��־��� [info]fun
		Logging::info("fun");
		//����
		MQ::Api::MessageAPI::SendMsg(e.botQQ, Enum::msgType::����, "", e.activeQQ, e.msg);
		//MQ::MessageAPI::SendMsg(e.botQQ, msgType::Ⱥ, e.sourceId, "", e.msg);
	}
}
/*
* ������
* ���ڸú�(MQ_REGISTER_EVENT)����������ע��ص�����
* �ھ�̬��Ա��ʼ�������ϵͳ�����¼�֮�󣬲���û������¼�����֮ǰ��ִ��,��������SDK��ע���¼��ص�
*/
MQ_REGISTER_EVENT
{
	if (EventContInit)return;
	//ע���¼��ص�����1,���ȼ�20000
	MQ::Event::reg_Event(processEvent, 20000);
	//ע���¼��ص�����2,���ȼ�10000
	MQ::Event::reg_Event([](const Event::NormalEvent& e) {
		MQEventCheck(e.eventType, Enum::MQEventEnum::��Ϣ����_����)
		{
			if (e.botQQ == e.activeQQ)return;
			//��־��� lambda
			Api::FrameAPI::OutPut("lambda");
			//����QQ
			Api::MessageAPI::SendMsg(e.botQQ, Enum::msgType::����, "", e.activeQQ, MQ::�ı�����::����QQ() + ":" + e.msg);
			//��ֹ�������¼��ص�����ִ��,�����ȼ��ص�������Ȩ�ܾ�
			e.eventBlock();
		}
	}, 10000);
	//ע���¼��ص�����3,���ȼ�10000
	Event::reg_Event([](const Event::NormalEvent& e) {
		MQEventCheck(e.eventType, Enum::MQEventEnum::��Ϣ����_���������)
		{
			//�����¼�����ֵΪ����,�������ȼ��ص��������������޷��޸�����״̬
			e.retIgnore();
		}
		}, 10000);
	//ע�����ô���,���ȼ�ΪĬ��30000
	Event::reg_Setting([](const auto& e) {
		MessageBoxA(nullptr, "Text", "Caption", 0);
		});
	EventContInit = true;
}
