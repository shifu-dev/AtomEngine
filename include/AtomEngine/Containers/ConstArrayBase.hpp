#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/IConstArray.hpp"

namespace Atom
{
    template <typename TElement>
    class ConstArrayBase : public virtual IConstArray<TElement>
    {
        using ElementT = TElement;                                          ///< ----
        using IConstListT = IConstList<TElement>;                           ///< ----
        using ForwardIteratorBoxT = ForwardIteratorBox<ElementT>;       ///< ----
        using IEqualityComparerT = IEqualityComparer<ElementT>;             ///< ----
        using ConstForEachActionT = const ILoopAction<const ElementT ref>;  ///< ----
        using ArrayIteratorT = ArrayIterator<ElementT>;                     ///< ----

        // *******************************************************************
        // * IConstArray

        /// ----------------------------------------------------------------------------
        /// @return Pointer to the underlying array.
        mpublic virtual const ElementT ptr Data() const noexcept final
        {
            return mArray;
        }

        mpublic virtual const ArrayIteratorT Begin() const noexcept final
        {
            return ArrayIteratorT(mArray + 0);
        }

        mpublic virtual const ArrayIteratorT End() const noexcept final
        {
            return ArrayIteratorT(mArray + mCount);
        }

        // *******************************************************************
        // * IConstList

        mpublic virtual const ElementT ref operator[](const sizet index) const noexcept final
        {
            return mArray[index];
        }

        mpublic using IConstListT::FirstIndexOf;

        mpublic virtual sizet FirstIndexOf(const ElementT ref element, const IEqualityComparerT ref comparer) const noexcept final
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

        mpublic using IConstListT::LastIndexOf;

        mpublic virtual sizet LastIndexOf(const ElementT ref element, const IEqualityComparerT ref comparer) const noexcept final
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

        mprotected virtual void mAssertIndexIsInBounds(const sizet index) const final
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

        mpublic virtual sizet Count() const noexcept final
        {
            return mCount;
        }

        // *******************************************************************
        // * IIterable

        mpublic virtual void ForEach(ConstForEachActionT& callback) const final
        {
            for (sizet i = 0; i < mCount; i++)
            {
                callback(mArray[i]);
            }
        }

        mprotected const ForwardIteratorBoxT mIterableBegin() const noexcept final
        {
            return ForwardIteratorBoxT(Begin());
        }

        mprotected const ForwardIteratorBoxT mIterableEnd() const noexcept final
        {
            return ForwardIteratorBoxT(End());
        }

        // *******************************************************************

        mprotected ElementT ptr mArray;
        mprotected sizet mCount;       
    };
}