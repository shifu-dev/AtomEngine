#pragma once
#include "SSEngine/Core.hpp"
#include "SSEngine/Collections/Iterator.hpp"
#include <stdexcept>

namespace SSEngine
{
    template <typename TValueType>
    class Array;

    /// @brief iterator for stack array
    /// @tparam TValueType type of element stack array holds
    template <typename TValueType>
    class ArrayIterator : public RandomAccessIterator<TValueType>
    {
        using ValueTypeT = typename Array<TValueType>::ValueTypeT;
        using ThisT = ArrayIterator<ValueTypeT>;
        using BaseT = RandomAccessIterator<TValueType>;
        using SizeT = umax;

    public:
        ArrayIterator(TValueType ptr elementPtr)
            : _ptr(elementPtr) { }

        virtual TValueType lref Value() override
        {
            return ptr _ptr;
        }

        virtual const TValueType lref Value() const override
        {
            return ptr _ptr;
        }

        virtual void MoveFwdBy(const SizeT steps) noexcept override
        {
            _ptr + steps;
        }

        virtual void MoveBwdBy(const SizeT steps) noexcept override
        {
            _ptr - steps;
        }

        virtual int Compare(const ForwardIterator<ValueTypeT> lref rhs) const noexcept override
        {
            const ThisT ptr rhsPtr = dynamic_cast<const ThisT ptr>(lref rhs);
            if (rhsPtr isnot null)
            {
                return Compare(ptr rhsPtr);
            }

            return -1;
        }

        virtual int Compare(const ArrayIterator<ValueTypeT> lref rhs) const noexcept
        {
            return _ptr - rhs._ptr;
        }

    protected:
        ValueTypeT ptr _ptr;
    };
}

template <typename TValueType>
using SSArray = SSEngine::Array<TValueType>;