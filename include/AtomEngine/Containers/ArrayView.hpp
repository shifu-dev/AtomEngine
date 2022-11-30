#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/InitializerList.hpp"
#include "AtomEngine/Containers/ConstArrayBase.hpp"

namespace Atom
{
    /// Represents a read only collection that holds memory in contiguous order.
    /// 
    /// @tparam TElement Type of element this array contains.
    template <typename TElement>
    class ArrayView : public ConstArrayBase<TElement>
    {
        using ThisT = ArrayView<TElement>;
        using BaseT = ConstArrayBase<TElement>;
        using ElementT = TElement;
        using InitializerListT = InitializerList<ElementT>;
        using IConstArrayT = IConstArray<TElement>;

        mprotected using BaseT::mArray;
        mprotected using BaseT::mCount;

        // *******************************************************************
        // * Constructors and Destructors

        mpublic ArrayView() noexcept = default;

        mpublic ArrayView(const InitializerListT list) noexcept :
            ThisT(list.begin(), list.size()) { }

        mpublic ArrayView(const ElementT ptr arr, const sizet count) noexcept
        {
            mArray = CCAST(ElementT ptr, arr);
            mCount = count;
        }

        mpublic ArrayView(const IConstArrayT ref arr) noexcept :
            ThisT(arr.Data(), arr.Count()) { }

        mpublic ArrayView(const IConstArrayT ref arr, const sizet start) noexcept :
            ThisT(arr.Data() + start, arr.Count()) { }

        mpublic ArrayView(const IConstArrayT ref arr, const sizet start, const sizet count) noexcept :
            ThisT(arr.Data() + start, min(arr.Count(), count)) { }

        mpublic ArrayView(const ThisT ref other) noexcept = default;
        mpublic ArrayView(ThisT rref other) noexcept = default;

        mpublic ThisT ref operator = (const ThisT ref other) noexcept = default;
        mpublic ThisT ref operator = (ThisT rref other) noexcept = default;

        mpublic dtor ArrayView() noexcept = default;
    };
}