#pragma once
#ifndef __MQCONFIG_H__
#define __MQCONFIG_H__
#define USE_SLN
#define USE_JSONCPP
//#define USE_TIMER

#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN             // 从 Windows 头文件中排除极少使用的内容
// Windows 头文件
#include <windows.h>
#include <functional>
#include <string>
#include <cstdint>
#include <vector>
#include <map>
#include <set>
#include <exception>
#include <ctime>
#include <sstream>

#define CallingConvention __stdcall
#define ThreadPoolSize 2
#define _DELETE(__Ptr) {if(__Ptr != nullptr){delete (__Ptr); (__Ptr) = nullptr;}}
#define _DELETE_Arr(__Ptr) {if(__Ptr != nullptr){delete[] (__Ptr); (__Ptr) = nullptr;}}
#endif //!__MQCONFIG_H__
