#include <queue>
#include <mutex>
#include <thread>
#include <atomic>
#include <future>

typedef unsigned int uint;

typedef void* (*TaskFn) (void* pArgs);

template<typename T, typename ...Args>
using Fn = T (*) (Args...);

typedef struct
{
	TaskFn				uTaskFn;
	void*				uArgs;
	std::promise<void*>	uPromise;
}
Task;