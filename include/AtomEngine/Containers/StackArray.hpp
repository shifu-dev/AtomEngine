#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/IArray.hpp"

namespace Atom
{
    /// @brief stack allocated non-resiable array
    /// @tparam TElement type of value stored in array
    /// @tparam TSize size of array, this cannot be changed
    template <typename TElement, sizet TSize>
    class StackArray : public IArray<TElement>
    {
        using ElementT = TElement;
        using IArrayT = IArray<TElement>;

        mpublic static constexpr sizet Size = TSize;

        mpublic StackArray() : IArrayT()
        {
            IArrayT::mArray = mStackArray;
            IArrayT::mCapacity = Size;
            IArrayT::mCount = 0;
        }

        mprotected ElementT mStackArray[Size];
    };
}