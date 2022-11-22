#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/List.hpp"
#include "AtomEngine/Containers/DynamicCollection.hpp"

namespace Atom
{
    /// @brief list like structure that can manage memory dynamically
    /// @tparam TElement type of element to store
    template <typename TElement>
    class DynamicList : 
        public virtual List<TElement>, 
        public virtual DynamicCollection<TElement> {};
}