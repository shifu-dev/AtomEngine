#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/IArray.hpp"
#include "AtomEngine/Containers/ConstArrayBase.hpp"

namespace Atom
{
    /// Represents a collection that holds memory in contiguous order.
    /// 
    /// @tparam TElement Type of element this array contains.
    template <typename TElement>
    class ArrayBase : public ConstArrayBase<TElement>,
        public virtual IArray<TElement>
    {
        using ElementT = TElement;                                      ///< ----
        using IPredicateT = IPredicate<const ElementT ref, sizet>;      ///< ----
        using IForwardIteratorT = IForwardIterator<ElementT>;           ///< ----
        using BoxedForwardIteratorT = BoxedForwardIterator<ElementT>;   ///< ----
        using ArrayIteratorT = ArrayIterator<ElementT>;                 ///< ----

        mprotected using ConstArrayBase<TElement>::mAssertIndexIsInBounds;

        // *******************************************************************

        /// @brief checks capcity and resizes if required
        /// @param count count of elements to insert
        /// @note this function is called every time any number
        /// of elements are to be inserted irrelevance of their position
        mprotected void mAssertCapacityFor(const sizet count) const
        {
            if (mCount >= mCapacity)
            {
                throw std::runtime_error("could not allocate memory for " + (mCount + 1));
            }
        }

        // *******************************************************************
        // * IArray

        /// ----------------------------------------------------------------------------
        /// @return Pointer to the underlying array.
        mpublic virtual ElementT ptr Data() noexcept override final
        {
            return mArray;
        }

        mpublic virtual ArrayIteratorT Begin() noexcept override final
        {
            return ArrayIteratorT(mArray + 0);
        }

        mpublic virtual ArrayIteratorT End() noexcept override final
        {
            return ArrayIteratorT(mArray + mCount);
        }

        // *******************************************************************
        // * IList

        mpublic virtual ElementT ref operator[](const sizet index) noexcept override final
        {
            return mArray[index];
        }

        mpublic virtual void InsertAt(const sizet index, const ElementT ref element) override final
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

        mpublic virtual void InsertBack(const ElementT ref element) override final
        {
            mAssertCapacityFor(1);
            mArray[mCount] = element;
            mCount++;
        }

        mpublic virtual void RemoveBack() override final
        {
            mAssertIndexIsInBounds(0);

            mArray[mCount] = ElementT();
            mCount--;
        }

        mpublic virtual void InsertAt(const sizet index, const IForwardIteratorT ref it, const sizet count) override final
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

        mpublic virtual void RemoveAt(const sizet index) override final
        {
            mAssertIndexIsInBounds(index);

            for (sizet i = index; i < mCount; i++)
            {
                swap(mArray[i], mArray[i + 1]);
            }

            mArray[mCount] = ElementT();
            mCount--;
        }

        mpublic virtual void RemoveFrom(const sizet from, const sizet to) override final
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

        mpublic virtual void RemoveIfCallable(const IPredicateT ref pred) noexcept override final
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
        // * IITerable

        mpublic virtual void ForEach(const IAction<ElementT ref> ref callback) override final
        {
            for (sizet i = 0; i < mCount; i++)
            {
                callback(mArray[i]);
            }
        }

        mprotected BoxedForwardIteratorT mIterableBegin() noexcept override final
        {
            return BoxedForwardIteratorT(Begin());
        }

        mprotected BoxedForwardIteratorT mIterableEnd() noexcept override final
        {
            return BoxedForwardIteratorT(End());
        }

        // *******************************************************************

        mprotected ElementT ptr mArray;
        mprotected sizet mCount;
        mprotected sizet mCapacity;
    };
}