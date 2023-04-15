#pragma once
#ifdef USE_ONEAPI

    #include <functional>
    #include "oneapi/tbb/parallel_for.h"

namespace Rt2::Thread
{
    template <typename T, typename SizeType = uint32_t>
    class For
    {
    public:
        using Function    = std::function<void(T&)>;
        using PointerType = T*;

    private:
        PointerType _data{nullptr};
        Function    _invoke{nullptr};

        For(const PointerType ptr, Function invoke) :
            _data(ptr),
            _invoke(std::move(invoke))
        {
        }

    public:
        void operator()(const oneapi::tbb::blocked_range<SizeType>& r) const
        {
            PointerType ptr = _data;
            for (SizeType i = r.begin(); i != r.end(); ++i)
                _invoke(ptr[i]);
        }

        static void invoke(PointerType     ptr,
                           SizeType        size,
                           const Function& invoke)
        {
            oneapi::tbb::parallel_for(
                oneapi::tbb::blocked_range<SizeType>(0, size),
                For(ptr, invoke));
        }
    };

}  // namespace Rt2::Thread
#endif
