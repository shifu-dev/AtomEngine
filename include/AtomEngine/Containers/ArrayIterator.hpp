#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/Iterator.hpp"

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

        ArrayIterator(const ThisT ref other) = default;
        ArrayIterator(ThisT rref other) = default;

        ThisT ref operator = (const ThisT ref other) = default;
        ThisT ref operator = (ThisT rref other) = default;

        virtual ElementT ref Value() noexcept override
        {
            return ptr mPtr;
        }

        virtual const ElementT ref Value() const noexcept override
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

        virtual int Compare(const IteratorT ref rhs) const noexcept override
        {
            const ThisT ptr rhsPtr = dcast<const ThisT ptr>(ref rhs);
            if (rhsPtr isnot null)
            {
                return Compare(ptr rhsPtr);
            }

            return -1;
        }

        virtual int Compare(const ThisT ref rhs) const noexcept
        {
            return scast<int>(mPtr - rhs.mPtr);
        }

    protected:
        mutable ElementT ptr mPtr;
    };
}