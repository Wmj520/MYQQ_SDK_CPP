#pragma once

#ifndef __SINGLETON_H__
#define __SINGLETON_H__

#include<mutex>
#include<atomic>
template<typename _InstanceType>
class singleton
{
public:
	__forceinline static _InstanceType* instance()
	{
		_InstanceType* _Ins = __Instance.load(std::memory_order_acquire);
		if (nullptr != _Ins)return _Ins;
		static std::mutex __Ins_Mutex;
		std::lock_guard<std::mutex> _Lg(__Ins_Mutex);
		_Ins = __Instance.load(std::memory_order_relaxed);
		if (nullptr == _Ins)
		{
			try
			{
				_Ins = ::new _InstanceType();
				__Instance.store(_Ins, std::memory_order_release);
				if (!__Ins_Exist.load(std::memory_order_acquire))
				{
					singleton<_InstanceType>::schedule_for_destory(singleton<_InstanceType>::destory_instance);
					__Ins_Exist.store(true, std::memory_order_release);
				}
			}
			catch (...)
			{
				::delete _Ins;
				//THROW
			}
		}
		return nullptr;
	}
	static void destory_instance()
	{
		_InstanceType* _Ins = __Instance.load(std::memory_order_acquire);
		if (nullptr != _Ins)
		{
			static std::mutex __Ins_Destory_Mutex;
			std::lock_guard<std::mutex> __Lg(__Ins_Destory_Mutex);
			_Ins = __Instance.load(std::memory_order_acquire);
			if (nullptr != _Ins)
			{
				::delete _Ins;
				__Instance.store(nullptr, std::memory_order_release);
			}
		}
	}

protected:
	static void schedule_for_destory(void(*func)())
	{
		std::atexit(func);
	}
	singleton() {}
	virtual ~singleton() {}
	singleton(const singleton<_InstanceType>&) = delete;
	singleton<_InstanceType>& operator=(const singleton<_InstanceType>&) = delete;
	static std::atomic<_InstanceType*> __Instance;
	static std::atomic_bool __Ins_Exist;
};
template<typename _InstanceType>
std::atomic<_InstanceType*> singleton< _InstanceType>::__Instance(nullptr);
template<typename _InstanceType>
std::atomic_bool singleton< _InstanceType>::__Ins_Exist(false);
#endif // !__SINGLETON_H__