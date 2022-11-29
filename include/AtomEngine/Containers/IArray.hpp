#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/IConstArray.hpp"
#include "AtomEngine/Containers/IList.hpp"

namespace Atom
{
    /// Represents a collection that holds memory in contiguous order.
    /// 
    /// @tparam TElement Type of element this array contains.
    template <typename TElement>
    interface IArray : public virtual IConstArray<TElement>, public virtual IList<TElement>
    {
        using ElementT = TElement;
        using IConstArrayT = IConstArray<ElementT>;
        using IPredicateT = IPredicate<const ElementT ref, sizet>;
        using IForwardIteratorT = IForwardIterator<ElementT>;
        using ArrayIteratorT = ArrayIterator<ElementT>;

        // *******************************************************************

        /// ----------------------------------------------------------------------------
        /// @return Pointer to the underlying array.
        mpublic virtual ElementT ptr Data() noexcept abstract;

        mpublic virtual ArrayIteratorT Begin() noexcept abstract;

        mpublic virtual ArrayIteratorT End() noexcept abstract;
    };
}