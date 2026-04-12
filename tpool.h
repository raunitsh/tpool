// tpool.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>

#include "types.h"

class ThreadPool
{

public:

			ThreadPool			(uint pNumThreads);

	void	Enqueue				(Task& pTask);

private:

	void	InternalExecuteTask	(Task& pTask);

	uint	vNumThreads;
};