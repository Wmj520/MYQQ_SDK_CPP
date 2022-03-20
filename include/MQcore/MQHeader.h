#pragma once
#ifndef __MQ_HEADER__
#define __MQ_HEADER__
#include <MQconfig.h>
#define MYQQ
#if (!defined (MYQQ)) && (!defined MYQQA)
#error 请在"MQconfig.H"确定你使用的MYQQ版本！
#elif (defined MYQQ) && (defined MYQQA)
#error 请选择其中一个版本！
#endif
#if defined MYQQ
#define APIDLLNAME "MyQQApi.dll"
#elif defined MYQQA
#define APIDLLNAME "MyQQAApi.dll"
#endif

#if !defined USE_CMAKE
#define PluginId "MYQQ_SDK_CPP"
#define PluginAuthor "you"
#define PluginDesc "plugin information"
#define PluginVer "1.0.0"
#define PluginSkey "SDG5D4Ys89h7DJ849d"
#define PluginSdk "S1"
#endif

#if !defined PluginId 
#error 请确定插件名字‘PluginId’！
#endif

#include "MQType.h"
#include "MQAPI.h"
#include "MQEvent.h"
#include "MQException.h"
#include "MQLogging.h"
#endif // !__MQ_HEADER__
