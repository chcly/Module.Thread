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
        if (!_status.get(_mutex))
        {
            _status.set(true, _mutex);
            _thread.invoke(
                [this]
                { update(); });
        }
    }

    void Runner::stop()
    {
        if (_status.get(_mutex))
        {
            _status.set(false, _mutex);
            _thread.join();
        }
    }

    bool Runner::isRunning()
    {
        return _status.get(_mutex);
    }

    void Runner::update()
    {
    }

}  // namespace Rt2::Thread
