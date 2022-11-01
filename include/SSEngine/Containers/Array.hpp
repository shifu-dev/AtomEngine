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
    class Array : public virtual List<TElement>, public virtual IteratorIterable<ArrayIterator<TElement>>
    {
        using ContainerDefinationT = ContainerDefination<TElement>;
        using SizeT = typename ContainerDefinationT::SizeT;
        using ElementT = typename ContainerDefinationT::ElementT;
        using IterableT = typename ContainerDefinationT::IterableT;
        using CollectionT = typename ContainerDefinationT::CollectionT;
        using ListT = typename ContainerDefinationT::ListT;
        using ForwardIteratorT = typename ContainerDefinationT::ForwardIteratorT;
        using ArrayIteratorT = typename ContainerDefinationT::ArrayIteratorT;
        using IteratorPointerT = typename ContainerDefinationT::IteratorPointerT;
        using ComparerT = typename ContainerDefinationT::ComparerT;
        using EqualityComparerT = typename ContainerDefinationT::EqualityComparerT;
        static const sizet NPOS = ContainerDefinationT::NPOS;

        using PredicateT = Predicate<const ElementT lref, SizeT>;

    public:
        using SizeType = SizeT;
        using ElementType = ElementT;
        using IteratorType = ArrayIterator<TElement>;

    public:

        // *******************************************************************

    public:

        // *******************************************************************

        virtual const ElementT lref operator[](SizeT index) const noexcept final override
        {
            return mArray[index];
        }

        virtual ElementT lref operator[](SizeT index) noexcept final override
        {
            return mArray[index];
        }

        // *******************************************************************

        virtual void ForEach(const Callable<void(const ElementT lref)> lref callback) const final override
        {
            for (SizeT i = 0; i < mCount; i++)
            {
                callback(mArray[i]);
            }
        }

        virtual void ForEach(const Callable<void(ElementT lref)> lref callback) final override
        {
            for (SizeT i = 0; i < mCount; i++)
            {
                callback(mArray[i]);
            }
        }

        virtual IteratorType Begin() noexcept final override
        {
            return IteratorType(mArray + 0);
        }

        virtual const IteratorType Begin() const noexcept final override
        {
            return IteratorType(mArray + 0);
        }

        virtual IteratorType End() noexcept final override
        {
            return IteratorType(mArray + mCount);
        }

        virtual const IteratorType End() const noexcept final override
        {
            return IteratorType(mArray + mCount);
        }

        // *******************************************************************

        virtual ElementT lref ElementAt(const SizeT index) final override
        {
            AssertIndex(index);

            return mArray[index];
        }

        virtual const ElementT lref ElementAt(const SizeT index) const final override
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

        virtual SizeT FirstIndexOf(const ElementT lref element, const EqualityComparerT lref comparer) const final override
        {
            for (SizeT i = 0; i < mCount; i++)
            {
                if (comparer.Compare(mArray[i], element) iseq true)
                {
                    return i;
                }
            }

            return NPOS;
        }

        virtual SizeT LastIndexOf(const ElementT lref element, const EqualityComparerT lref comparer) const final override
        {
            for (SizeT i = mCount; i >= 0; i--)
            {
                if (comparer.Compare(mArray[i], element) iseq true)
                {
                    return i;
                }
            }

            return NPOS;
        }

        // *******************************************************************

        virtual SizeT Count() const noexcept final override
        {
            return mCount;
        }

        // *******************************************************************

        virtual void InsertAt(const SizeT index, const ElementT lref element) final override
        {
            AssertIndex(index);
            AssertCapacityFor(1);

            for (SizeT i = mCount; i >= index; i--)
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

        virtual void InsertAt(const SizeT index, const ForwardIteratorT lref it, const SizeT count) final override
        {
            AssertIndex(index);
            AssertCapacityFor(count);

            for (SizeT i = mCount; i >= index; i--)
            {
                std::swap(mArray[i], mArray[i + count]);
            }

            mCount += count;
            for (SizeT i = index; i < count; i++)
            {
                mArray[index] = ptr it;
                it++;
            }
        }

        // *******************************************************************

        virtual void RemoveAt(const SizeT index) final override
        {
            AssertIndex(index);

            for (SizeT i = index; i < mCount; i++)
            {
                std::swap(mArray[i], mArray[i + 1]);
            }

            mArray[mCount] = ElementT();
            mCount--;
        }

        // *******************************************************************

        virtual void RemoveFrom(const SizeT from, const SizeT to) final override
        {
            const SizeT count = to - from;
            for (SizeT i = from; i < (mCount - count); i++)
            {
                mArray[i] = mArray[i + count];
            }

            for (SizeT i = (mCount - count); i < mCount; i++)
            {
                mArray[i] = ElementT();
            }
            mCount -= count;
        }

        // *******************************************************************

        virtual void RemoveIfCallable(const PredicateT lref pred) noexcept final override
        {
            SizeT count = mCount;
            for (SizeT i = 0; i < count; i++)
            {
                if (pred(mArray[i], SizeT(i)) iseq true)
                {
                    RemoveAt(i);

                    i--;
                    count--;
                }
            }
        }

        // *******************************************************************
    protected:

        void AssertIndex(const SizeT index) const
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
        void AssertCapacityFor(const SizeT count)
        {
            if (mCount >= mCapacity)
            {
                throw std::runtime_error("could not allocate memory for " + (mCount + 1));
            }
        }

        // *******************************************************************

    protected:
        ElementT ptr mArray;
        SizeT mCapacity;
        SizeT mCount;
    };
}