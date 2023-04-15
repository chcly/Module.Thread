#pragma once
#include "SharedValue.h"
#include "Thread.h"

namespace Rt2::Thread
{
    class Runner
    {
    private:
        Thread            _thread{};
        SharedValue<bool> _status{false};
        Mutex             _mutex{};

    public:
        Runner();
        virtual ~Runner();

        void start();

        void stop();

        bool isRunning();

        virtual void update();
    };
}  // namespace Rt2::Thread
