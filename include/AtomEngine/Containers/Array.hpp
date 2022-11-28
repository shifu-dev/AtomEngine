#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/ConstArray.hpp"
#include "AtomEngine/Containers/List.hpp"

namespace Atom
{
    /// Represents a collection that holds memory in contiguous order.
    /// 
    /// @tparam TElement Type of element this array contains.
    template <typename TElement>
    class Array : public virtual ConstArray<TElement>, public virtual List<TElement>
    {
        using ElementT = TElement;
        using ConstArrayT = ConstArray<ElementT>;
        using ConstListT = ConstList<ElementT>;
        using ForwardIteratorT = ForwardIterator<ElementT>;
        using BoxedForwardIteratorT = BoxedForwardIterator<ElementT>;
        using EqualityComparerT = EqualityComparer<ElementT>;
        using PredicateT = Predicate<const ElementT ref, sizet>;
        using IteratorT = ArrayIterator<ElementT>;

        mprotected using ConstArrayT::mAssertIndexIsInBounds;
        mprotected using ConstArrayT::mArray;
        mprotected using ConstArrayT::mCount;

        // *******************************************************************

        mpublic virtual ElementT ref operator[](sizet index) noexcept final override
        {
            return mArray[index];
        }

        // *******************************************************************

        mpublic virtual void ForEach(const Action<ElementT ref> ref callback) final override
        {
            for (sizet i = 0; i < mCount; i++)
            {
                callback(mArray[i]);
            }
        }

        mpublic IteratorT Begin() noexcept
        {
            return IteratorT(mArray + 0);
        }

        mpublic IteratorT End() noexcept
        {
            return IteratorT(mArray + mCount);
        }

        // *******************************************************************

        /// @{ ----------------------------------------------------------------------------
        /// @return Pointer to the underlying array.
        mpublic ElementT ptr Data() noexcept
        {
            return mArray;
        }

        // *******************************************************************

        mpublic virtual void InsertAt(const sizet index, const ElementT ref element) final override
        {
            mAssertIndexIsInBounds(index);
            mAssertCapacityFor(1);

            for (sizet i = mCount; i >= index; i--)
            {
                swap(mArray[i], mArray[i - 1]);
            }

            mCount++;
            mArray[index] = element;
        }

        mpublic virtual void InsertBack(const ElementT ref element) final override
        {
            mAssertCapacityFor(1);
            mArray[mCount] = element;
            mCount++;
        }

        mpublic virtual void RemoveBack() final override
        {
            mAssertIndexIsInBounds(0);

            mArray[mCount] = ElementT();
            mCount--;
        }

        // *******************************************************************

        mpublic virtual void InsertAt(const sizet index, const ForwardIteratorT ref it, const sizet count) final override
        {
            mAssertIndexIsInBounds(index);
            mAssertCapacityFor(count);

            for (sizet i = mCount; i >= index; i--)
            {
                swap(mArray[i], mArray[i + count]);
            }

            mCount += count;
            for (sizet i = index; i < count; i++)
            {
                mArray[index] = ptr it;
                it++;
            }
        }

        // *******************************************************************

        mpublic virtual void RemoveAt(const sizet index) final override
        {
            mAssertIndexIsInBounds(index);

            for (sizet i = index; i < mCount; i++)
            {
                swap(mArray[i], mArray[i + 1]);
            }

            mArray[mCount] = ElementT();
            mCount--;
        }

        // *******************************************************************

        mpublic virtual void RemoveFrom(const sizet from, const sizet to) final override
        {
            const sizet count = to - from;
            for (sizet i = from; i < (mCount - count); i++)
            {
                mArray[i] = mArray[i + count];
            }

            for (sizet i = (mCount - count); i < mCount; i++)
            {
                mArray[i] = ElementT();
            }
            mCount -= count;
        }

        // *******************************************************************

        mpublic virtual void RemoveIfCallable(const PredicateT ref pred) noexcept final override
        {
            sizet count = mCount;
            for (sizet i = 0; i < count; i++)
            {
                if (pred(mArray[i], sizet(i)) is true)
                {
                    RemoveAt(i);

                    i--;
                    count--;
                }
            }
        }

        // *******************************************************************

        /// @brief checks capcity and resizes if required
        /// @param count count of elements to insert
        /// @note this function is called every time any number
        /// of elements are to be inserted irrelevance of their position
        mprotected void mAssertCapacityFor(const sizet count)
        {
            if (mCount >= mCapacity)
            {
                throw std::runtime_error("could not allocate memory for " + (mCount + 1));
            }
        }

        // *******************************************************************

        mprotected sizet mCapacity;
    };
}