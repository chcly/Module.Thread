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

        explicit SharedValue(const ValueType& val) :
            _value(val)
        {
        }

        ValueType get()
        {
            ScopeLock lock(&_mutex);
            return _value;
        }

        ValueType tryGet(ValueType error)
        {
            if (const ScopeLock lock(&_mutex);
                !lock.isLocked())
                return _value;
            return error;
        }

        void set(const ValueType& rhs)
        {
            if (const ScopeLock lock(&_mutex);
                lock.isLocked())
                _value = rhs;
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
