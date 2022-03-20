#pragma once
#include <detail/Logger.hpp>
#include <MQCore/MQType.h>

#ifndef __MYEXCEPTION_H__
#define __MYEXCEPTION_H__
struct MyException : public std::exception
{
protected:
	char* str;
public:
	UINT code;
	std::string ExcepetionName;
	const char* ExcepetionDesc;

	MyException(int code, const char* desc = "") :code(code), ExcepetionDesc(desc), str(new char[512])
	{}
	~MyException() { _DELETE_Arr(str); }
	virtual const char* what() const throw()
	{
		return ("MyException");
	}
	virtual void log(const char* LogPath) const throw()
	{
	}
};
#endif // !__MYEXCEPTION_H__

extern Text LogFile;
namespace MQ::exception
{
	class MQException : public MyException
	{
	public:
		MQException(Integer code, Text desc = "") : MyException(code, desc)
		{
			this->ExcepetionName = "MQException";
		}
		enum MQExceptionEnum
		{
			MQOK, MQInitOutTime = 1, MQDllInitFailed = 2, MQDllFuncError = 3
		};
		inline Text what()const throw() override
		{
			memset(str, 0, 512);
			sprintf(str, "·%s[%s %s]:Error Code 0X%.4X", ExcepetionName.c_str(), __DATE__, __TIME__, code);
			switch (code)
			{
			case MQExceptionEnum::MQInitOutTime: sprintf(str, "%s, %s\n", str, "插件初始化失败！");
				break;
			case MQExceptionEnum::MQDllInitFailed: sprintf(str, "%s, %s\n", str, "api加载失败，请确认路径下是否存在对应Dll文件或者插件是否使用了错误的函数名！");
				break;
			case MQExceptionEnum::MQDllFuncError: sprintf(str, "%s, %s\n", str, "api函数加载失败，请确认dll是否存在对应函数！");
				break;
			case MQOK:
			default: sprintf(str, "%s, %s\n", str, "插件正常运行！");
				break;
			}
			if (this->ExcepetionDesc != "")
			{
				sprintf(str, "%s%s\n", str, this->ExcepetionDesc);
			}
			return str;
		}
		inline void log(Text logfile = LogFile) const throw() override
		{
			using namespace logger;
			auto* _logger = fileLogger::instance();
			if (_logger)
			{
				_logger->set(logfile);
				_logger->info(what());
			}
		}
	};

}
#define MQExceptionCode(code, desc) \
	try\
	{\
		throw(MQ::exception::MQException(code, desc));\
	}\
	catch (const MQ::exception::MQException& e)\
	{\
		e.log();\
	}\


template <typename T, typename... Args>
std::function<T(Args...)> __stdcall MQExceptionWrapper(T(__stdcall* func)(Args...))
{
	return std::function<T(Args...)>([func](Args&&... args) -> T
		{
			try
			{
				return func(std::forward<Args>(args)...);
			}
			catch (const MQ::exception::MQException& e)
			{
				e.log();
			}
			return T(0);
		});
}