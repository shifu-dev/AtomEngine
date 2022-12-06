#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/IDynamicArray.hpp"
#include "AtomEngine/Containers/ArrayBase.hpp"

namespace Atom
{
    template <typename TElement>
    class DynamicArray : public ArrayBase<TElement>,
        public virtual IDynamicArray<TElement>
    {
        using ElementT = TElement;                                               ///< ----
        using ThisT = DynamicArray<TElement>;                                    ///< ----
        using BaseT = ArrayBase<TElement>;                                       ///< ----
        using IDynamicArrayT = IDynamicArray<TElement>;                          ///< ----
        using InitializerListT = InitializerList<TElement>;                      ///< ----
        using IForwardIteratorT = IForwardIterator<ElementT>;                    ///< ----
        using IConstIterableT = IConstIterable<ElementT>;                        ///< ----
        using IConstCollectionT = IConstCollection<ElementT>;                    ///< ----

        mpublic using BaseT::Clear;
        mprotected using BaseT::mArray;
        mprotected using BaseT::mCount;
        mprotected using BaseT::mCapacity;

        // *******************************************************************
        // * Constructors and Destructors

        mpublic DynamicArray() noexcept :
            mAllocator(DefaultAllocatorInstance)
        {
            mArray = null;
            mCount = 0;
            mCapacity = 0;
        }

        mpublic DynamicArray(const sizet count) : ThisT()
        {
            Resize(count);
        }

        mpublic DynamicArray(const InitializerListT list) : ThisT()
        {
            InsertFront(list);
        }

        mpublic DynamicArray(const IForwardIteratorT ref it, const sizet count) : ThisT()
        {
            InsertFront(it, count);
        }

        mpublic DynamicArray(const IForwardIteratorT ref begin, const IForwardIteratorT ref end) : ThisT()
        {
            InsertFront(begin, end);
        }

        mpublic DynamicArray(const IConstIterableT ref elements, const sizet count) : ThisT()
        {
            InsertFront(elements, count);
        }

        mpublic DynamicArray(const IConstIterableT ref elements) : ThisT()
        {
            InsertFront(elements);
        }

        mpublic DynamicArray(const IConstCollectionT ref elements) : ThisT()
        {
            InsertFront(elements);
        }

        mpublic DynamicArray(const ThisT ref other) noexcept = default;
        mpublic DynamicArray(ThisT rref other) noexcept = default;

        mpublic ThisT ref operator = (const ThisT ref other) noexcept = default;
        mpublic ThisT ref operator = (ThisT rref other) noexcept = default;

        mpublic dtor DynamicArray()
        {
            Clear();
            ShrinkToFit();
        }

        // *******************************************************************
        // * IDynamicCollection

        mpublic virtual void Resize(const sizet count) final
        {
            sizet checkedCount = max(count, mCount);

            if (checkedCount != mCapacity)
            {
                mArray = mAllocator.Reallocate<ElementT>(mArray, checkedCount);
            }
        }

        mpublic virtual sizet Reserve(const sizet count) final
        {
            if (mCapacity - mCount < count)
            {
                mAllocator.Reallocate<ElementT>(mArray, mCapacity - mCount + count);
            }

            return mCapacity - mCount;
        }

        mpublic virtual void ShrinkToFit() final
        {
            return Resize(mCount);
        }

        // *******************************************************************

        mprotected IAllocator ref mAllocator;
    };
}