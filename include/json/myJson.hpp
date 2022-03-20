#pragma once
#ifndef __JSON_FUN__
#define __JSON_FUN__
#ifdef USE_JSONCPP
#include "json.h"
#include <fstream>
class JsonParser
{
protected:
#define __GetJsonMember(__Type, __Name) template<class _Ty>\
static typename std::enable_if<std::is_same<_Ty, __Type>::value, bool>::type getJsonMember(const Json::Value* _root, _Ty& _ret)\
{\
	if (_root->is##__Name())\
	{\
		_ret = _root->as##__Name();\
		return true;\
	}\
	return false;\
}
	__GetJsonMember(int, Int)
		__GetJsonMember(int64_t, Int64)
		__GetJsonMember(uint32_t, UInt)
		__GetJsonMember(uint64_t, UInt64)
		__GetJsonMember(bool, Bool)
		__GetJsonMember(double, Double)
		template<class _Ty>
	static typename std::enable_if<std::is_same<_Ty, std::string>::value, bool>::type getJsonMember(const Json::Value* _json, _Ty& _ret)
	{
		if (_json->isString())_ret = _json->asCString();
		else _ret = _json->toStyledString();
		return true;
	}
	template<class _Ty>
	static typename std::enable_if<std::is_same<_Ty, Json::Value*>::value, bool>::type getJsonMember(const Json::Value* _json, _Ty& _ret)
	{
		if (!_json->isObject())return false;
		_ret = const_cast<_Ty>(_json);
		return true;
	}
#undef __GetJsonMember
public:
	static bool toFile(Json::Value* _json, std::string const& fileName)
	{
		std::ofstream out;
		out.open(fileName);
		if (!out.is_open())return false;
		out << _json->toStyledString();
		out.close();
		return true;
	}
	template<class _Ty>
	static inline bool parseStr(Json::Value* _json, _Ty const& _str)
	{
		Json::CharReaderBuilder builder;
		builder["collectComments"] = false;
		std::stringstream basic_stringstream(_str);
		parseFromStream(builder, basic_stringstream, _json, nullptr);
		return true;
	}
	static inline bool parseFile(Json::Value* _json, std::string const& _file)
	{
		std::ifstream in;
		in.open(_file);
		if (!in.is_open())return false;
		Json::CharReaderBuilder builder;
		builder["collectComments"] = false;
		parseFromStream(builder, in, _json, nullptr);
		return true;
	}
	static inline Json::Value* parsePathExist(Json::Value* _json, std::initializer_list<std::string>const& _path)
	{
		auto _value = _json;
		for (const auto& it : _path)
		{
			if (!_value->isMember(it))return nullptr;
			_value = &((*_value)[it]);
		}
		return _value;
	}
	static inline Json::Value* parsePath(Json::Value* _json, std::initializer_list<std::string>const& _path)
	{
		auto _value = _json;
		for (const auto& it : _path)
		{
			_value = &((*_value)[it]);
		}
		return _value;
	}
	template<class _Ty>
	static bool read(Json::Value* _json, std::initializer_list<std::string>const& _path, _Ty& _Data)
	{
		auto _value = parsePathExist(_json, _path);
		if (_value == nullptr)return false;
		return getJsonMember(_value, _Data);
	}
	template<class _Ty>
	static bool readArray(Json::Value* _json, std::initializer_list<std::string>const& _path, std::vector<_Ty>& _Data)
	{
		auto _value = parsePathExist(_json, _path);
		if (_value == nullptr || !_value->isArray())return false;
		_Data.resize(_value->size());
		for (size_t i = 0; i < _value->size(); i++)
		{
			getJsonMember(&(*_value)[i], _Data[i]);
		}
		return true;
	}
	template<class _Ty>
	static bool write(Json::Value* _json, std::initializer_list<std::string>const& _path, _Ty const& _Data)
	{
		auto _value = parsePath(_json, _path);
		if (_value == nullptr)return false;
		*_value = _Data;
		return true;
	}
	template<class _Ty>
	static bool writeArray(Json::Value* _json, std::initializer_list<std::string>const& _path, std::initializer_list<_Ty> const& _Data)
	{
		auto _value = parsePath(_json, _path);
		if (_value == nullptr)return false;
		if (!_value->isArray())_value->clear();
		for (const auto& it : _Data)
		{
			_value->append(it);
		}
		return true;
	}
	template<class _Ty>
	static bool check(Json::Value* _json, std::initializer_list<std::string>const& _path, _Ty const& _Data)
	{
		_Ty _Da;
		if (!read(_json, _path, _Da))return false;
		return _Da == _Data;
	}
};

#define parseJsonToStruct(_json, _struct, _attr)	JsonParser::read(&_json, {"_attr"}, _struct.##_attr);
#define parseJson(_attr) parseJsonToStruct(_json, _event, _attr)
#define parseStruct(_attr) _json[#_attr] = _event.#_attr
#endif
#endif
