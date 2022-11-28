#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/IConstArray.hpp"
#include "AtomEngine/Containers/IList.hpp"

namespace Atom
{
    /// Represents a collection that holds memory in contiguous order.
    /// 
    /// @tparam TElement Type of element this array contains.
    template <typename TElement>
    interface IArray : public virtual IConstArray<TElement>, public virtual IList<TElement>
    {
        using ElementT = TElement;
        using IConstArrayT = IConstArray<ElementT>;
        using IPredicateT = IPredicate<const ElementT ref, sizet>;
        using IForwardIteratorT = IForwardIterator<ElementT>;
        using ArrayIteratorT = ArrayIterator<ElementT>;

        mprotected using IConstArrayT::mAssertIndexIsInBounds;
        mprotected using IConstArrayT::mArray;
        mprotected using IConstArrayT::mCount;

        // *******************************************************************

        mpublic virtual ElementT ref operator[](sizet index) noexcept final override
        {
            return mArray[index];
        }

        // *******************************************************************

        mpublic virtual void ForEach(const IAction<ElementT ref> ref callback) final override
        {
            for (sizet i = 0; i < mCount; i++)
            {
                callback(mArray[i]);
            }
        }

        mpublic ArrayIteratorT Begin() noexcept
        {
            return ArrayIteratorT(mArray + 0);
        }

        mpublic ArrayIteratorT End() noexcept
        {
            return ArrayIteratorT(mArray + mCount);
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

        mpublic virtual void InsertAt(const sizet index, const IForwardIteratorT ref it, const sizet count) final override
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

        mpublic virtual void RemoveIfCallable(const IPredicateT ref pred) noexcept final override
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