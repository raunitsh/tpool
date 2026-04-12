#include <iostream>

#include "tpool.h"

using namespace std;

std::mutex mtx;

void 
PrintNumber (void* args) 
{
    mtx.lock();
    cout << "Task running, got: " << *(int*)(args) << endl;
    mtx.unlock();

    delete args;
}

int 
main () 
{
    ThreadPool pool(4); 

    for (int i = 0; i < 10; i++) 
    {
        Task t;
        int* arg = new int(i);
        
        t.uTaskFn = PrintNumber;
        t.uArgs = arg;
        
        pool.Enqueue (t);
    }

    return 0;
}