#pragma once
#include <cstdint>
#include <string>
#ifndef __MQTYPE__
#define __MQTYPE__

typedef const char* Text;
typedef std::string Str;
typedef std::stringstream StrBuffer;
typedef int32_t Integer;
typedef uint32_t UInteger;
typedef int64_t LLInteger;
typedef uint64_t ULLInteger;
typedef int8_t SInteger;
typedef uint8_t SUInteger;
namespace MQ::Type
{
	typedef struct
	{
		Str publisher; //������
		Str title;		//����
		Str content;	//����
		bool isTop;		//�Ƿ��ö�
		Str fid;		//
		Str timeTamp;	//����ʱ���
	}GroupNotice;
	typedef struct
	{
		Str groupId;
		Str groupName;
		Str groupOwner;
		UInteger groupMemNum;
	}GroupInfo;
	typedef struct
	{
		Str groupId;					//Ⱥ��
		Str uin;						//QQ��
		Str nick;						//�ǳ�
		ULLInteger join_time;			//��Ⱥʱ�� 10λʱ���
		ULLInteger last_speak_time;		//�����ʱ�� 10λʱ���
		Str card;						//Ⱥ�ǳ�
		Integer point;					//��Ծ����
		Integer level;					//Ⱥ�ĵȼ�
		Integer role;					//����Ȩ�� 0Ⱥ�� 1����Ա 2��ͨ��Ա
	}groupMemberInfoV1;
	typedef struct
	{
		Str uin;						//QQ��
		Str qage;						//Q��
		Str card;						//Ⱥ�ǳ�
		ULLInteger join_time;			//��Ⱥʱ�� 10λʱ���
		ULLInteger last_speak_time;		//�����ʱ�� 10λʱ���
		Str g;							//�Ա� 0�� 1Ů -1δ֪
		Integer point;					//��Ծ����
		Integer level;					//Ⱥ�ĵȼ�
		Integer role;					//����Ȩ�� 0Ⱥ�� 1����Ա 2��ͨ��Ա
	}groupMemberInfoV2;
	typedef struct
	{
		UInteger type;
		Str Id;
		Str filename;
		Str fileMd5;
		Str fileSize;
		Str fileSha;
		UInteger downloadNum;
		Str uploadQQ;
		Str uploadName;
		Str uploadTime;
	}GroupFile;
	//�����Ϣ
	typedef struct
	{
		Str name;
		Str idCard;	//���֤
		Str balance;	//���
	}BalanceInfo;
	//�ȼ���Ϣ
	typedef struct
	{
		Str objQQ;
		Str actDay;		//��Ծ����
		Str remainActDay;	//ʣ���Ծ����
		Str vip;			//��Ա
	}LevelInfo;
	//Ⱥ����
	typedef struct
	{
		Str giftId;		//Ⱥ����ID
		Str giftName;		//Ⱥ��������
		Integer giftNum;	//Ⱥ��������
	}GroupGift;
	//��Ƭǽ
	typedef struct
	{
		Str filekey;
		Str uploadTime;	//�ϴ�ʱ���,10λ
		Str pic_url_640;
		Str pic_url_160;
		Str pic_url_100;
		Str pic_url_0;
	}PicWaller;
	//Ⱥ��ϸ��Ϣ
	typedef struct
	{
		bool forbid_chat;		//��������ʱ�Ự	1Ϊ�ر�,0Ϊ����
		bool forbid_discuss;	//�������µ�Ⱥ��	1Ϊ�ر�,0Ϊ����
		bool invite_friend;		//�������������Ⱥ	0Ϊ������,1Ϊ����
		bool search;			//��������		1Ϊ�ر�,0Ϊ����
		bool me_shutup;			//���Ƿ񱻽���		1Ϊ�ر�,0Ϊ����
		Integer me_shutupTime;	//����ʣ������		me_shutup��Ϊ0ʱΪʣ������
		bool all_shutup;		//ȫȺ����			0Ϊ�ر�,����ΪȫȺ����
		bool file;				//�ϴ�Ⱥ�ļ�		1Ϊ������Ⱥ���͹���Ա,0Ϊ����������
		bool album;				//�ϴ�Ⱥ���		1Ϊ������Ⱥ���͹���Ա,0Ϊ����������
	}GroupDetail;
	//Ⱥ��ϸ��Ϣ_Ⱥ����Ա
	typedef struct
	{
		Str objQQ;
		Str name;
		bool isGroupOwner;		//�Ƿ���Ⱥ��
		bool isRecvGroupEvent;	//�Ƿ���ռ�Ⱥ��֤��Ϣ	1Ϊ����,0������
	}GroupDetail_Admin;
	//Ⱥ��ϸ��Ϣ_�����б�
	typedef struct
	{
		Str objQQ;
		bool isAdmin;			//�Ƿ���Ⱥ����
		UInteger shutupTime;	//����ʣ������
	}GroupDetail_ShutupList;
}

#ifndef StrToText
template<class _Ty>
typename std::enable_if<std::is_same<_Ty, Str>::value, Text>::type
isStr(_Ty& _Data)
{
	return _Data.c_str();
}
template<class _Ty>
typename std::enable_if<!std::is_same<_Ty, Str>::value, _Ty>::type
isStr(_Ty& _Data)
{
	return _Data;
}
#define StrToText(__Var) isStr((__Var))
#define _TextVaild(__Var) (__Var)  ? (__Var) : ""
#define _PtrVaild(__Var)  (__Var)  ? (__Var) : nullptr
#endif
#endif