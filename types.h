#include <queue>
#include <mutex>
#include <thread>
#include <atomic>
#include <future>

typedef unsigned int uint;

typedef void* (*TaskFn) (void* pArgs);

typedef struct
{
	TaskFn				uTaskFn;
	void*				uArgs;
	std::promise<void*>	uPromise;
}
Task;