#pragma once
#include "SSEngine/Core.hpp"
#include "SSEngine/Collections/Iterable.hpp"
#include "SSEngine/Collections/Collection.hpp"
#include <stdexcept>

namespace SSEngine
{
    /// @brief stack allocated non-resiable array
    /// @tparam TValueType type of value stored in array
    /// @tparam TSize size of array, this cannot be changed
    template <typename TValueType, sizet TSize>
    class StackArray : public Array<TValueType>
    {
        using ArrayT = Array<TValueType>;

    public:
        using SizeT = typename ArrayT::SizeT;
        using ValueTypeT = typename ArrayT::ValueTypeT;
        using IteratorT = typename ArrayT::IteratorT;
        using InitializerListT = std::initializer_list<ValueTypeT>;

    public:
        constexpr StackArray() : ArrayT() { }

    protected:
        TValueType _stackArray[TSize];
    };
}

template <typename TValueType, sizet TSize>
using SSStackArray = SSEngine::StackArray<TValueType, TSize>;