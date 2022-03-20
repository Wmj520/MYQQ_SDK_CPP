#pragma once
#include<atomic>
#include <mutex>
#ifndef CLASS_NOCOPY_DECLARE
#define CLASS_NOCOPY_DECLARE(__classname__) __classname__(const __classname__&) = delete;\
											__classname__& operator=(const __classname__&) = delete;
#endif // !CLASS_NOCOPY_DECLARE
#ifndef MIN
#define MIN(A, B) ((A>B)?B:A)
#endif
class spin_mutex
{
public:
	std::atomic_flag __Flag;
	void lock()
	{
		int k = 0;
		while (!try_lock()) {
			++k;
#ifdef _THIS_THREAD_
			this_thread::this_thread::no_interrupt_yield(MIN((k >> 2), 35));
#else
			if (k < 4) {}
			else if (k < 28)
			{
				std::this_thread::yield();
			}
			else
			{
				std::this_thread::sleep_until(_To_absolute_time(std::chrono::nanoseconds(MIN((k >> 2), 35))));
			}
#endif // _THIS_THREAD_
		}
	}
	void unlock()
	{
		__Flag.clear(std::memory_order_release);
	}
	bool try_lock()
	{
		return !__Flag.test_and_set(std::memory_order_acq_rel);
	}
	spin_mutex()
	{
		__Flag.clear();
	}
protected:
	CLASS_NOCOPY_DECLARE(spin_mutex)
};