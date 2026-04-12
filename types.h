#include <queue>
#include <mutex>
#include <thread>
#include <atomic>

typedef unsigned int uint;

typedef void (*TaskFn) (void* pArgs);

typedef struct
{
	TaskFn	uTaskFn;
	void* uArgs;

} Task;
