#pragma once
#ifndef __MQLOGGER_H__
#define __MQLOGGER_H__
#include "MQType.h"
#include "MQAPI.h"
#include <detail/Logger.hpp>

namespace MQ
{
	namespace Detail
	{
		class MQlogger : public logger::Logger, public singleton<MQlogger>
		{
			void __LOG(const char* _logMsg)final
			{
				Api::FrameAPI::OutPut(_logMsg);
			}
		};
	}
	namespace Logging
	{
#define Logger(__Level) static inline void __Level(Text _msg)\
		{\
			Detail::MQlogger::instance()->__Level(_msg);\
		}
		Logger(debug)
		Logger(info)
		Logger(warning)
		Logger(error)
		Logger(fatal)
#undef Logger
	}
	
}
#endif // !__MQLOGGER_H__
