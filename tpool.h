// tpool.hpp : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>

#include "types.h"

class ThreadPool
{

public:

								ThreadPool			(uint pNumThreads);
								~ThreadPool			();

	void						Enqueue				(const Task& pTask);

private:

	void						InternalExecuteTask (Task& pTask);
	void						InternalWorker		();

	uint						vNumThreads;
	std::queue<Task>			vTaskQueue;
	std::mutex					vMtx;
	std::condition_variable		vCv;
	std::vector<std::thread>	vThreads;
	std::atomic<bool>			vTasksDone;
};