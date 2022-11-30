#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/ArrayBase.hpp"

namespace Atom
{
    /// @brief stack allocated non-resiable array
    /// @tparam TElement type of value stored in array
    /// @tparam TSize size of array, this cannot be changed
    template <typename TElement, sizet TSize>
    class StackArray : public ArrayBase<TElement>
    {
        using ThisT = StackArray<TElement, TSize>;
        using BaseT = ArrayBase<TElement>;
        using ElementT = TElement;

        mprotected using BaseT::mArray;
        mprotected using BaseT::mCount;
        mprotected using BaseT::mCapacity;

        // *******************************************************************
        // * Constructors and Destructors

        mpublic StackArray() noexcept : BaseT()
        {
            mArray = mStackArray;
            mCapacity = TSize;
            mCount = 0;
        }

        // *******************************************************************

        mprotected ElementT mStackArray[TSize];
    };
}