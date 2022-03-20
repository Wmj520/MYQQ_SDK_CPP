#pragma once
#ifndef __GLOBALVAR_H__
#define __GLOBALVAR_H__
#include <MQconfig.h>
#include <detail/ThreadPool.hpp>
#include <MQcore/MQType.h>

extern std::atomic<bool> APIInitSuccess;
extern std::atomic<bool> PluginEnable;
extern std::atomic<bool> EventContInit;
extern ThreadPool::TPool p;
extern HMODULE MQHModule;
extern HMODULE DllHModule;

#ifdef USE_TIMER
#include <Timer.hpp>
extern Timer::Looper::IOEventLoop Looper;
extern std::atomic<bool> LooperInit;
#endif // USE_TIMER

#ifdef USE_JSONCPP
#include <json/json.h>
extern Str MQInfoStr;
extern Json::Value MQInfoJson;
#endif
#endif // !__GLOBALVAR_H__
