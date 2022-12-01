#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/IConstCollection.hpp"
#include "AtomEngine/Containers/IIterable.hpp"

namespace Atom
{
    /// ----------------------------------------------------------------------------
    /// Represents a modifiable collection of elements.
    /// 
    /// @tparam TElement type this collection contains.
    template <typename TElement>
    interface ICollection : public virtual IConstCollection<TElement>,
        public virtual IIterable<TElement>
    {
        using ElementT = TElement;                                             ///< ----

        /// ----------------------------------------------------------------------------
        /// Current count of elements allocated in memory.
        /// 
        /// @return Count of elements allocated in memory.
        mpublic virtual sizet Capacity() const noexcept abstract;

        /// ----------------------------------------------------------------------------
        /// Inserts an element in the collection.
        /// 
        /// @param element Element to insert.
        /// 
        /// @note Position of element is implementation dependent.
        mpublic virtual void Insert(const ElementT ref element) abstract;

        /// ----------------------------------------------------------------------------
        /// Removes element from the collection.
        /// 
        /// @param element Element to remove.
        mpublic virtual void Remove(const ElementT ref element) abstract;
    };
}