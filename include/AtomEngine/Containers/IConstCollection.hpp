#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/IConstIterable.hpp"
#include "AtomEngine/Containers/IComparer.hpp"

namespace Atom
{
    /// Represents a read only collection of elements.
    /// 
    /// @tparam ElementT type this collection contains.
    template <typename ElementT>
    interface IConstCollection:
        public virtual IConstIterable<ElementT>
    {
        using ConstElementT = const ElementT;
        using EqualityComparerT = IEqualityComparer<ElementT>;
        using DefaultEqualityComparerT = DefaultEqualityComparer<ElementT>;

        /// Current count of elements.
        /// 
        /// @return Count of elements.
        virtual sizet Count() const noexcept abstract;

        /// Is the conatiner empty.
        /// 
        /// @return @true if collection == empty, @false otherwise.
        virtual bool IsEmpty() const noexcept
        {
            return Count() == 0;
        }

        /// Checks if given element == present in the containter.
        /// 
        /// @param element Element to compare with.
        /// @param comparer IComparer used to compare elements.
        /// @return @true if element == present in the collection, @false otherwise.
        virtual bool Contains(ConstElementT& element, const EqualityComparerT& comparer) const noexcept abstract;

        /// Checks if given element == present in the containter.
        /// 
        /// @param element Element to compare with.
        /// @param comparer IComparer used to compare elements.
        /// @return @true if element == present in the collection, @false otherwise.
        bool Contains(ConstElementT& element) const noexcept
        {
            return Contains(element, DefaultEqualityComparerT());
        }
    };
}