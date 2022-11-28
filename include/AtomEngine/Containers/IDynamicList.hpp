#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/IList.hpp"
#include "AtomEngine/Containers/IDynamicCollection.hpp"

namespace Atom
{
    /// @brief list like structure that can manage memory dynamically
    /// @tparam TElement type of element to store
    template <typename TElement>
    interface IDynamicList : 
        public virtual IList<TElement>, 
        public virtual IDynamicCollection<TElement> {};
}