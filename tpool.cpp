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

		BaseTask* task = vTaskQueue.front();
		vTaskQueue.pop();
		lk.unlock();

		InternalExecuteTask(task);
	}
}

void
ThreadPool::InternalExecuteTask(BaseTask* pTask)
{
	pTask->Execute ();	
}