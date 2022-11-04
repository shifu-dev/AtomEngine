#pragma once
#include "SSEngine/Core.hpp"
#include "SSEngine/Containers/Comparer.hpp"
#include "SSEngine/Containers/Iterable.hpp"
#include "SSEngine/Containers/Collection.hpp"
#include "SSEngine/Containers/ArrayIterator.hpp"
#include <stdexcept>

namespace SSEngine
{
    /// @brief represents a collection that holds memory in contiguous order
    /// @tparam TElement type of element stored in array
    template <typename TElement>
    class Array : public virtual List<TElement>
    {
        using ElementT = TElement;
        using ForwardIteratorT = ForwardIterator<ElementT>;
        using EqualityComparerT = EqualityComparer<ElementT>;
        using PredicateT = Predicate<const ElementT lref, sizet>;
        using IteratorT = ArrayIterator<ElementT>;

    public:

        // *******************************************************************

        virtual const ElementT lref operator[](sizet index) const noexcept final override
        {
            return mArray[index];
        }

        virtual ElementT lref operator[](sizet index) noexcept final override
        {
            return mArray[index];
        }

        // *******************************************************************

        virtual void ForEach(const Callable<void(const ElementT lref)> lref callback) const final override
        {
            for (sizet i = 0; i < mCount; i++)
            {
                callback(mArray[i]);
            }
        }

        virtual void ForEach(const Callable<void(ElementT lref)> lref callback) final override
        {
            for (sizet i = 0; i < mCount; i++)
            {
                callback(mArray[i]);
            }
        }

        virtual IteratorT Begin() noexcept final override
        {
            return IteratorT(mArray + 0);
        }

        virtual const IteratorT Begin() const noexcept final override
        {
            return IteratorT(mArray + 0);
        }

        virtual IteratorT End() noexcept final override
        {
            return IteratorT(mArray + mCount);
        }

        virtual const IteratorT End() const noexcept final override
        {
            return IteratorT(mArray + mCount);
        }

        IteratorT begin() noexcept { return Begin(); }
        const IteratorT begin() const noexcept { return Begin(); }

        IteratorT end() noexcept { return End(); }
        const IteratorT end() const noexcept { return End(); }

    protected:
        virtual const ForwardIteratorPointerT Iterable_begin() const noexcept override
        {
            return ForwardIteratorPointerT(Begin());
        }

        virtual ForwardIteratorPointerT Iterable_begin() noexcept override
        {
            return ForwardIteratorPointerT(Begin());
        }

        virtual const ForwardIteratorPointerT Iterable_end() const noexcept override
        {
            return ForwardIteratorPointerT(End());
        }

        virtual ForwardIteratorPointerT Iterable_end() noexcept override
        {
            return ForwardIteratorPointerT(End());
        }

    public:
        // *******************************************************************

        virtual ElementT lref ElementAt(const sizet index) final override
        {
            AssertIndex(index);

            return mArray[index];
        }

        virtual const ElementT lref ElementAt(const sizet index) const final override
        {
            AssertIndex(index);

            return mArray[index];
        }

        // *******************************************************************

        ElementT ptr RawData() noexcept
        {
            return mArray;
        }

        const ElementT ptr RawData() const noexcept
        {
            return mArray;
        }

        // *******************************************************************

        virtual sizet FirstIndexOf(const ElementT lref element, const EqualityComparerT lref comparer) const final override
        {
            for (sizet i = 0; i < mCount; i++)
            {
                if (comparer.Compare(mArray[i], element) iseq true)
                {
                    return i;
                }
            }

            return NPOS;
        }

        virtual sizet LastIndexOf(const ElementT lref element, const EqualityComparerT lref comparer) const final override
        {
            for (sizet i = mCount; i >= 0; i--)
            {
                if (comparer.Compare(mArray[i], element) iseq true)
                {
                    return i;
                }
            }

            return NPOS;
        }

        // *******************************************************************

        virtual sizet Count() const noexcept final override
        {
            return mCount;
        }

        // *******************************************************************

        virtual void InsertAt(const sizet index, const ElementT lref element) final override
        {
            AssertIndex(index);
            AssertCapacityFor(1);

            for (sizet i = mCount; i >= index; i--)
            {
                std::swap(mArray[i], mArray[i - 1]);
            }

            mCount++;
            mArray[index] = element;
        }

        virtual void InsertBack(const ElementT lref element) final override
        {
            AssertCapacityFor(1);
            mArray[mCount] = element;
            mCount++;
        }

        virtual void RemoveBack() final override
        {
            AssertIndex(0);

            mArray[mCount] = ElementT();
            mCount--;
        }

        // *******************************************************************

        virtual void InsertAt(const sizet index, const ForwardIteratorT lref it, const sizet count) final override
        {
            AssertIndex(index);
            AssertCapacityFor(count);

            for (sizet i = mCount; i >= index; i--)
            {
                std::swap(mArray[i], mArray[i + count]);
            }

            mCount += count;
            for (sizet i = index; i < count; i++)
            {
                mArray[index] = ptr it;
                it++;
            }
        }

        // *******************************************************************

        virtual void RemoveAt(const sizet index) final override
        {
            AssertIndex(index);

            for (sizet i = index; i < mCount; i++)
            {
                std::swap(mArray[i], mArray[i + 1]);
            }

            mArray[mCount] = ElementT();
            mCount--;
        }

        // *******************************************************************

        virtual void RemoveFrom(const sizet from, const sizet to) final override
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

        virtual void RemoveIfCallable(const PredicateT lref pred) noexcept final override
        {
            sizet count = mCount;
            for (sizet i = 0; i < count; i++)
            {
                if (pred(mArray[i], sizet(i)) iseq true)
                {
                    RemoveAt(i);

                    i--;
                    count--;
                }
            }
        }

        // *******************************************************************
    protected:

        void AssertIndex(const sizet index) const
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
        void AssertCapacityFor(const sizet count)
        {
            if (mCount >= mCapacity)
            {
                throw std::runtime_error("could not allocate memory for " + (mCount + 1));
            }
        }

        // *******************************************************************

    protected:
        ElementT ptr mArray;
        sizet mCapacity;
        sizet mCount;
    };
}