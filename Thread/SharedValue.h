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
#include "Thread/Mutex.h"

namespace Rt2::Thread
{
    template <typename T>
    class SharedValue
    {
    public:
        using ValueType = T;

    protected:
        ValueType _value{};
        Mutex     _mutex{};

    public:
        SharedValue()                                  = default;
        SharedValue(const SharedValue& val)            = default;
        SharedValue& operator=(const SharedValue& val) = default;

        ScopeLock scopeLock()
        {
            return ScopeLock(&_mutex);
        }

        explicit SharedValue(const ValueType& val) :
            _value(val)
        {
        }

        ValueType get()
        {
            ScopeLock lock(&_mutex);
            return _value;
        }

        void lock()
        {
            _mutex.lock();
        }

        void unlock()
        {
            _mutex.unlock();
        }

        ValueType tryGet(ValueType error)
        {
            if (const ScopeLock lock(&_mutex);
                lock.isLocked())
                return _value;
            return error;
        }

        ValueType value()
        {
            return _value;
        }

        void set(const ValueType& rhs)
        {
            if (const ScopeLock lock(&_mutex);
                lock.isLocked())
                _value = std::move(rhs);
        }
    };

    template <typename T>
    class SharedCall : public SharedValue<T>
    {
    public:
        using ValueType = typename SharedValue<T>::ValueType;

    public:
        template <typename... Args>
        void invoke(Args&&... args)
        {
            if (const ScopeLock lock(&this->_mutex);
                lock.isLocked())
                this->_value(std::forward<Args>(args)...);
        }
    };
}  // namespace Rt2::Thread
