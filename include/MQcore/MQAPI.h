#pragma once
#ifndef __MQAPI_DEFINE__
#define __MQAPI_DEFINE__
///////////////////////
///////////////////////
#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <vector>
#include <functional>
#include <GlobalVar.h>
#include "MQType.h"
#include "MQException.h"

namespace MQ::Detail
{
	extern std::vector<std::function<void(HMODULE)>> apiFuncInitializers;
	static bool addFuncInit(const std::function<void(HMODULE)>& initializer) {
		apiFuncInitializers.push_back(initializer);
		return true;
	}
#define MQAPI(Name, ReturnType, ...) using Name##_FUNC = std::function<ReturnType (__stdcall)(__VA_ARGS__)>; \
	extern Name##_FUNC _##Name; \
	template <typename... Args> \
	ReturnType Name (Args&&... args) \
	{ \
		return p.push([&args...](int iThread){ return _##Name(std::forward<Args>(args)...); }).get(); \
	} 
#include <MQCore/MyQQAPI.inc>
#undef MQAPI
}
static void initFuncs(const HMODULE& hModule)
{
	for (const auto& initializer : MQ::Detail::apiFuncInitializers) {
		initializer(hModule);
	}
	MQ::Detail::apiFuncInitializers.clear();
}
namespace MQ::文本代码
{
	constexpr auto __str_replace_once = [](Str& str, const Str& replace) {
		str.replace(str.find_first_of("%s"), 2, replace);
	};
	constexpr Text _MQCodeStr[] =
	{
		"[name]", "[qq]","[GName]", "[GNum]","[RName]", "[Rqq]", "[\\n]", "[TimePer]","[Time]", "[时间戳]", "[r]","r[%s, %s]","[next]","[@%s]",
		"[@all]", "[Face%s.gif]", "[newFace, name=%s,Id=%s]", "[emoji=%s]", "[Face]", "[pic=%s]", "[FlashPic=%s]", "[Voi=%s]",
		"[Reply,MsgID=%s, MsgContent=%s,SendQQ=%s,Time=%s][@%s]"
	};
	inline Str 对象昵称(void) { return _MQCodeStr[0]; }
	inline Str 对象QQ(void) { return _MQCodeStr[1]; }
	inline Str 群名(void) { return _MQCodeStr[2]; }
	inline Str 群号(void) { return _MQCodeStr[3]; }
	inline Str 机器人昵称(void) { return _MQCodeStr[4]; }
	inline Str 机器人QQ(void) { return _MQCodeStr[5]; }
	inline Str 换行符(void) { return _MQCodeStr[6]; }
	inline Str 时间段(void) { return _MQCodeStr[7]; }
	inline Str 时间(void) { return _MQCodeStr[8]; }
	inline Str 时间戳(void) { return _MQCodeStr[9]; }
	inline Str 随机数(void) { return _MQCodeStr[10]; }
	inline Str 自定义随机数(uint16_t const& _Min, uint16_t const& _Max)
	{
		if (_Min > _Max)return "";
		Str _str(_MQCodeStr[11]);
		__str_replace_once(_str, std::to_string(_Min));
		__str_replace_once(_str, std::to_string(_Max));
		return _str;
	}
	inline Str 信息分段发送(void) { return _MQCodeStr[12]; }
	inline Str 艾特个人(Str _atQQ)
	{
		if (_atQQ.empty())return "";
		Str _str(_MQCodeStr[13]);
		__str_replace_once(_str, _atQQ);
		return _str;
	}
	inline Str 艾特全体(void) { return _MQCodeStr[14]; }
	inline Str 表情(const uint16_t& _Id)
	{
		Str _str(_MQCodeStr[15]);
		__str_replace_once(_str, std::to_string(_Id));
		return _str;
	}
	inline Str 新黄豆(Str _Name, const uint16_t& _Id)
	{
		Str _str(_MQCodeStr[16]);
		__str_replace_once(_str, _Name);
		__str_replace_once(_str, std::to_string(_Id));
		return _str;
	}
	inline Str 颜表情(const uint16_t& _EmojiCode)
	{
		Str _str(_MQCodeStr[17]);
		__str_replace_once(_str, std::to_string(_EmojiCode));
		return _str;
	}
	inline Str 随机表情(void) { return _MQCodeStr[18]; }
	inline Str 图片发送(Str _PicPath)
	{
		if (_PicPath.empty())return "";
		Str _str(_MQCodeStr[19]);
		__str_replace_once(_str, _PicPath);
		return _str;
	}
	inline Str 闪照(Str GUID)
	{
		if (GUID.empty())return "";
		Str _str(_MQCodeStr[20]);
		__str_replace_once(_str, GUID);
		return _str;
	}
	/*inline Str Voice(Str _Voi)
	{
		if (_Voi.empty())return "";
		char _str[512];
		memset(_str, 0, 512);
		sprintf(_str, _MQCodeStr[21], _Voi.c_str());
		return _str;
	}*/
	inline Str 回复消息(Str _MsgID, Str _MsgContent, Str _SendQQ, Str _Time)
	{
		if (_MsgID.empty() || _MsgContent.empty() || _SendQQ.empty() || _Time.empty())return "";
		Str _str(_MQCodeStr[22]);
		__str_replace_once(_str, _MsgID);
		__str_replace_once(_str, _MsgContent);
		__str_replace_once(_str, _SendQQ);
		__str_replace_once(_str, _Time);
		__str_replace_once(_str, _SendQQ);
		return _str;
	}

}
namespace MQ::Api
{
	namespace MessageAPI
	{
		inline void SendMsg(Str botQQ, Integer msgType, Str groupId, Str objQQ, Str msg)
		{
			return MQ::Detail::SendMsg(StrToText(botQQ), StrToText(msgType), StrToText(groupId), StrToText(objQQ), StrToText(msg));
		}
		inline void SendMsgEx(Str botQQ, Integer anonymous, Integer msgType, Str groupId, Str objQQ, Str msg, Integer bubbleId)
		{
			return MQ::Detail::SendMsgEx(StrToText(botQQ), StrToText(anonymous), StrToText(msgType), StrToText(groupId), StrToText(objQQ), StrToText(msg), StrToText(bubbleId));
		}
		inline void SendLongMsg(Str botQQ, Integer anonymous, Integer msgType, Str groupId, Str objQQ, Str msg, Integer isAnony)
		{
			return MQ::Detail::SendLongMsg(StrToText(botQQ), StrToText(anonymous), StrToText(msgType), StrToText(groupId), StrToText(objQQ), StrToText(msg), StrToText(isAnony));
		}
		inline void SendXml(Str botQQ, Integer anonymous, Integer msgType, Str groupId, Str objQQ, Str msgXML, Integer structType)
		{
			return MQ::Detail::SendXml(StrToText(botQQ), StrToText(anonymous), StrToText(msgType), StrToText(groupId), StrToText(objQQ), StrToText(msgXML), StrToText(structType));
		}
		inline void SendJson(Str botQQ, Integer anonymous, Integer msgType, Str groupId, Str objQQ, Str msgJson)
		{
			return MQ::Detail::SendJson(StrToText(botQQ), StrToText(anonymous), StrToText(msgType), StrToText(groupId), StrToText(objQQ), StrToText(msgJson));
		}
		inline Text WithdrawMsg(Str botQQ, Str groupId, Str objQQ, Str msgId)
		{
			return MQ::Detail::WithdrawMsg(StrToText(botQQ), StrToText(groupId), StrToText(objQQ), StrToText(msgId));
		}
		inline void BeInput(Str botQQ, Str objQQ)
		{
			return MQ::Detail::BeInput(StrToText(botQQ), StrToText(objQQ));
		}
		inline bool SendVoice(Str botQQ, Str objQQ, Str voiceAddr)
		{
			return MQ::Detail::SendVoice(StrToText(botQQ), StrToText(objQQ), StrToText(voiceAddr));
		}
		inline Text SendMail(Str botQQ, Str objQQ, Str voiceAddr)
		{
			return MQ::Detail::SendMail(StrToText(botQQ), StrToText(objQQ), StrToText(voiceAddr));
		}
	}
	namespace GroupAPI
	{
		inline void HandleGroupMyEvent(Str botQQ, Str data)
		{
			return MQ::Detail::HandleGroupMyEvent(StrToText(botQQ), StrToText(data));
		}
		inline Text GetDisGroupList(Str botQQ)
		{
			return MQ::Detail::GetDisGroupList(StrToText(botQQ));
		}
		inline Text GetDisGroupMemberList(Str botQQ, Str disgroupId)
		{
			return MQ::Detail::GetDisGroupMemberList(StrToText(botQQ), StrToText(disgroupId));
		}
		inline Text GetGroupList(Str botQQ)
		{
			return MQ::Detail::GetGroupList(StrToText(botQQ));
		}
		inline Text GetGroupList_A(Str botQQ)
		{
			return MQ::Detail::GetGroupList_A(StrToText(botQQ));
		}
		inline Text GetGroupList_B(Str botQQ)
		{
			return MQ::Detail::GetGroupList_B(StrToText(botQQ));
		}
		inline Text GetGroupMemberList(Str botQQ, Str groupId)
		{
			return MQ::Detail::GetGroupMemberList(StrToText(botQQ), StrToText(groupId));
		}
		inline Text GetGroupMemberList_B(Str botQQ, Str groupId)
		{
			return MQ::Detail::GetGroupMemberList_B(StrToText(botQQ), StrToText(groupId));
		}
		inline Text GetGroupMemberList_C(Str botQQ, Str groupId)
		{
			return MQ::Detail::GetGroupMemberList_C(StrToText(botQQ), StrToText(groupId));
		}
		inline Text GetAdminList(Str botQQ, Str groupId)
		{
			return MQ::Detail::GetAdminList(StrToText(botQQ), StrToText(groupId));
		}
		inline bool JoinGroup(Str botQQ, Str groupId, Str joinReason)
		{
			return MQ::Detail::JoinGroup(StrToText(botQQ), StrToText(groupId), StrToText(joinReason));
		}
		inline void QuitGroup(Str botQQ, Str groupId)
		{
			return MQ::Detail::QuitGroup(StrToText(botQQ), StrToText(groupId));
		}
		inline bool Shutup(Str botQQ, Str groupId, Str objQQ, Str durTime)
		{
			return MQ::Detail::Shutup(StrToText(botQQ), StrToText(groupId), StrToText(objQQ), StrToText(durTime));
		}
		inline bool IsShutup(Str botQQ, Str groupId, Str objQQ)
		{
			return MQ::Detail::IsShutup(StrToText(botQQ), StrToText(groupId), StrToText(objQQ));
		}
		inline bool SetAnon(Str botQQ, Str groupId, bool anonStatus)
		{
			return MQ::Detail::SetAnon(StrToText(botQQ), StrToText(groupId), StrToText(anonStatus));
		}
		inline void SetShieldedGroup(Str botQQ, Str groupId, Integer setType)
		{
			return MQ::Detail::SetShieldedGroup(StrToText(botQQ), StrToText(groupId), StrToText(setType));
		}
		inline Integer SetAdmin(Str botQQ, Str groupId, Str objQQ, Integer setType)
		{
			return MQ::Detail::SetAdmin(StrToText(botQQ), StrToText(groupId), StrToText(objQQ), StrToText(setType));
		}
		inline Text GetGroupMemberNum(Str botQQ, Str groupId)
		{
			return MQ::Detail::GetGroupMemberNum(StrToText(botQQ), StrToText(groupId));
		}
		inline Text GetGroupCard(Str botQQ, Str groupId, Str objQQ)
		{
			return MQ::Detail::GetGroupCard(StrToText(botQQ), StrToText(groupId), StrToText(objQQ));
		}
		inline Text GetGroupAddMode(Str botQQ, Str groupId)
		{
			return MQ::Detail::GetGroupAddMode(StrToText(botQQ), StrToText(groupId));
		}
		inline bool SetGroupCard(Str botQQ, Str groupId, Str objQQ, Str cardName)
		{
			return MQ::Detail::SetGroupCard(StrToText(botQQ), StrToText(groupId), StrToText(objQQ), StrToText(cardName));
		}
		inline void KickGroupMBR(Str botQQ, Str groupId, Str objQQ, bool noJoin)
		{
			return MQ::Detail::KickGroupMBR(StrToText(botQQ), StrToText(groupId), StrToText(objQQ), StrToText(noJoin));
		}
		inline void QuitDisGroup(Str botQQ, Str groupId)
		{
			return MQ::Detail::QuitDisGroup(StrToText(botQQ), StrToText(groupId));
		}
		inline void KickDisGroupMBR(Str botQQ, Str groupId, Str objQQ)
		{
			return MQ::Detail::KickDisGroupMBR(StrToText(botQQ), StrToText(groupId), StrToText(objQQ));
		}
		inline void AdminInviteGroup(Str botQQ, Str groupId, Str objQQ)
		{
			return MQ::Detail::AdminInviteGroup(StrToText(botQQ), StrToText(groupId), StrToText(objQQ));
		}
		inline void NoAdminInviteGroup(Str botQQ, Str groupId, Str objQQ)
		{
			return MQ::Detail::NoAdminInviteGroup(StrToText(botQQ), StrToText(groupId), StrToText(objQQ));
		}
		inline Text GetGroupChatLv(Str botQQ, Str groupId, Str objQQ)
		{
			return MQ::Detail::GetGroupChatLv(StrToText(botQQ), StrToText(groupId), StrToText(objQQ));
		}
		inline Integer GetAnon(Str botQQ, Str groupId)
		{
			return MQ::Detail::GetAnon(StrToText(botQQ), StrToText(groupId));
		}
		inline Integer InviteGroup_other(Str botQQ, Str srcGroupId, Str objGroupId, Str objQQ)
		{
			return MQ::Detail::InviteGroup_other(StrToText(botQQ), StrToText(srcGroupId), StrToText(objGroupId), StrToText(objQQ));
		}
		inline bool ShutupGroup(Str botQQ, Str groupId, bool isShut)
		{
			return MQ::Detail::ShutupGroup(StrToText(botQQ), StrToText(groupId), StrToText(isShut));
		}
		inline Text SetMsgEssence(Str botQQ, Str groupId, Str msgNo, Str msgId)
		{
			return MQ::Detail::SetMsgEssence(StrToText(botQQ), StrToText(groupId), StrToText(msgNo), StrToText(msgId));
		}
		inline void SetDisGroupName(Str botQQ, Str groupId, Str disGroupName)
		{
			return MQ::Detail::SetDisGroupName(StrToText(botQQ), StrToText(groupId), StrToText(disGroupName));
		}
		inline bool UpGroupFile(Str botQQ, Str groupId, Str filePath)
		{
			return MQ::Detail::UpGroupFile(StrToText(botQQ), StrToText(groupId), StrToText(filePath));
		}
		inline Integer SetGroupName(Str botQQ, Str groupId, Str groupName)
		{
			return MQ::Detail::SetGroupName(StrToText(botQQ), StrToText(groupId), StrToText(groupName));
		}
		inline Text GetNoticDetail(Str botQQ, Str groupId, Str noticId)
		{
			return MQ::Detail::GetNoticDetail(StrToText(botQQ), StrToText(groupId), StrToText(noticId));
		}
		inline Text GetGroupMemberInfo(Str botQQ, Str groupId, Str objQQ)
		{
			return MQ::Detail::GetGroupMemberInfo(StrToText(botQQ), StrToText(groupId), StrToText(objQQ));
		}
		inline bool PBGroupNotic(Str botQQ, Str groupId, Str title, Str content)
		{
			return MQ::Detail::PBGroupNotic(StrToText(botQQ), StrToText(groupId), StrToText(title), StrToText(content));
		}
		inline Text PublishVote_A(Str botQQ, Str groupId, Str title, Str option1, Str option2, Str option3, Str deadlineTimeStamp, Str isAnony)
		{
			return MQ::Detail::PublishVote_A(StrToText(botQQ), StrToText(groupId), StrToText(title), StrToText(option1), StrToText(option2), StrToText(option3), StrToText(deadlineTimeStamp), StrToText(isAnony));
		}
		inline Text PublishVote_B(Str botQQ, Str groupId, Str title, Str option1, Str option2, Str option3, Str deadlineTimeStamp, Str isAnony)
		{
			return MQ::Detail::PublishVote_B(StrToText(botQQ), StrToText(groupId), StrToText(title), StrToText(option1), StrToText(option2), StrToText(option3), StrToText(deadlineTimeStamp), StrToText(isAnony));
		}

		inline void HandleGroupEvent(Str botQQ, Str data, Integer handleType, Str complement, Integer neverAccept)
		{
			return MQ::Detail::HandleGroupEvent(StrToText(botQQ), StrToText(data), StrToText(handleType), StrToText(complement), StrToText(neverAccept));
		}
		inline Text CreateDisGroup(Str botQQ, Str objQQ)
		{
			return MQ::Detail::CreateDisGroup(StrToText(botQQ), StrToText(objQQ));
		}
		inline Text CreateGroup_A(Str botQQ, Str groupName, Str groupType)
		{
			return MQ::Detail::CreateGroup_A(StrToText(botQQ), StrToText(groupName), StrToText(groupType));
		}
		inline Text InviteDisGroup(Str botQQ, Str groupId, Str objQQ)
		{
			return MQ::Detail::InviteDisGroup(StrToText(botQQ), StrToText(groupId), StrToText(objQQ));
		}
		inline Text GetGroupName(Str botQQ, Str groupId)
		{
			return MQ::Detail::GetGroupName(StrToText(botQQ), StrToText(groupId));
		}
		inline Text SearchGroup(Str botQQ, Str keyword, Integer page)
		{
			return MQ::Detail::SearchGroup(StrToText(botQQ), StrToText(keyword), StrToText(page));
		}
		inline Text CreateGroupPay(Str botQQ, Str groupId, Str title, Integer type, Str objQQ, Str payEveryone)
		{
			return MQ::Detail::CreateGroupPay(StrToText(botQQ), StrToText(groupId), StrToText(title), StrToText(type), StrToText(objQQ), StrToText(payEveryone));
		}
		inline Text GetGroupPayDetail(Str botQQ, Str groupPayNo)
		{
			return MQ::Detail::GetGroupPayDetail(StrToText(botQQ), StrToText(groupPayNo));
		}
		inline Integer GroupPayIsOk(Str payDetailJson, Str objQQ)
		{
			return MQ::Detail::GroupPayIsOk(StrToText(payDetailJson), StrToText(objQQ));
		}
		inline Integer SendGroupPayMsg(Str botQQ, Str groupPayNo)
		{
			return MQ::Detail::SendGroupPayMsg(StrToText(botQQ), StrToText(groupPayNo));
		}
		inline Text JoinGroupEx(Str botQQ, Str groupId, Str reason, Str port, Str channel)
		{
			return MQ::Detail::JoinGroupEx(StrToText(botQQ), StrToText(groupId), StrToText(reason), StrToText(port), StrToText(channel));
		}
		inline Text GetJoinGroupMsg(Str botQQ, Str groupMsgId)
		{
			return MQ::Detail::GetJoinGroupMsg(StrToText(botQQ), StrToText(groupMsgId));
		}
		inline Text CheckJoinGroupMsg(Str botQQ, Str groupMsgId)
		{
			return MQ::Detail::CheckJoinGroupMsg(StrToText(botQQ), StrToText(groupMsgId));
		}
		inline bool SetGroupTempSession(Str botQQ, Str groupId, Str turn)
		{
			return MQ::Detail::SetGroupTempSession(StrToText(botQQ), StrToText(groupId), StrToText(turn));
		}
		inline bool SetGroupLaunchNew(Str botQQ, Str groupId, Str turn)
		{
			return MQ::Detail::SetGroupLaunchNew(StrToText(botQQ), StrToText(groupId), StrToText(turn));
		}
		inline bool GetGroupTempSession(Str botQQ, Str groupId)
		{
			return MQ::Detail::GetGroupTempSession(StrToText(botQQ), StrToText(groupId));
		}
		inline bool GetGroupLaunchNew(Str botQQ, Str groupId)
		{
			return MQ::Detail::GetGroupLaunchNew(StrToText(botQQ), StrToText(groupId));
		}
		inline bool InviteGroup_otherEx(Str botQQ, Str groupId, Str objQQandFromGroup)
		{
			return MQ::Detail::InviteGroup_otherEx(StrToText(botQQ), StrToText(groupId), StrToText(objQQandFromGroup));
		}
		inline bool GiveGift(Str botQQ, Str groupId, Str objQQ, Str giftId, Integer giftNum)
		{
			return MQ::Detail::GiveGift(StrToText(botQQ), StrToText(groupId), StrToText(objQQ), StrToText(giftId), StrToText(giftNum));
		}
		inline Text CheckGift(Str botQQ)
		{
			return MQ::Detail::CheckGift(StrToText(botQQ));
		}
		inline Text TakeGift(Str botQQ)
		{
			return MQ::Detail::TakeGift(StrToText(botQQ));
		}
		inline bool SetGroupVerify(Str botQQ, Str groupId, Integer verifyType, Str problemCorrectly, Str answer)
		{
			return MQ::Detail::SetGroupVerify(StrToText(botQQ), StrToText(groupId), StrToText(verifyType), StrToText(problemCorrectly), StrToText(answer));
		}
		inline Text DelMsgEssence(Str botQQ, Str groupId, Str msgNo, Str msgId)
		{
			return MQ::Detail::DelMsgEssence(StrToText(botQQ), StrToText(groupId), StrToText(msgNo), StrToText(msgId));
		}
		inline Text GetGroupFileList(Str botQQ, Str groupId, Str fileId)
		{
			return MQ::Detail::GetGroupFileList(StrToText(botQQ), StrToText(groupId), StrToText(fileId));
		}
		inline Text GetGroupFileUrl(Str botQQ, Str groupId, Str fileId, Str size, Str name)
		{
			return MQ::Detail::GetGroupFileUrl(StrToText(botQQ), StrToText(groupId), StrToText(fileId), StrToText(size), StrToText(name));
		}
		inline bool UpGroupTempFile(Str botQQ, Str fromGroup, Str objQQ, Str filePath)
		{
			return MQ::Detail::UpGroupTempFile(StrToText(botQQ), StrToText(fromGroup), StrToText(objQQ), StrToText(filePath));
		}
		inline bool FileGroupToGroup(Str botQQ, Str fromGroup, Str objGroup, Str fileId)
		{
			return MQ::Detail::FileGroupToGroup(StrToText(botQQ), StrToText(fromGroup), StrToText(objGroup), StrToText(fileId));
		}
		inline bool FileGroupToFriend(Str botQQ, Str fromGroup, Str objQQ, Str fileId)
		{
			return MQ::Detail::FileGroupToFriend(StrToText(botQQ), StrToText(fromGroup), StrToText(objQQ), StrToText(fileId));
		}
	};
	namespace FriendAPI
	{
		inline Text GetFriendList(Str botQQ)
		{
			return MQ::Detail::GetFriendList(StrToText(botQQ));
		}
		inline Text GetFriendList_B(Str botQQ)
		{
			return MQ::Detail::GetFriendList_B(StrToText(botQQ));
		}
		inline bool AddFriend(Str botQQ, Str objQQ, Str joinReason)
		{
			return MQ::Detail::AddFriend(StrToText(botQQ), StrToText(objQQ), StrToText(joinReason));
		}
		inline void AddBkList(Str botQQ, Str objQQ)
		{
			return MQ::Detail::AddBkList(StrToText(botQQ), StrToText(objQQ));
		}
		inline void DelBkList(Str botQQ, Str objQQ)
		{
			return MQ::Detail::DelBkList(StrToText(botQQ), StrToText(objQQ));
		}
		inline bool DelFriend(Str botQQ, Str objQQ)
		{
			return MQ::Detail::DelFriend(StrToText(botQQ), StrToText(objQQ));
		}
		inline Text GetObjInfo(Str botQQ, Str objQQ)
		{
			return MQ::Detail::GetObjInfo(StrToText(botQQ), StrToText(objQQ));
		}
		inline bool ShakeWindow(Str botQQ, Str objQQ)
		{
			return MQ::Detail::ShakeWindow(StrToText(botQQ), StrToText(objQQ));
		}
		inline Text GetQQAddMode(Str botQQ, Str objQQ)
		{
			return MQ::Detail::GetQQAddMode(StrToText(botQQ), StrToText(objQQ));
		}
		inline Integer GetOnlineState(Str botQQ, Str objQQ)
		{
			return MQ::Detail::GetOnlineState(StrToText(botQQ), StrToText(objQQ));
		}
		inline bool IfFriend(Str botQQ, Str objQQ)
		{
			return MQ::Detail::IfFriend(StrToText(botQQ), StrToText(objQQ));
		}
		inline Text UpVote(Str botQQ, Str objQQ)
		{
			return MQ::Detail::UpVote(StrToText(botQQ), StrToText(objQQ));
		}
		inline Text UpVoteEx(Str botQQ, Str objQQ)
		{
			return MQ::Detail::UpVoteEx(StrToText(botQQ), StrToText(objQQ));
		}
		inline Integer GetExpertDays(Str botQQ, Str objQQ)
		{
			return MQ::Detail::GetExpertDays(StrToText(botQQ), StrToText(objQQ));
		}
		inline Text GetQQLevelInfo(Str botQQ, Str objQQ)
		{
			return MQ::Detail::GetQQLevelInfo(StrToText(botQQ), StrToText(objQQ));
		}
		inline Text GetFriendsRemark(Str botQQ, Str objQQ)
		{
			return MQ::Detail::GetFriendsRemark(StrToText(botQQ), StrToText(objQQ));
		}
		inline void SetFriendsRemark(Str botQQ, Str objQQ, Str setRemark)
		{
			return MQ::Detail::SetFriendsRemark(StrToText(botQQ), StrToText(objQQ), StrToText(setRemark));
		}

		inline void HandleFriendEvent(Str botQQ, Str objQQ, Integer handleType, Str complement)
		{
			return MQ::Detail::HandleFriendEvent(StrToText(botQQ), StrToText(objQQ), StrToText(handleType), StrToText(complement));
		}
		inline Text UpFriendFile(Str botQQ, Str objQQ, Str filePath)
		{
			return MQ::Detail::UpFriendFile(StrToText(botQQ), StrToText(objQQ), StrToText(filePath));
		}
		inline bool SetFriendVerifyEx(Str botQQ, Integer verifyType, Str problemCorrectly, Str answer, Str problemNeed1, Str problemNeed2, Str problemNeed3)
		{
			return MQ::Detail::SetFriendVerifyEx(StrToText(botQQ), StrToText(verifyType), StrToText(problemCorrectly), StrToText(answer), StrToText(problemNeed1), StrToText(problemNeed2), StrToText(problemNeed3));
		}
		inline bool SetSpecialCare(Str botQQ, Str objQQ)
		{
			return MQ::Detail::SetSpecialCare(StrToText(botQQ), StrToText(objQQ));
		}
		inline bool DelSpecialCare(Str botQQ, Str objQQ)
		{
			return MQ::Detail::DelSpecialCare(StrToText(botQQ), StrToText(objQQ));
		}
	};
	namespace KeyAPI
	{
		inline void GetDomainCookies(Str botQQ, Str pt_aid, Str aid, Str jumpAddr)
		{
			return MQ::Detail::GetDomainCookies(StrToText(botQQ), StrToText(pt_aid), StrToText(aid), StrToText(jumpAddr));
		}
		inline Text GetBlogPsKey(Str botQQ)
		{
			return MQ::Detail::GetBlogPsKey(StrToText(botQQ));
		}
		inline Text GetQQInfoPsKey(Str botQQ)
		{
			return MQ::Detail::GetQQInfoPsKey(StrToText(botQQ));
		}
		inline Text GetQQVIPPsKey(Str botQQ)
		{
			return MQ::Detail::GetQQVIPPsKey(StrToText(botQQ));
		}
		inline Text GetZonePsKey(Str botQQ)
		{
			return MQ::Detail::GetZonePsKey(StrToText(botQQ));
		}
		inline Text GetGroupPsKey(Str botQQ)
		{
			return MQ::Detail::GetGroupPsKey(StrToText(botQQ));
		}
		inline Text GetClassRoomPsKey(Str botQQ)
		{
			return MQ::Detail::GetClassRoomPsKey(StrToText(botQQ));
		}
		inline Text GetTenPayPsKey(Str botQQ)
		{
			return MQ::Detail::GetTenPayPsKey(StrToText(botQQ));
		}
		inline Text GetJuBaoPsKey(Str botQQ)
		{
			return MQ::Detail::GetJuBaoPsKey(StrToText(botQQ));
		}
		inline Text GetBkn(Str botQQ)
		{
			return MQ::Detail::GetBkn(StrToText(botQQ));
		}
		inline Text GetBkn32(Str botQQ)
		{
			return MQ::Detail::GetBkn32(StrToText(botQQ));
		}
		inline Text GetLongLdw(Str botQQ)
		{
			return MQ::Detail::GetLongLdw(StrToText(botQQ));
		}
		inline Text GetClientkey(Str botQQ)
		{
			return MQ::Detail::GetClientkey(StrToText(botQQ));
		}
		inline Text GetLongClientkey(Str botQQ)
		{
			return MQ::Detail::GetLongClientkey(StrToText(botQQ));
		}
		inline Text SessionKey(Str botQQ)
		{
			return MQ::Detail::SessionKey(StrToText(botQQ));
		}
	};
	namespace FrameAPI
	{
		inline void OutPut(Str content)
		{
			return MQ::Detail::OutPut(StrToText(content));
		}
		inline Text GetVer(void)
		{
			return MQ::Detail::GetVer();
		}
		inline bool IsEnable(void)
		{
			return MQ::Detail::IsEnable();
		}
		inline void DisabledPlugin(void)
		{
			return MQ::Detail::DisabledPlugin();
		}
		inline Text GetQQList(void)
		{
			return MQ::Detail::GetQQList();
		}
		inline Text GetOnlineQQlist(void)
		{
			return MQ::Detail::GetOnlineQQlist();
		}
		inline Text GetOffLineList(void)
		{
			return MQ::Detail::GetOffLineList();
		}
		inline bool AddQQ(Str botQQ, Str pwdQQ, Str Token, Str Agent)
		{
			return MQ::Detail::AddQQ(StrToText(botQQ), StrToText(pwdQQ), StrToText(Token), StrToText(Agent));
		}
		inline void DelQQ(Str botQQ)
		{
			return MQ::Detail::DelQQ(StrToText(botQQ));
		}
		inline void Login(Str botQQ)
		{
			return MQ::Detail::Login(StrToText(botQQ));
		}
		inline void Logout(Str botQQ)
		{
			return MQ::Detail::Logout(StrToText(botQQ));
		}
		inline Text CreatQrCodeInfo(void)
		{
			return MQ::Detail::CreatQrCodeInfo();
		}
		inline Integer GetQrCodeStatus(Str qrId)
		{
			return MQ::Detail::GetQrCodeStatus(StrToText(qrId));
		}
		inline Text CloseQrCode(Str qrId)
		{
			return MQ::Detail::CloseQrCode(StrToText(qrId));
		}
		inline Text GetQrCodePath(Str qrFile)
		{
			return MQ::Detail::GetQrCodePath(StrToText(qrFile));
		}
		inline Text GetQrQQNumber(Str qrFile)
		{
			return MQ::Detail::GetQrQQNumber(StrToText(qrFile));
		}
		inline Text GetPluginList(void)
		{
			return MQ::Detail::GetPluginList();
		}
		inline Text GetShieldedState(Str botQQ)
		{
			return MQ::Detail::GetShieldedState(StrToText(botQQ));
		}
		inline Text OutPutEx(Str content, Str fontColor, Str bgColor)
		{
			return MQ::Detail::OutPutEx(StrToText(content), StrToText(fontColor), StrToText(bgColor));
		}
	};
	namespace QQAnotherAPI
	{

	};
	namespace HBAPI
	{
		inline Text QueryBalance(Str botQQ, Str payPwd)
		{
			return MQ::Detail::QueryBalance(StrToText(botQQ), StrToText(payPwd));
		}
		inline Text TransferAccounts(Str botQQ, Str payPwd, Str objQQ, Str objName, Str amount, Str comment, bool isFriend)
		{
			return MQ::Detail::TransferAccounts(StrToText(botQQ), StrToText(payPwd), StrToText(objQQ), StrToText(objName), StrToText(amount), StrToText(comment), StrToText(isFriend));
		}
		inline Text RedPack_KeyWord(Str botQQ, Str payPwd, Str objId, Str num, Str amount, Str keyword, Integer type)
		{
			return MQ::Detail::RedPack_KeyWord(StrToText(botQQ), StrToText(payPwd), StrToText(objId), StrToText(num), StrToText(amount), StrToText(keyword), StrToText(type));
		}
		inline Text RedPack_Luck(Str botQQ, Str payPwd, Str objId, Str num, Str amount, Str greeting)
		{
			return MQ::Detail::RedPack_Luck(StrToText(botQQ), StrToText(payPwd), StrToText(objId), StrToText(num), StrToText(amount), StrToText(greeting));
		}
		inline Text RedPack_Ordinary(Str botQQ, Str payPwd, Str objId, Str num, Str amount, Str greeting, Integer type, Str disGroupId)
		{
			return MQ::Detail::RedPack_Ordinary(StrToText(botQQ), StrToText(payPwd), StrToText(objId), StrToText(num), StrToText(amount), StrToText(greeting), StrToText(type), StrToText(disGroupId));
		}
		inline Text RedPack_Voice(Str botQQ, Str payPwd, Str objId, Str num, Str amount, Str greeting, Integer type)
		{
			return MQ::Detail::RedPack_Voice(StrToText(botQQ), StrToText(payPwd), StrToText(objId), StrToText(num), StrToText(amount), StrToText(greeting), StrToText(type));
		}
		inline Text RedPack_Exclusive(Str botQQ, Str payPwd, Str groupId, Str objQQ, Str num, Str amount, Str greeting)
		{
			return MQ::Detail::RedPack_Exclusive(StrToText(botQQ), StrToText(payPwd), StrToText(groupId), StrToText(objQQ), StrToText(num), StrToText(amount), StrToText(greeting));
		}
		inline Text RedPack_Astroke(Str botQQ, Str payPwd, Str groupId, Str num, Str amount, Str level)
		{
			return MQ::Detail::RedPack_Astroke(StrToText(botQQ), StrToText(payPwd), StrToText(groupId), StrToText(num), StrToText(amount), StrToText(level));
		}
		inline Text RedPack_Game(Str botQQ, Str payPwd, Str objId, Str num, Str amount, Str greeting, Integer type, Str rank)
		{
			return MQ::Detail::RedPack_Game(StrToText(botQQ), StrToText(payPwd), StrToText(objId), StrToText(num), StrToText(amount), StrToText(greeting), StrToText(type), StrToText(rank));
		}
		inline Text HB_Detial(Str botQQ, Str groupId, Str mqMsg)
		{
			return MQ::Detail::HB_Detial(StrToText(botQQ), StrToText(groupId), StrToText(mqMsg));
		}
		inline Text HB_DetialEx(Str botQQ, Str groupId, Str mqMsg, Integer page)
		{
			return MQ::Detail::HB_DetialEx(StrToText(botQQ), StrToText(groupId), StrToText(mqMsg), StrToText(page));
		}
	}


	/*
	* MQAPI\((.*?), (.*?), (.*)\)
	* inline $2 $1($3)\r\n{\r\nreturn MQ::Detail::$1($3);\r\n}
	*/

}
#endif // !__MQAPI_DEFINE__
