#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/IConstList.hpp"
#include "AtomEngine/Containers/ArrayIterator.hpp"

namespace Atom
{
    /// Represents a read only collection that holds memory in contiguous order.
    /// 
    /// @tparam TElement Type of element this array contains.
    template <typename TElement>
    interface IConstArray : public virtual IConstList<TElement>
    {
        using ElementT = TElement;
        using IConstListT = IConstList<ElementT>;
        using IForwardIteratorT = IForwardIterator<ElementT>;
        using BoxedForwardIteratorT = BoxedForwardIterator<ElementT>;
        using IEqualityComparerT = IEqualityComparer<ElementT>;
        using ArrayIteratorT = ArrayIterator<ElementT>;

        mpublic virtual const ElementT ref operator[](sizet index) const noexcept final override
        {
            return mArray[index];
        }

        mpublic virtual void ForEach(const IAction<const ElementT ref> ref callback) const final override
        {
            for (sizet i = 0; i < mCount; i++)
            {
                callback(mArray[i]);
            }
        }

        mpublic const ArrayIteratorT Begin() const noexcept
        {
            return ArrayIteratorT(mArray + 0);
        }

        mpublic const ArrayIteratorT End() const noexcept
        {
            return ArrayIteratorT(mArray + mCount);
        }

        mprotected BoxedForwardIteratorT mIterableBegin() noexcept final override
        {
            return BoxedForwardIteratorT(Begin());
        }

        mprotected const BoxedForwardIteratorT mIterableBegin() const noexcept final override
        {
            return BoxedForwardIteratorT(Begin());
        }

        mprotected BoxedForwardIteratorT mIterableEnd() noexcept final override
        {
            return BoxedForwardIteratorT(End());
        }

        mprotected const BoxedForwardIteratorT mIterableEnd() const noexcept final override
        {
            return BoxedForwardIteratorT(End());
        }

        /// ----------------------------------------------------------------------------
        /// @return Pointer to the underlying array.
        mpublic const ElementT ptr Data() const noexcept
        {
            return mArray;
        }

        mpublic virtual sizet FirstIndexOf(const ElementT ref element, const IEqualityComparerT ref comparer) const noexcept final override
        {
            for (sizet i = 0; i < mCount; i++)
            {
                if (comparer.Compare(mArray[i], element) is true)
                {
                    return i;
                }
            }

            return NPOS;
        }

        mpublic virtual sizet LastIndexOf(const ElementT ref element, const IEqualityComparerT ref comparer) const noexcept final override
        {
            for (sizet i = mCount; i >= 0; i--)
            {
                if (comparer.Compare(mArray[i], element) is true)
                {
                    return i;
                }
            }

            return NPOS;
        }

        mpublic virtual sizet Count() const noexcept final override
        {
            return mCount;
        }

        // *******************************************************************

        mprotected void mAssertIndexIsInBounds(const sizet index) const override final
        {
            IConstListT::mAssertIndexIsInBounds(index);
        }

        // *******************************************************************

        mprotected ElementT ptr mArray;
        mprotected sizet mCount;
    };
}