#pragma once
#include "SSEngine/Core.hpp"
#include "SSEngine/Containers/Array.hpp"
#include <stdexcept>

namespace SSEngine
{
    /// @brief stack allocated non-resiable array
    /// @tparam TElement type of value stored in array
    /// @tparam TSize size of array, this cannot be changed
    template <typename TElement, sizet TSize>
    class StackArray : public Array<TElement>
    {
        using ElementT = TElement;
        using ArrayT = Array<TElement>;

    public:
        static constexpr sizet Size = TSize;

    public:
        StackArray() : ArrayT()
        {
            ArrayT::mArray = mStackArray;
            ArrayT::mCapacity = Size;
            ArrayT::mCount = 0;
        }

    protected:
        ElementT mStackArray[Size];
    };
}