#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/Array.hpp"
#include "AtomEngine/Containers/DynamicList.hpp"

namespace Atom
{
    /// Represents a resizable collection that holds memory in contiguous order.
    /// 
    /// @tparam TElement Type of element this array contains.
    template <typename TElement>
    class DynamicArray : public virtual Array<TElement>, public virtual DynamicList<TElement>
    {
    };
}