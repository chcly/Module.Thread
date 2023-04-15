#pragma once
#include <functional>
#include <thread>

namespace Rt2::Thread
{
    class Thread
    {
    public:
        using Update = std::function<void()>;

    private:
        using PlatformThread = std::thread;

        PlatformThread* _thread;

    public:
        Thread();
        ~Thread();

        void invoke(const Update& update);

        template <typename Callable, typename... Args>

        void invoke(const Callable& call, Args&& ... args)
        {
            if (!_thread)
                _thread = new PlatformThread(call, std::forward<Args>(args)...);
        }

        void join();

        static void yield();

        static void sleep(uint32_t ms);
    };

}  // namespace Rt2::Thread
