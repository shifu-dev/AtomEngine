#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/Comparer.hpp"
#include "AtomEngine/Containers/Iterable.hpp"
#include "AtomEngine/Containers/Collection.hpp"
#include "AtomEngine/Containers/ArrayIterator.hpp"

namespace Atom
{
    /// @brief represents a collection that holds memory in contiguous order
    /// @tparam TElement type of element stored in array
    template <typename TElement>
    class Array : public virtual List<TElement>
    {
        using ElementT = TElement;
        using ForwardIteratorT = ForwardIterator<ElementT>;
        using BoxedForwardIteratorT = BoxedForwardIterator<ElementT>;
        using EqualityComparerT = EqualityComparer<ElementT>;
        using PredicateT = Predicate<const ElementT ref, sizet>;
        using IteratorT = ArrayIterator<ElementT>;

        // *******************************************************************

        mpublic virtual const ElementT ref operator[](sizet index) const noexcept final override
        {
            return mArray[index];
        }

        mpublic virtual ElementT ref operator[](sizet index) noexcept final override
        {
            return mArray[index];
        }

        // *******************************************************************

        mpublic virtual void ForEach(const Callable<void(const ElementT ref)> ref callback) const final override
        {
            for (sizet i = 0; i < mCount; i++)
            {
                callback(mArray[i]);
            }
        }

        mpublic virtual void ForEach(const Callable<void(ElementT ref)> ref callback) final override
        {
            for (sizet i = 0; i < mCount; i++)
            {
                callback(mArray[i]);
            }
        }

        mpublic virtual IteratorT Begin() noexcept final override
        {
            return IteratorT(mArray + 0);
        }

        mpublic virtual const IteratorT Begin() const noexcept final override
        {
            return IteratorT(mArray + 0);
        }

        mpublic virtual IteratorT End() noexcept final override
        {
            return IteratorT(mArray + mCount);
        }

        mpublic virtual const IteratorT End() const noexcept final override
        {
            return IteratorT(mArray + mCount);
        }

        mpublic IteratorT begin() noexcept { return Begin(); }
        mpublic const IteratorT begin() const noexcept { return Begin(); }

        mpublic IteratorT end() noexcept { return End(); }
        mpublic const IteratorT end() const noexcept { return End(); }

        mprotected virtual const BoxedForwardIteratorT Iterable_begin() const noexcept override
        {
            return BoxedForwardIteratorT(Begin());
        }

        mprotected virtual BoxedForwardIteratorT Iterable_begin() noexcept override
        {
            return BoxedForwardIteratorT(Begin());
        }

        mprotected virtual const BoxedForwardIteratorT Iterable_end() const noexcept override
        {
            return BoxedForwardIteratorT(End());
        }

        mprotected virtual BoxedForwardIteratorT Iterable_end() noexcept override
        {
            return BoxedForwardIteratorT(End());
        }

        // *******************************************************************

        mpublic virtual ElementT ref ElementAt(const sizet index) final override
        {
            AssertIndex(index);

            return mArray[index];
        }

        mpublic virtual const ElementT ref ElementAt(const sizet index) const final override
        {
            AssertIndex(index);

            return mArray[index];
        }

        // *******************************************************************

        mpublic ElementT ptr RawData() noexcept
        {
            return mArray;
        }

        mpublic const ElementT ptr RawData() const noexcept
        {
            return mArray;
        }

        // *******************************************************************

        mpublic virtual sizet FirstIndexOf(const ElementT ref element, const EqualityComparerT ref comparer) const final override
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

        mpublic virtual sizet LastIndexOf(const ElementT ref element, const EqualityComparerT ref comparer) const final override
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

        // *******************************************************************

        mpublic virtual sizet Count() const noexcept final override
        {
            return mCount;
        }

        // *******************************************************************

        mpublic virtual void InsertAt(const sizet index, const ElementT ref element) final override
        {
            AssertIndex(index);
            AssertCapacityFor(1);

            for (sizet i = mCount; i >= index; i--)
            {
                swap(mArray[i], mArray[i - 1]);
            }

            mCount++;
            mArray[index] = element;
        }

        mpublic virtual void InsertBack(const ElementT ref element) final override
        {
            AssertCapacityFor(1);
            mArray[mCount] = element;
            mCount++;
        }

        mpublic virtual void RemoveBack() final override
        {
            AssertIndex(0);

            mArray[mCount] = ElementT();
            mCount--;
        }

        // *******************************************************************

        mpublic virtual void InsertAt(const sizet index, const ForwardIteratorT ref it, const sizet count) final override
        {
            AssertIndex(index);
            AssertCapacityFor(count);

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
            AssertIndex(index);

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

        mprotected void AssertIndex(const sizet index) const
        {
            if (index > (mCount - 1))
            {
                throw std::out_of_range("index was out of range");
            }
        }

        /// @brief checks capcity and resizes if required
        /// @param count count of elements to insert
        /// @note this function is called every time any number
        /// of elements are to be inserted irrelevance of their position
        mprotected void AssertCapacityFor(const sizet count)
        {
            if (mCount >= mCapacity)
            {
                throw std::runtime_error("could not allocate memory for " + (mCount + 1));
            }
        }

        // *******************************************************************

        mprotected ElementT ptr mArray;
        mprotected sizet mCapacity;
        mprotected sizet mCount;
    };
}