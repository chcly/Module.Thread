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

        Copy(const PointerType dest, const ConstPointerType src) :
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
