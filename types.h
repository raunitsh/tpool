#include <queue>
#include <mutex>
#include <thread>
#include <atomic>
#include <future>

typedef unsigned int uint;

template<typename T, typename ...Args>
using Fn = T (*) (Args...);