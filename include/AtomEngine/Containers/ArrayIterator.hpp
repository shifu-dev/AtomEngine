#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/IRandomAccessIterator.hpp"

namespace Atom
{
    template <typename TElement>
    interface IArray;

    /// Iterator for array.
    /// 
    /// @tparam TElement Type of element iterator iterates over.
    template <typename TElement>
    interface ArrayIterator : public virtual IRandomAccessIterator<TElement>
    {
        using ThisT = ArrayIterator<TElement>;
        using ElementT = TElement;
        using IIteratorT = IIterator<ElementT>;

        mpublic ArrayIterator(ElementT ptr elementPtr)
            : mPtr(elementPtr) { }

        mpublic ArrayIterator(const ThisT ref other) = default;
        mpublic ArrayIterator(ThisT rref other) = default;

        mpublic ThisT ref operator = (const ThisT ref other) = default;
        mpublic ThisT ref operator = (ThisT rref other) = default;

        mpublic virtual ElementT ref Value() noexcept override
        {
            return ptr mPtr;
        }

        mpublic virtual const ElementT ref Value() const noexcept override
        {
            return ptr mPtr;
        }

        mpublic virtual void MoveFwdBy(const sizet steps) const noexcept override
        {
            mPtr = mPtr + steps;
        }

        mpublic virtual void MoveBwdBy(const sizet steps) const noexcept override
        {
            mPtr = mPtr - steps;
        }

        mpublic virtual int Compare(const IIteratorT ref rhs) const noexcept override
        {
            const ThisT ptr rhsPtr = DCAST(const ThisT ptr, ref rhs);
            if (rhsPtr isnot null)
            {
                return Compare(ptr rhsPtr);
            }

            return -1;
        }

        mpublic virtual int Compare(const ThisT ref rhs) const noexcept
        {
            return SCAST(int, mPtr - rhs.mPtr);
        }

        mprotected mutable ElementT ptr mPtr;
    };
}