#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/IConstIterable.hpp"
#include "AtomEngine/Containers/IComparer.hpp"

namespace Atom
{
    /// ----------------------------------------------------------------------------
    /// Represents a read only collection of elements.
    /// 
    /// @tparam TElement type this collection contains.
    template <typename TElement>
    interface IConstCollection : public virtual IConstIterable<TElement>
    {
        using ElementT = TElement;                                             ///< ----
        using IEqualityComparerT = IEqualityComparer<ElementT>;                ///< ----
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
        /// @param comparer IComparer used to compare elements.
        /// @return @true if element is present in the collection, @false otherwise.
        mpublic virtual bool Contains(const ElementT ref element, const IEqualityComparerT ref comparer) const noexcept abstract;

        /// ----------------------------------------------------------------------------
        /// Checks if given element is present in the containter.
        /// 
        /// @param element Element to compare with.
        /// @param comparer IComparer used to compare elements.
        /// @return @true if element is present in the collection, @false otherwise.
        mpublic bool Contains(const ElementT ref element) const noexcept
        {
            return Contains(element, DefaultEqualityComparerT());
        }
    };
}