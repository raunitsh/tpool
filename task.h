#include "types.h"

class BaseTask 
{
    public:

virtual         void        Execute         () = 0;
virtual
                            ~BaseTask       () = default;
};

template<typename Ret, typename ...Args>
class DerivedTask : public BaseTask 
{
    public:

                            DerivedTask     ();
                            DerivedTask     (Fn<Ret, Args...> fn, Args... args);
                            ~DerivedTask    ();

        void                Execute         () override;

public:
        std::promise<Ret>   uPromise;

private:
        Fn<Ret, Args...>    vTaskFn;
        std::tuple<Args...> vArgs;
};

#include "task.hxx"
