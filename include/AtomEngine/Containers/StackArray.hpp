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
        using ElementT = TElement;
        using ArrayBaseT = ArrayBase<TElement>;

        mpublic static constexpr sizet Size = TSize;

        mpublic StackArray() : ArrayBaseT()
        {
            ArrayBaseT::mArray = mStackArray;
            ArrayBaseT::mCapacity = Size;
            ArrayBaseT::mCount = 0;
        }

        mprotected ElementT mStackArray[Size];
    };
}