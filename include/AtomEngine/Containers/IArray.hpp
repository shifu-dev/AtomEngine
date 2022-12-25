#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/IConstArray.hpp"
#include "AtomEngine/Containers/IList.hpp"

namespace Atom
{
    /// Represents a collection that holds memory in contiguous order.
    /// 
    /// @tparam ElementT Type of element this array contains.
    template <typename ElementT>
    interface IArray:
        public virtual IConstArray<ElementT>,
        public virtual IList<ElementT>
    {
        using ArrayIteratorT = ArrayIterator<ElementT>;

    /// ----------------------------------------------------------------------------
    public:
        /// @return Pointer to the underlying array.
        virtual ElementT* Data() noexcept = 0;

        virtual ArrayIteratorT Begin() noexcept = 0;

        virtual ArrayIteratorT End() noexcept = 0;
    };
}