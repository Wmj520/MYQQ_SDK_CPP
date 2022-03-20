#pragma once
#ifndef __MQ_HEADER__
#define __MQ_HEADER__
#include <MQconfig.h>
#define MYQQ
#if (!defined (MYQQ)) && (!defined MYQQA)
#error ����"MQconfig.H"ȷ����ʹ�õ�MYQQ�汾��
#elif (defined MYQQ) && (defined MYQQA)
#error ��ѡ������һ���汾��
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
#error ��ȷ��������֡�PluginId����
#endif

#include "MQType.h"
#include "MQAPI.h"
#include "MQEvent.h"
#include "MQException.h"
#include "MQLogging.h"
#endif // !__MQ_HEADER__
