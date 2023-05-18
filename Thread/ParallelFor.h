#pragma once
#include <cstdint>

#ifdef USE_ONEAPI
#include <oneapi/tbb.h>
#endif

#include <functional>

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
#ifdef USE_ONEAPI
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
#else
        void operator()(const SizeType& r) const
        {
            PointerType ptr = _data;
            PointerType end = _data + r;

            while (ptr != end)
                _invoke(*ptr++);
        }

        static void invoke(PointerType     ptr,
                           SizeType        size,
                           const Function& invoke)
        {
            For(ptr, invoke)(size);
        }
#endif
    };

    template <typename T, typename SizeType = uint32_t>
    class Copy
    {
    public:
        using PointerType      = T*;
        using ConstPointerType = const T*;

    private:
        ConstPointerType _src{nullptr};
        PointerType      _dest{nullptr};

        Copy(PointerType dest, ConstPointerType src) :
            _src(src),
            _dest(dest)
        {
        }

    public:
#ifdef USE_ONEAPI
        void operator()(const oneapi::tbb::blocked_range<SizeType>& r) const
        {
            ConstPointerType s = _src;
            PointerType      d = _dest;

            for (SizeType i = r.begin(); i != r.end(); ++i)
                d[i] = s[i];
        }

        static void invoke(PointerType      dest,
                           ConstPointerType src,
                           SizeType         size)
        {
            oneapi::tbb::parallel_for(
                oneapi::tbb::blocked_range<SizeType>(0, size),
                Copy(dest, src));
        }
#else
        void operator()(const SizeType& r) const
        {
            ConstPointerType s = _src;
            PointerType      d = _dest;

            for (SizeType i = 0; i<r; ++i)
                d[i] = s[i];
        }

        static void invoke(PointerType      dest,
                           ConstPointerType src,
                           SizeType         size)
        {
            Copy(dest, src)(size);
        }
#endif
    };
}  // namespace Rt2::Thread
