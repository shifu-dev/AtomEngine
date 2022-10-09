#pragma once
#include "SSEngine/Core.hpp"
#include "SSEngine/Collections/Iterator.hpp"
#include <stdexcept>

namespace SSEngine
{
    template <typename TElement>
    class Array;

    /// @brief iterator for stack array
    /// @tparam TElement type of element stack array holds
    template <typename TElement>
    class ArrayIterator : public virtual RandomAccessIterator<TElement>
    {
        using SizeType = sizet;
        using ThisT = ArrayIterator<TElement>;
        using BaseT = RandomAccessIterator<TElement>;
        using IteratorT = Iterator<TElement>;

    public:
        using ElementType = TElement;

    public:
        ArrayIterator(TElement ptr elementPtr)
            : _ptr(elementPtr) { }

        ArrayIterator(const ThisT lref other) = default;
        ArrayIterator(ThisT rref other) = default;

        ThisT lref operator = (const ThisT lref other) = default;
        ThisT lref operator = (ThisT rref other) = default;

        virtual TElement lref Value() noexcept override
        {
            return ptr _ptr;
        }

        virtual const TElement lref Value() const noexcept override
        {
            return ptr _ptr;
        }

        virtual void MoveFwdBy(const SizeType steps) const noexcept override
        {
            _ptr = _ptr + steps;
        }

        virtual void MoveBwdBy(const SizeType steps) const noexcept override
        {
            _ptr = _ptr - steps;
        }

        virtual int Compare(const IteratorT lref rhs) const noexcept override
        {
            const ThisT ptr rhsPtr = dynamic_cast<const ThisT ptr>(lref rhs);
            if (rhsPtr isnot null)
            {
                return Compare(ptr rhsPtr);
            }

            return -1;
        }

        virtual int Compare(const ThisT lref rhs) const noexcept
        {
            return _ptr - rhs._ptr;
        }

    protected:
        mutable ElementType ptr _ptr;
    };
}