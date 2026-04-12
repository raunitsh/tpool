// tpool.cpp : Defines the entry point for the application.
//

#include "tpool.h"

ThreadPool::ThreadPool (uint pNumThreads)
{
	vNumThreads = pNumThreads;
}

void
ThreadPool::Enqueue (Task& pTask)
{
	InternalExecuteTask(pTask);
}

void
ThreadPool::InternalExecuteTask(Task& pTask)
{
	pTask.uTaskFn (pTask.uArgs);
}