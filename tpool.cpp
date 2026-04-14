// tpool.cpp : Defines the entry point for the application.
//

#include "tpool.h"

ThreadPool::ThreadPool (uint pNumThreads)
{
	vNumThreads = pNumThreads;
	vTasksDone = false;

	for (uint i = 0; i < pNumThreads; i++)
	{
		vThreads.emplace_back (&ThreadPool::InternalWorker, this);
	}
}

ThreadPool::~ThreadPool()
{
	vMtx.lock();
	vTasksDone = true;
	vMtx.unlock();

	vCv.notify_all();

	for (std::thread& t : vThreads)
		t.join();
}

void
ThreadPool::InternalWorker()
{
	while (true)
	{
		std::unique_lock<std::mutex> lk (vMtx);

		while (!vTasksDone && vTaskQueue.empty())
		{
			vCv.wait (lk);
		}

		if (vTasksDone && vTaskQueue.empty())
		{
			lk.unlock ();
			return;
		}

		Task task = std::move (vTaskQueue.front());
		vTaskQueue.pop();
		lk.unlock();

		InternalExecuteTask(task);
	}
}

std::future<void*>
ThreadPool::Enqueue (Task pTask)
{
	std::future<void*> f = pTask.uPromise.get_future();

	vMtx.lock();
	vTaskQueue.push(std::move (pTask));
	vMtx.unlock();

	vCv.notify_all ();

	return f;
}

void
ThreadPool::InternalExecuteTask(Task& pTask)
{
	void* res = pTask.uTaskFn (pTask.uArgs);
	
	pTask.uPromise.set_value (res);
}