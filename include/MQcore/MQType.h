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
		Str publisher; //发布者
		Str title;		//标题
		Str content;	//内容
		bool isTop;		//是否置顶
		Str fid;		//
		Str timeTamp;	//发布时间戳
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
		Str groupId;					//群号
		Str uin;						//QQ号
		Str nick;						//昵称
		ULLInteger join_time;			//入群时间 10位时间戳
		ULLInteger last_speak_time;		//最后发言时间 10位时间戳
		Str card;						//群昵称
		Integer point;					//活跃积分
		Integer level;					//群聊等级
		Integer role;					//管理权限 0群主 1管理员 2普通成员
	}groupMemberInfoV1;
	typedef struct
	{
		Str uin;						//QQ号
		Str qage;						//Q龄
		Str card;						//群昵称
		ULLInteger join_time;			//入群时间 10位时间戳
		ULLInteger last_speak_time;		//最后发言时间 10位时间戳
		Str g;							//性别 0男 1女 -1未知
		Integer point;					//活跃积分
		Integer level;					//群聊等级
		Integer role;					//管理权限 0群主 1管理员 2普通成员
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
	//余额信息
	typedef struct
	{
		Str name;
		Str idCard;	//身份证
		Str balance;	//余额
	}BalanceInfo;
	//等级信息
	typedef struct
	{
		Str objQQ;
		Str actDay;		//活跃天数
		Str remainActDay;	//剩余活跃天数
		Str vip;			//会员
	}LevelInfo;
	//群礼物
	typedef struct
	{
		Str giftId;		//群礼物ID
		Str giftName;		//群礼物名称
		Integer giftNum;	//群礼物数量
	}GroupGift;
	//照片墙
	typedef struct
	{
		Str filekey;
		Str uploadTime;	//上传时间戳,10位
		Str pic_url_640;
		Str pic_url_160;
		Str pic_url_100;
		Str pic_url_0;
	}PicWaller;
	//群详细信息
	typedef struct
	{
		bool forbid_chat;		//允许发起临时会话	1为关闭,0为开启
		bool forbid_discuss;	//允许发起新的群聊	1为关闭,0为开启
		bool invite_friend;		//允许邀请好友入群	0为不允许,1为允许
		bool search;			//允许被搜索		1为关闭,0为开启
		bool me_shutup;			//我是否被禁言		1为关闭,0为开启
		Integer me_shutupTime;	//禁言剩余秒数		me_shutup不为0时为剩余秒数
		bool all_shutup;		//全群禁言			0为关闭,否则为全群禁言
		bool file;				//上传群文件		1为仅允许群主和管理员,0为允许所有人
		bool album;				//上传群相册		1为仅允许群主和管理员,0为允许所有人
	}GroupDetail;
	//群详细信息_群管理员
	typedef struct
	{
		Str objQQ;
		Str name;
		bool isGroupOwner;		//是否是群主
		bool isRecvGroupEvent;	//是否接收加群验证消息	1为接收,0不接收
	}GroupDetail_Admin;
	//群详细信息_禁言列表
	typedef struct
	{
		Str objQQ;
		bool isAdmin;			//是否是群管理
		UInteger shutupTime;	//禁言剩余秒数
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