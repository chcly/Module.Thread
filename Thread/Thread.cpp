#include "Thread/Thread.h"
#include "Utils/Console.h"

namespace Rt2::Thread
{

    Thread::Thread()
    {
    }

    Thread::~Thread()
    {
        if (_thread)
            join();
    }

    void Thread::yield()
    {
        sleep(1);
    }

    void Thread::sleep(const uint32_t ms)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    }
    
    void Thread::invoke(const Update& update)
    {
        if (!_thread)
            _thread = new StandardThread(update);
    }

    void Thread::join()
    {
        if (_thread)
        {
            if (!_thread->joinable())
            {
                Console::println(
                    "attempt to join a thread, "
                    "from the wrong thread");
                return;
            }

            try
            {
                _thread->join();
                delete _thread;
                _thread = nullptr;
            }
            catch (...)
            {
                delete _thread;
                _thread = nullptr;
            }
        }
    }

}  // namespace Rt2::Thread
