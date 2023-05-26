/*
-------------------------------------------------------------------------------
    Copyright (c) Charles Carley.

  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
-------------------------------------------------------------------------------
*/
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
