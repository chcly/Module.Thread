#include <cstdio>
#include "Source/ParallelFor.h"
#include "Source/Runner.h"
#include "Source/Thread.h"
#include "Utils/Array.h"
#include "Utils/Console.h"
#include "Utils/Time.h"
#include "gtest/gtest.h"
#include "oneapi/tbb.h"

using namespace Rt2::Thread;

GTEST_TEST(Thread, Thread_001)
{
    constexpr uint32_t wait       = 0x10;
    const uint32_t     scopeStart = Rt2::Time::now32();
    {
        struct Sleeper
        {
            void operator()(const uint32_t w1, const uint32_t w2, const uint32_t w3) const
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

GTEST_TEST(Thread, Thread_002)
{
    class TestRunner : public Runner
    {
    private:
        int _i{0};

    public:
        ~TestRunner() override = default;

        void update() override
        {
            ++_i;
        }
    };

    class Primary
    {
    private:
        Mutex                 mutex;
        SharedValue<uint32_t> current{0};

    public:
        Primary() = default;

        void operator()(const uint32_t n)
        {
            TestRunner runner;
            for (uint32_t i = 1; i <= n; ++i)
            {
                if (runner.isRunning())
                    runner.stop();
                runner.start();
                current.set(i, mutex);
            }
            if (runner.isRunning())
                runner.stop();
        }

        uint32_t iteration()
        {
            return current.get(mutex);
        }
    };

    constexpr uint32_t inside        = 200;
    constexpr uint32_t foregroundMax = (inside * 1000) * 2;

    uint32_t foreground = 0;
    Primary  main;
    {
        uint32_t i = 0;
        Thread   th;

        constexpr uint32_t outside = inside >> 1;

        th.invoke([&main, inside]
                  { main(inside); });

        while (i < outside && foreground < foregroundMax)
        {
            i = main.iteration();
            ++foreground;
        }
        EXPECT_GE(i, outside);
        EXPECT_GE(main.iteration(), outside);
    }

    EXPECT_LT(foreground, foregroundMax);
    EXPECT_EQ(main.iteration(), inside);
}

GTEST_TEST(OneAPI, Test_001)
{
    Rt2::SimpleArray<int> foo;

    Rt2::Console::println("alloc");
    foo.resize(1'000'000, 0);
    Rt2::Console::println("run");
    For<int>::invoke(foo.data(), foo.size(), [](int& v)
    {
        v += 1;
        v %= 3;
    });
}
