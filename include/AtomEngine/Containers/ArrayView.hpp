#pragma once
#include "AtomEngine/Core.hpp"
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
        using IConstArrayT = IConstArray<TElement>;

        mprotected using BaseT::mArray;
        mprotected using BaseT::mCount;

        // *******************************************************************
        // * Constructors and Destructors

        mpublic ArrayView() noexcept = default;

        mpublic template <sizet TSize>
        ArrayView(const ElementT(&arr)[TSize]) noexcept :
            ThisT(arr, TSize) { }

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