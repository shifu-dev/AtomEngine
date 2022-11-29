#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/IConstList.hpp"
#include "AtomEngine/Containers/ArrayIterator.hpp"

namespace Atom
{
    /// Represents a read only collection that holds memory in contiguous order.
    /// 
    /// @tparam TElement Type of element this array contains.
    template <typename TElement>
    interface IConstArray : public virtual IConstList<TElement>
    {
        using ElementT = TElement;
        using ArrayIteratorT = ArrayIterator<ElementT>;

        /// ----------------------------------------------------------------------------
        /// @return Pointer to the underlying array.
        mpublic virtual const ElementT ptr Data() const noexcept abstract;

        mpublic virtual const ArrayIteratorT Begin() const noexcept abstract;

        mpublic virtual const ArrayIteratorT End() const noexcept abstract;
    };
}