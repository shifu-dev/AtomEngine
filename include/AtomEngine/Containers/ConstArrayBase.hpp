#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/IConstArray.hpp"

namespace Atom
{
    template <typename TElement>
    class ConstArrayBase : public virtual IConstArray<TElement>
    {
        using ElementT = TElement;                                          ///< ----
        using BoxedForwardIteratorT = BoxedForwardIterator<ElementT>;       ///< ----
        using IEqualityComparerT = IEqualityComparer<ElementT>;             ///< ----
        using ArrayIteratorT = ArrayIterator<ElementT>;                     ///< ----

        // *******************************************************************
        // * IConstArray

        /// ----------------------------------------------------------------------------
        /// @return Pointer to the underlying array.
        mpublic virtual const ElementT ptr Data() const noexcept override final
        {
            return mArray;
        }

        mpublic virtual const ArrayIteratorT Begin() const noexcept override final
        {
            return ArrayIteratorT(mArray + 0);
        }

        mpublic virtual const ArrayIteratorT End() const noexcept override final
        {
            return ArrayIteratorT(mArray + mCount);
        }

        // *******************************************************************
        // * IConstList

        mpublic virtual const ElementT ref operator[](const sizet index) const noexcept override final
        {
            return mArray[index];
        }

        mpublic virtual sizet FirstIndexOf(const ElementT ref element, const IEqualityComparerT ref comparer) const noexcept override final
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

        mpublic virtual sizet LastIndexOf(const ElementT ref element, const IEqualityComparerT ref comparer) const noexcept override final
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

        mprotected virtual void mAssertIndexIsInBounds(const sizet index) const override final
        {
            mAssertIndexIsInBounds(index, "Index was out of range");
        }

        mprotected virtual void mAssertIndexIsInBounds(const sizet index, const char ptr msg) const
        {
            if (index >= mCount)
            {
                throw std::out_of_range("Index was out of range");
            }
        }

        // *******************************************************************
        // * IConstCollection

        mpublic virtual sizet Count() const noexcept override final
        {
            return mCount;
        }

        // *******************************************************************
        // * IIterable

        mpublic virtual void ForEach(const IAction<const ElementT ref> ref callback) const override final
        {
            for (sizet i = 0; i < mCount; i++)
            {
                callback(mArray[i]);
            }
        }

        mprotected const BoxedForwardIteratorT mIterableBegin() const noexcept override final
        {
            return BoxedForwardIteratorT(Begin());
        }

        mprotected const BoxedForwardIteratorT mIterableEnd() const noexcept override final
        {
            return BoxedForwardIteratorT(End());
        }

        // *******************************************************************

        mprotected ElementT ptr mArray;
        mprotected sizet mCount;       
    };
}