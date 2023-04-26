#pragma once
#include <functional>
#include <thread>

namespace Rt2::Thread
{
    using StandardThread = std::thread;

    class Thread
    {
    public:
        using Update = std::function<void()>;

    private:
        StandardThread* _thread{nullptr};

    public:
        Thread();
        ~Thread();

        void invoke(const Update& update);

        template <typename Callable, typename... Args>
        void invoke(const Callable &call, Args&&... args)
        {
            if (!_thread)
                _thread = new StandardThread(call, std::forward<Args>(args)...);
        }

        void join();

        static void yield();

        static void sleep(uint32_t ms);
    };
}  // namespace Rt2::Thread
