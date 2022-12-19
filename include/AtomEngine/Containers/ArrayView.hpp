#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/InitializerList.hpp"
#include "AtomEngine/Containers/ConstArrayBase.hpp"

namespace Atom
{
    /// Represents a read only collection that holds memory in contiguous order.
    /// 
    /// @tparam ElementT Type of element this array contains.
    template <typename ElementT>
    class ArrayView: public ConstArrayBase<ElementT>
    {
        using ThisT = ArrayView<ElementT>;
        using BaseT = ConstArrayBase<ElementT>;
        using ConstElementT = const ElementT;
        using InitializerListT = InitializerList<ElementT>;
        using ConstArrayT = const IConstArray<ElementT>;

    /// ----------------------------------------------------------------------------
    public:
        ArrayView() noexcept = default;

        ArrayView(const InitializerListT list) noexcept:
            ThisT(list.begin(), list.size()) { }

        ArrayView(ConstElementT* arr, sizet count) noexcept
        {
            _array = CCAST(ElementT*, arr);
            _count = count;
        }

        ArrayView(ConstArrayT& arr) noexcept:
            ThisT(arr.Data(), arr.Count()) { }

        ArrayView(ConstArrayT& arr, sizet start) noexcept:
            ThisT(arr.Data() + start, arr.Count()) { }

        ArrayView(ConstArrayT& arr, sizet start, sizet count) noexcept:
            ThisT(arr.Data() + start, min(arr.Count(), count)) { }

        ArrayView(const ThisT& other) noexcept = default;
        ArrayView(ThisT&& other) noexcept = default;

        ThisT& operator = (const ThisT& other) noexcept = default;
        ThisT& operator = (ThisT&& other) noexcept = default;

        ~ArrayView() noexcept = default;

    /// ----------------------------------------------------------------------------
    protected:
        using BaseT::_array;
        using BaseT::_count;
    };
}