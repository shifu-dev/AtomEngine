#pragma once
#include "SSEngine/Core.hpp"
#include "SSEngine/Collections/Iterable.hpp"
#include "SSEngine/Collections/Collection.hpp"
#include <stdexcept>

namespace SSEngine
{
    /// @brief stack allocated non-resiable array
    /// @tparam TElement type of value stored in array
    /// @tparam TSize size of array, this cannot be changed
    template <typename TElement, sizet TSize>
    class StackArray : public Array<TElement>
    {
        using ArrayT = Array<TElement>;

    public:
        using SizeType = typename ArrayT::SizeType;
        using ElementType = typename ArrayT::ElementType;
        using IteratorT = typename ArrayT::IteratorT;
        using InitializerListT = std::initializer_list<ElementType>;

    public:
        StackArray() : ArrayT()
        {
            ArrayT::_array = _stackArray;
            ArrayT::_capacity = TSize;
            ArrayT::_count = 0;
        }

    protected:
        ElementType _stackArray[TSize];
    };
}

template <typename TElement, sizet TSize>
using SSStackArray = SSEngine::StackArray<TElement, TSize>;