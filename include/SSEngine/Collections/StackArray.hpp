#pragma once
#include "SSEngine/Core.hpp"
#include "SSEngine/Collections/Array.hpp"
#include "SSEngine/Collections/ContainerDefination.hpp"
#include <stdexcept>

namespace SSEngine
{
    /// @brief stack allocated non-resiable array
    /// @tparam TElement type of value stored in array
    /// @tparam TSize size of array, this cannot be changed
    template <typename TElement, sizet TSize>
    class StackArray : public Array<TElement>
    {
        using ContainerDefinationT = ContainerDefination<TElement>;
        using ArrayT = typename ContainerDefinationT::ArrayT;
        using SizeT = typename ContainerDefinationT::SizeT;
        using ElementT = typename ContainerDefinationT::ElementT;
        using IteratorT = typename ContainerDefinationT::IteratorT;
        using InitializerListT = typename ContainerDefinationT::InitializerListT;

    public:
        using SizeType = SizeT;
        using ElementType = ElementT;
        using IteratorType = typename ArrayT::IteratorType;
        static constexpr SizeT Size = TSize;

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