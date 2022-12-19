#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/IList.hpp"
#include "AtomEngine/Containers/IDynamicCollection.hpp"

namespace Atom
{
    /// List like structure that can manage memory dynamically
    /// 
    /// @tparam ElementT type of element to store
    template <typename ElementT>
    interface IDynamicList:
        public virtual IList<ElementT>,
        public virtual IDynamicCollection<ElementT> { };
}