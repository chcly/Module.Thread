#pragma once
#include <shared_mutex>
#include  <mutex>


namespace Rt2::Thread
{
    using Mutex = std::mutex;

    class ScopeLock
    {
    private:
        Mutex *_mutex{nullptr};

    public:
        explicit ScopeLock(Mutex * mutex)
        {
            if (mutex->try_lock())
                _mutex = mutex;
        }

        ~ScopeLock()
        {
            if (_mutex)
                _mutex->unlock();
        }

        bool isLocked() const
        {
            return _mutex != nullptr;
        }
    };


}  // namespace Rt2::Thread
