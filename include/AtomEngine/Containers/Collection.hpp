#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/ConstCollection.hpp"

namespace Atom
{
    /// ----------------------------------------------------------------------------
    /// Represents a modifiable collection of elements.
    /// 
    /// @tparam TElement type this collection contains.
    template <typename TElement>
    class Collection : public virtual ConstCollection<TElement>
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