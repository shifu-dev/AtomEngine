#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/Iterable.hpp"
#include "AtomEngine/Containers/Comparer.hpp"

namespace Atom
{
    /// ----------------------------------------------------------------------------
    /// Represents a modifiable collection of elements.
    /// 
    /// @tparam TElement type this collection contains.
    template <typename TElement>
    class Collection : public virtual Iterable<TElement>
    {
        using ElementT = TElement;                                             ///< ----
        using EqualityComparerT = EqualityComparer<ElementT>;                  ///< ----
        using DefaultEqualityComparerT = DefaultEqualityComparer<ElementT>;    ///< ----

        /// ----------------------------------------------------------------------------
        /// Current count of elements.
        /// 
        /// @return Count of elements.
        mpublic virtual sizet Count() const noexcept abstract;

        /// ----------------------------------------------------------------------------
        /// Is the conatiner empty.
        /// 
        /// @return @true if collection is empty, @false otherwise.
        mpublic virtual bool IsEmpty() const noexcept
        {
            return Count() == 0;
        }

        /// ----------------------------------------------------------------------------
        /// Checks if given element is present in the containter.
        /// 
        /// @param element Element to compare with.
        /// @param comparer Comparer used to compare elements.
        /// @return @true if element is present in the collection, @false otherwise.
        mpublic virtual bool Contains(const ElementT ref element, const EqualityComparerT ref comparer) const noexcept abstract;

        /// ----------------------------------------------------------------------------
        /// Checks if given element is present in the containter.
        /// 
        /// @param element Element to compare with.
        /// @param comparer Comparer used to compare elements.
        /// @return @true if element is present in the collection, @false otherwise.
        mpublic bool Contains(const ElementT ref element) const noexcept
        {
            return Contains(element, DefaultEqualityComparerT());
        }

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