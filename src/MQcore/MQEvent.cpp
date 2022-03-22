#include <MQconfig.h>
#include <MQCore/MQHeader.h>
#include <GlobalVar.h>
#include <json/myJson.hpp>
BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        DllHModule = hModule;
        break;
    }

    return TRUE;
}

class Priority
{
public:
    Priority(const uint16_t& priority) : __priority(priority) {}
    void setPriority(const uint16_t& priority) { __priority = priority; }
    uint16_t priority(void)const { return this->__priority; }
protected:
    uint16_t __priority;
};
template<class _FunTy>
class functionCont : public Priority
{
public:
    std::function<void(_FunTy)> _Fun;
    functionCont(const std::function<void(_FunTy)>& _fun, const uint16_t& priortiy = 30000) : _Fun(_fun), Priority(priortiy)
    {}
};
bool operator<(const Priority& a, const Priority& b)
{
    return a.priority() < b.priority();
}
template<class _FunContTy, class _ArgTy>
inline void CallAllFun(const _FunContTy& _FunCont, _ArgTy const& _Args)
{
    if (!EventContInit || _FunCont.empty())return;
    for (const auto& _Fun : _FunCont)
    {
        if (!_Args.eventContinue())break;
        if (_Fun._Fun)_Fun._Fun(_Args);
    }
}
#define __MQEVENT(__Event, __EventData)                                                         \
        std::set<functionCont<__EventData>>& __Event##CallbackCont(void)                        \
        {                                                                                       \
            static std::set<functionCont<__EventData>> __Event##_Callback;                      \
            return __Event##_Callback;                                                          \
        }                                                                                       \
        void clr_##__Event(void){__Event##CallbackCont().clear();}                              \
		void reg_##__Event(const std::function<void(__EventData)>& _Callback, const uint16_t& priority)\
        {__Event##CallbackCont().insert({_Callback, priority});}

////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
namespace MQ::Event
{
    __MQEVENT(Setting, SettingEvent const&)
    __MQEVENT(End, EndEvent const&)
    __MQEVENT(Event, NormalEvent const&)
    __MQEVENT(Message, MessageEvent const&)
}
using namespace MQ;
/*
* 插件信息
*/
EVENT(Text, MQ_Info, 0)(void)
{
#ifdef USE_JSONCPP
    MQInfoJson["name"] = PluginId;
    MQInfoJson["author"] = PluginAuthor;
    MQInfoJson["description"] = PluginDesc;
    MQInfoJson["version"] = PluginVer;
    MQInfoJson["skey"] = PluginSkey;
    MQInfoJson["sdk"] = PluginSdk;
    MQInfoStr = MQInfoJson.toStyledString();
    return StrToText(MQInfoStr);
#else
    return "";
#endif
}
/*
* 右键点击插件（如果未设置窗口可删除此函数）
*/
EVENT(void, MQ_Set, 0)(void)
{
    Event::SettingEvent _event;
    CallAllFun(Event::SettingCallbackCont(), _event);
}
/*
* 当插件被卸载时将会调用
* 插件销毁，需要在此子程序下结束线程和关闭组件释放内存资源，否则可能引起程序异常(如果未加载任何对象内存资源可以删掉此函数)
*/
EVENT(Enum::EventRet, MQ_End, 0)(void)
{
    Event::EndEvent _event;
    CallAllFun(Event::EndCallbackCont(), _event);
    MQExceptionWrapper(__UnInit)();
    return _event.operation;
}


EVENT(Enum::EventRet, MQ_Message, 24)(Text 框架QQ, Integer 消息类型, Text rawText, Text cookies, Text sessionKey, Text clientKey)
{
    Event::MessageEvent _event(_TextVaild(框架QQ), (消息类型), _TextVaild(rawText), _TextVaild(cookies), _TextVaild(sessionKey), _TextVaild(clientKey));
    CallAllFun(Event::MessageCallbackCont(), _event);
    return _event.operation;
}
/*
* 框架QQ     : 机器人QQ,多Q版用于判定哪个QQ接收到该消息
* 消息类型 : 消息类型,常见消息类型: -1,未定义事件 1,好友信息 2,群信息 3,讨论组信息 4,群临时会话 5,讨论组临时会话 6,在线临时会话
* 消息子类型 : 事件子类型,此参数在不同消息类型下,有不同的定义
* 消息来源  : 消息来源,如:群号、讨论组ID、临时会话QQ、好友QQ等
* 触发对象_主动  : 触发者QQ
* 触发对象_被动 : 被操作QQ
* 消息       : 消息内容
* 消息序号    : 消息序号
* 消息ID     : 消息ID
* rawMAPIText   : 此参数用于插件加载拒绝理由
*/
EVENT(Enum::EventRet, MQ_Event, 44)(Text 框架QQ, Integer 消息类型, Integer 消息子类型, Text 消息来源, Text 触发对象_主动, Text 触发对象_被动,
    Text 消息, Text 消息序号, Text 消息ID, Text 原始信息, char* 信息回传文本指针)
{
    MQEventCheck(消息类型, Enum::MQEventEnum::消息类型_本插件载入)
    {
        p.push([](int) {MQExceptionWrapper(__Init)(); });
    }
    auto InitTime = clock();
    while (!APIInitSuccess)
    {
        OutTime(3)
        {
            MQExceptionCode(exception::MQException::MQExceptionEnum::MQInitOutTime, "");
            return Enum::EventRet::事件处理_拒绝;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    MQEventCheck(消息类型, Enum::MQEventEnum::消息类型_插件被启用)
    {
        MQExceptionCode(exception::MQException::MQExceptionEnum::MQOK, "插件启用成功！");
    }
    MQEventCheck(消息类型, Enum::MQEventEnum::消息类型_插件被禁用)
    {
        MQExceptionCode(exception::MQException::MQExceptionEnum::MQOK, "插件正在禁用！");
    }
    MQEventCheck(消息类型, Enum::MQEventEnum::消息类型_本插件载入)
    {
        return Enum::EventRet::事件处理_同意;
    }
    MQEventCheck(消息类型, Enum::MQEventEnum::消息类型_插件被启用)
    {
        return Enum::EventRet::事件处理_同意;
    }
    Event::NormalEvent _event(_TextVaild(框架QQ), 消息类型, 消息子类型, _TextVaild(消息来源), _TextVaild(触发对象_主动), _TextVaild(触发对象_被动), _TextVaild(消息),
        _TextVaild(消息序号), _TextVaild(消息ID), _TextVaild(原始信息), _PtrVaild(信息回传文本指针));
    CallAllFun(Event::EventCallbackCont(), _event);
    return _event.operation;
}


/*
* 插件初始化函数
*/
void CallingConvention __Init()
{
    if (!PluginEnable)
    {
        MQHModule = LoadLibraryA(APIDLLNAME);
        if (MQHModule)
        {
            initFuncs(MQHModule);
            APIInitSuccess = true;
            MQExceptionCode(exception::MQException::MQExceptionEnum::MQOK, "插件载入成功！");
            Api::FrameAPI::OutPut("插件Api初始化完毕...");
            init();
            PluginEnable = true;
        }
        else
        {
            throw(exception::MQException(exception::MQException::MQExceptionEnum::MQDllInitFailed));
        }
    }
}
/*
* 插件释放函数
*/
void CallingConvention __UnInit()
{
    if (PluginEnable)
    {
        Api::FrameAPI::OutPut("即将卸载插件...");
        if (MQHModule != nullptr)
        {
            FreeLibrary(MQHModule);
            MQHModule = nullptr;
        }
        p.stop();
        MQExceptionCode(exception::MQException::MQExceptionEnum::MQOK, "插件正在卸载！");
        PluginEnable = false;
    }
}

#undef __MQEVENT