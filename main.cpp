#include <iostream>

#include "tpool.h"

using namespace std;

std::mutex mtx;

void*
PrintNumber (void* args) 
{
    mtx.lock();
    cout << "Task running, got: " << *(int*)(args) << endl;
    mtx.unlock();

    return (void*)args;
}

int 
main () 
{
    ThreadPool pool(4); 
    std::vector<future<void*>> fs;

    for (int i = 0; i < 10; i++) 
    {
        int* arg = new int(i);
        
        future<void*> f = pool.Enqueue ({PrintNumber, arg});
        fs.emplace_back(std::move(f));
    }

    this_thread::sleep_for (chrono::milliseconds(8));

    for (uint i=0; i<fs.size(); i++)
    {
        void * res = fs[i].get ();
        cout << "got value: " << *(int*)res << endl;
    }

    return 0;
}