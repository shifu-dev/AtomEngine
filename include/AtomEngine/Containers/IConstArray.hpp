#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/IConstList.hpp"
#include "AtomEngine/Containers/ArrayIterator.hpp"

namespace Atom
{
    /// Represents a read only collection that holds memory in contiguous order.
    /// 
    /// @tparam ElementT Type of element this array contains.
    template <typename ElementT>
    interface IConstArray:
        public virtual IConstList<ElementT>
    {
        using ConstElementT = const ElementT;
        using ArrayIteratorT = ArrayIterator<ElementT>;

    /// ----------------------------------------------------------------------------
    public:
        /// @return Pointer to the underlying array.
        virtual ConstElementT* Data() const noexcept abstract;

        virtual const ArrayIteratorT Begin() const noexcept abstract;

        virtual const ArrayIteratorT End() const noexcept abstract;
    };
}