#include <iostream>

#include "tpool.h"

using namespace std;

std::mutex mtx;

std::string 
GetNum (int pN)
{
    mtx.lock ();
    cout << "Task running, got: " << pN << endl;
    mtx.unlock ();

    return "Hello Raunit";
}

int 
main () 
{
    ThreadPool pool(4); 
    std::vector<future<std::string>> fs;

    for (int i = 0; i < 10; i++) 
    {
        future<string> f = pool.Enqueue (GetNum, i);
        fs.emplace_back(std::move(f));
    }

    this_thread::sleep_for (chrono::milliseconds(8));

    for (uint i=0; i<fs.size(); i++)
    {
        string res = fs[i].get ();
        cout << "got value: " << res << endl;
    }

    return 0;
}