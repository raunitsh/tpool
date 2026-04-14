#include <queue>
#include <mutex>
#include <thread>
#include <atomic>
#include <future>

typedef unsigned int uint;

typedef int (*TaskFn) (void* pArgs);

typedef struct
{
	TaskFn				uTaskFn;
	void*				uArgs;
	std::promise<int>	uPromise;
}
Task;