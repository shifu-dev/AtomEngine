#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/ICollection.hpp"

namespace Atom
{
    /// Base class for collections which can manage memory dynamically.
    /// 
    /// @tparam ElementT type of element to store
    template <typename ElementT>
    interface IDynamicCollection:
        public virtual ICollection<ElementT>
    {
        /// Resizes the underlying memory.
        /// 
        /// @param count count of objects to allocate memor for
        /// @note this does not change element count
        virtual void Resize(sizet count) = 0;

        /// Asks the collection to reserve memory for count elements.
        /// 
        /// @param count minimum count of elements to reserve memory for
        /// @return count of reserved memory for element
        virtual sizet Reserve(sizet count) = 0;

        /// Resizes capacity equal to count.
        /// 
        /// @return count of memory for element currently allocated
        virtual void ShrinkToFit() = 0;
    };
}