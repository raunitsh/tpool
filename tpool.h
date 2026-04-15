// tpool.hpp : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>

#include "task.h"

class ThreadPool
{

public:

								ThreadPool			(uint pNumThreads);
								~ThreadPool			();

	template<typename Ret, typename ...Args>
	std::future<Ret>            Enqueue             (Fn<Ret, Args...> pFunc, Args... pArgs);

private:

	void						InternalExecuteTask (BaseTask* pTask);
	void						InternalWorker		();

	uint						vNumThreads;
	std::queue<BaseTask*>		vTaskQueue;
	std::mutex					vMtx;
	std::condition_variable		vCv;
	std::vector<std::thread>	vThreads;
	bool						vTasksDone;
};

#include "tpool.hxx"