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
#include "Thread/Runner.h"

namespace Rt2::Thread
{
    Runner::Runner() = default;

    Runner::~Runner()
    {
        stop();
    }

    void Runner::start()
    {
        if (!_status.get())
        {
            _status.set(true);
            _thread.invoke(
                [this]
                { update(); });
        }
    }

    void Runner::stop()
    {
        if (_status.get())
        {
            _status.set(false);
            _thread.join();
        }
    }

    bool Runner::isRunning()
    {
        return _status.get();
    }

    bool Runner::isRunningUnlocked()
    {
        return _status.value();
    }

    void Runner::update()
    {
    }

}  // namespace Rt2::Thread
