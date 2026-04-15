#pragma once

template <typename Ret, typename ...Args>
DerivedTask<Ret, Args...>::DerivedTask ()
{
}

template <typename Ret, typename ...Args>
DerivedTask<Ret, Args...>::DerivedTask (Fn<Ret, Args...> fn, Args... args) 
    : vTaskFn (std::move (fn)), vArgs (std::forward<Args> (args)...)
{
}

template <typename Ret, typename... Args>
DerivedTask<Ret, Args...>::~DerivedTask ()
{
}

template <typename Ret, typename... Args>
void
DerivedTask<Ret, Args...>::Execute ()
{
    if constexpr (std::is_void_v<Ret>) 
    {

        std::apply (vTaskFn, vArgs);
        uPromise.set_value ();
    } 
    else 
    {
        uPromise.set_value (std::apply (vTaskFn, vArgs));
    }
}
