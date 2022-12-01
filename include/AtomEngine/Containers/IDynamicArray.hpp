#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/IArray.hpp"
#include "AtomEngine/Containers/IDynamicList.hpp"

namespace Atom
{
    /// Represents a resizable collection that holds memory in contiguous order.
    /// 
    /// @tparam TElement Type of element this array contains.
    template <typename TElement>
    interface IDynamicArray :
        public virtual IArray<TElement>,
        public virtual IDynamicList<TElement>
    {
    };
}