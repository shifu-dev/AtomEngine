#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/IArray.hpp"
#include "AtomEngine/Containers/IDynamicList.hpp"

namespace Atom
{
    /// Represents a resizable collection that holds memory in contiguous order.
    /// 
    /// @tparam ElementT Type of element this array contains.
    template <typename ElementT>
    interface IDynamicArray :
        public virtual IArray<ElementT>,
        public virtual IDynamicList<ElementT> { };
}