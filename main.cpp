#include "tpool.h"

using namespace std;

void
HW (void* pNum)
{
	cout << "Hello CMake " << *(int*)pNum << endl;
}

void
PW(void *)
{
	cout << "Hello CMake " << endl;
}

int 
main ()
{
	ThreadPool pool(4);

	Task t {PW};

	pool.Enqueue (t);

	return 0;
}
