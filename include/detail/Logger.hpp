#pragma once
#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <functional>
#include <detail/singleton.h>
#define TestPoint(_Num) info("≤‚ ‘µ„" # _Num)

namespace logger
{
	enum LogLevel : uint8_t
	{
		Debug = 0, Info, Warning, Error, Fatal
	};
	const static  char* __LogHead[] = {
		"[Debug]:","[Info]:","[Warning]:","[Error]:","[Fatal]:"

	};
	class Logger
	{
	public:
		typedef std::function<void(const char*)> logFunc;
		Logger() :__Log(nullptr) { setLog(std::bind(&Logger::__LOG, this, std::placeholders::_1)); }
		virtual ~Logger() { __Log = nullptr; }
		void debug(const char* _msg)
		{
			write(LogLevel::Debug, _msg);
		}
		void info(const char* _msg)
		{
			write(LogLevel::Info, _msg);
		}
		void warning(const char* _msg)
		{
			write(LogLevel::Warning, _msg);
		}
		void error(const char* _msg)
		{
			write(LogLevel::Error, _msg);
		}
		void fatal(const char* _msg)
		{
			write(LogLevel::Fatal, _msg);
		}
		void setLog(logFunc&& _log)
		{
			__Log = _log;
		}
	protected:
		void write(LogLevel const& _level, const char* _logMsg)
		{
			uint16_t _len = (uint16_t)__min(strlen(_logMsg) + 10, 1024);
			char* _log = new char[_len];
			memset(_log, 0, _len);
			snprintf(_log, _len, "%s%s\n", __LogHead[_level], _logMsg);
			this->log(_log);
			delete[] _log;
		}
		void log(const char* _logMsg)
		{
			__Log != nullptr ? __Log(_logMsg) : (void)0;
		}

		virtual void __LOG(const char* _logMsg)
		{
			(void)_logMsg;
		}
		logFunc __Log;

	};
	class consoleLogger : public Logger
	{
		void __LOG(const char* _logMsg)override
		{
			printf(_logMsg);
		}
	};
	class fileLogger final : public Logger, public singleton<fileLogger>
	{
	private:
		FILE* __Fp;
		void __LOG(const char* _logMsg)override
		{
			if (!__Fp)return (void)(0);
			size_t nBytes = fprintf(__Fp, "%s", _logMsg);
			fflush(__Fp);
			(void)nBytes;
		}
	public:
		fileLogger() : Logger(), __Fp(nullptr) {}
		~fileLogger()
		{
			close();
		}
		void set(const char* fileName)
		{
			close();
			__Fp = fopen(fileName, "a+b");
		}
		void close(void)
		{
			if (__Fp)
				fclose(__Fp);
		}
	};
}
typedef logger::fileLogger fileLogger;
#endif // !__LOGGER_H__