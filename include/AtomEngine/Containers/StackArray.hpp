#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/ArrayBase.hpp"

namespace Atom
{
    /// @brief stack allocated non-resiable array
    /// @tparam ElementT type of value stored in array
    /// @tparam TSize size of array, this cannot be changed
    template <typename ElementT, sizet TSize>
    class StackArray: public ArrayBase<ElementT>
    {
        using ThisT = StackArray<ElementT, TSize>;
        using BaseT = ArrayBase<ElementT>;

    /// ----------------------------------------------------------------------------
    public:
        StackArray() noexcept:
            BaseT()
        {
            _array = _stackArray;
            _capacity = TSize;
            _count = 0;
        }

    /// ----------------------------------------------------------------------------
    protected:
        using BaseT::_array;
        using BaseT::_count;
        using BaseT::_capacity;

        ElementT _stackArray[TSize];
    };
}