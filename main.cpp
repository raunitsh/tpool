#include <iostream>

#include "tpool.h"

using namespace std;

std::mutex mtx;

int
PrintNumber (void* args) 
{
    //mtx.lock();
    //cout << "Task running, got: " << *(int*)(args) << endl;
    //mtx.unlock();

    return *(int*)args;
}

int 
main () 
{
    ThreadPool pool(4); 
    std::vector<future<int>> fs;

    for (int i = 0; i < 10; i++) 
    {
        int* arg = new int(i);
        
        future<int> f = pool.Enqueue ({PrintNumber, arg});
        fs.emplace_back(std::move(f));
    }

    for (future<int>& f : fs)
    {
        cout << "got value: " << f.get() << endl;
    }

    return 0;
}