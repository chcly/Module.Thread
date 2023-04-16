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

    void Runner::update()
    {
    }

}  // namespace Rt2::Thread
