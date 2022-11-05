#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/Iterator.hpp"
#include <stdexcept>

namespace Atom
{
    template <typename TElement>
    class Array;

    /// @brief iterator for stack array
    /// @tparam TElement type of element stack array holds
    template <typename TElement>
    class ArrayIterator : public virtual RandomAccessIterator<TElement>
    {
        using ThisT = ArrayIterator<TElement>;
        using ElementT = TElement;
        using IteratorT = Iterator<ElementT>;

    public:
        ArrayIterator(ElementT ptr elementPtr)
            : mPtr(elementPtr) { }

        ArrayIterator(const ThisT lref other) = default;
        ArrayIterator(ThisT rref other) = default;

        ThisT lref operator = (const ThisT lref other) = default;
        ThisT lref operator = (ThisT rref other) = default;

        virtual ElementT lref Value() noexcept override
        {
            return ptr mPtr;
        }

        virtual const ElementT lref Value() const noexcept override
        {
            return ptr mPtr;
        }

        virtual void MoveFwdBy(const sizet steps) const noexcept override
        {
            mPtr = mPtr + steps;
        }

        virtual void MoveBwdBy(const sizet steps) const noexcept override
        {
            mPtr = mPtr - steps;
        }

        virtual int Compare(const IteratorT lref rhs) const noexcept override
        {
            const ThisT ptr rhsPtr = dcast<const ThisT ptr>(lref rhs);
            if (rhsPtr isnot null)
            {
                return Compare(ptr rhsPtr);
            }

            return -1;
        }

        virtual int Compare(const ThisT lref rhs) const noexcept
        {
            return scast<int>(mPtr - rhs.mPtr);
        }

    protected:
        mutable ElementT ptr mPtr;
    };
}