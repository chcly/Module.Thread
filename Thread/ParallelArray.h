#pragma once
#ifdef USE_ONEAPI

#include <functional>
#include "oneapi/tbb/concurrent_vector.h"

namespace Rt2::Thread
{
    template <typename T>
    class ParallelArray : public oneapi::tbb::concurrent_vector<T>
    {
        
    };
}  // namespace Rt2::Thread
#endif
