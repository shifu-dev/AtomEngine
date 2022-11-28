#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/IConstCollection.hpp"

namespace Atom
{
    /// ----------------------------------------------------------------------------
    /// Represents a modifiable collection of elements.
    /// 
    /// @tparam TElement type this collection contains.
    template <typename TElement>
    interface ICollection : public virtual IConstCollection<TElement>
    {
        using ElementT = TElement;                                             ///< ----

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