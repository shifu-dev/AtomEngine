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
        using ConstArrayIteratorT = TConstArrayIterator<ElementT>;

    /// ----------------------------------------------------------------------------
    public:
        /// @returns Const pointer to the underlying array.
        virtual const ElementT* Data() const noexcept = 0;

        /// ArrayIterator to the first element.
        /// 
        /// @note
        /// - This is to avoid boxing the iterator which happens in IIterable.
        virtual ConstArrayIteratorT Begin() const noexcept = 0;

        /// ArrayIterator to the last element.
        /// 
        /// @note
        /// - This is to avoid boxing the iterator which happens in IIterable.
        virtual ConstArrayIteratorT End() const noexcept = 0;
    };
}