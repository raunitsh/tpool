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
	vTasksDone = true;
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

		Task task = vTaskQueue.front();
		vTaskQueue.pop();
		lk.unlock();

		InternalExecuteTask(task);
	}
}

void
ThreadPool::Enqueue (const Task& pTask)
{
	vMtx.lock();
	vTaskQueue.push (pTask);
	vMtx.unlock();

	vCv.notify_all ();
}

void
ThreadPool::InternalExecuteTask(Task& pTask)
{
	pTask.uTaskFn (pTask.uArgs);
}