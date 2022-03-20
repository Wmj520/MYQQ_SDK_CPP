#include <GlobalVar.h>

ThreadPool::TPool p(ThreadPoolSize);
Text LogFile = "../log/log.ini";
HMODULE MQHModule = nullptr;
HMODULE DllHModule = nullptr;
std::atomic<bool> APIInitSuccess = false;
std::atomic<bool> PluginEnable = false;
std::atomic<bool> EventContInit = false;
#ifdef USE_JSONCPP
Json::Value MQInfoJson;
Str MQInfoStr = "";
#endif
#ifdef USE_TIMER
Timer::Looper::IOEventLoop Looper;
std::atomic<bool> LooperInit = false;
#endif // USE_TIMER