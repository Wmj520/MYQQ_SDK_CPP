#include <MQCore/MQAPI.h>

namespace MQ::Detail
{
    std::vector<std::function<void(HMODULE)>> apiFuncInitializers;
#define MQAPI(Name, ReturnType, ...) Name##_FUNC _##Name; \
	using Name##_TYPE = ReturnType (__stdcall*)(__VA_ARGS__); \
    bool _init_##Name = addFuncInit( [] (const auto& hModule) { \
        _##Name = reinterpret_cast<Name##_TYPE>(GetProcAddress(hModule, "Api_" #Name)); \
        if (!_##Name)MQExceptionCode(MQ::exception::MQException::MQExceptionEnum::MQDllFuncError, "Unable to initialize API Function " #Name); \
    });
#include <MQCore/MyQQAPI.inc>
#undef MQAPI
}