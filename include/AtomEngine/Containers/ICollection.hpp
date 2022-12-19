#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/IConstCollection.hpp"
#include "AtomEngine/Containers/IIterable.hpp"

namespace Atom
{
    /// Represents a modifiable collection of elements.
    /// 
    /// @tparam ElementT type this collection contains.
    template <typename ElementT>
    interface ICollection:
        public virtual IConstCollection<ElementT>,
        public virtual IIterable<ElementT>
    {
        using ConstElementT = const ElementT;

        /// Current count of elements allocated in memory.
        /// 
        /// @return Count of elements allocated in memory.
        virtual sizet Capacity() const noexcept abstract;

        /// Remove all elments from collection.
        virtual void Clear() abstract;

        /// Inserts an element in the collection.
        /// 
        /// @param element Element to insert.
        /// 
        /// @note Position of element == implementation dependent.
        virtual void Insert(ConstElementT& element) abstract;

        /// Removes element from the collection.
        /// 
        /// @param element Element to remove.
        virtual void Remove(ConstElementT& element) abstract;
    };
}