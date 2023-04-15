#pragma once
#include "Mutex.h"

namespace Rt2::Thread
{

    template <typename T>
    class SharedValue
    {
    public:
        using ValueType = T;

    protected:
        ValueType      _value{};

    public:
        SharedValue() = default;
        SharedValue(const SharedValue& val)           = delete;
        SharedValue operator=(const SharedValue& val) = delete;

        explicit SharedValue(const ValueType& val) :
            _value(val)
        {
        }

        ValueType get(Mutex &owner)
        {
            ScopeLock lock(&owner);
            return _value;
        }

        void set(const ValueType& rhs, Mutex &owner)
        {
            if (const ScopeLock lock(&owner); 
                lock.isLocked())
                _value = rhs;
        }
    };

    template <typename T>
    class CallValue : public SharedValue<T>
    {
    public:
        using ValueType = typename SharedValue<T>::ValueType;

    public:
        template <typename... Args>
        void invoke(Mutex &owner, Args&&... args)
        {
            if (const ScopeLock lock(&owner); 
                lock.isLocked())
                this->_value((std::forward<Args>(args), ...));
        }
    };
}  // namespace Rt2
