#include <cstdio>
#include "Source/Runner.h"
#include "Source/Thread.h"
#include "Utils/Console.h"
#include "Utils/Time.h"
#include "gtest/gtest.h"

using namespace Rt2::Thread;

GTEST_TEST(Thread, Thread_001)
{
    constexpr uint32_t wait       = 0x10;
    const uint32_t     scopeStart = Rt2::Time::now32();
    {
        struct Sleeper
        {
            void operator()(uint32_t w1, uint32_t w2, uint32_t w3) const
            {
                Thread::sleep(w1);
                Thread::sleep(w2);
                Thread::sleep(w3);
            }
        };

        Thread th;

        constexpr Sleeper sleeper;
        th.invoke(sleeper, wait, wait, wait);
    }
    const uint32_t scopeEnd = Rt2::Time::now32();
    EXPECT_GE(scopeEnd - scopeStart, wait);
}

GTEST_TEST(Thread, Thread_003)
{
    class TestRunner : public Runner
    {
    private:
        int _i{0};

    public:
        ~TestRunner() override = default;

        void update() override
        {
            Rt2::Console::println("run ", _i);
            ++_i;
        }
    };

    TestRunner runner;
    for (int i = 0; i < 100; ++i)
    {
        if (runner.isRunning())
            runner.stop();

        runner.start();
    }
    if (runner.isRunning())
        runner.stop();
}
