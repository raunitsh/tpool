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
        int* arg = new int(i);
        
        pool.Enqueue ({PrintNumber, arg});
    }

    return 0;
}