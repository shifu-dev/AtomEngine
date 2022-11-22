#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/Iterable.hpp"
#include "AtomEngine/Containers/Comparer.hpp"

namespace Atom
{
    /// @brief a data structure that can modify elements
    /// @tparam TElement type of element to store
    template <typename TElement>
    class Collection : public virtual Iterable<TElement>
    {
        using ElementT = TElement;
        using EqualityComparerT = EqualityComparer<ElementT>;

        /// @brief current count of elements
        /// @return count of elements
        mpublic virtual sizet Count() const noexcept abstract;

        mpublic virtual bool IsEmpty() const noexcept
        {
            return Count() == 0;
        }

        /// @brief checks if given element is present in collection
        /// @param element element to compare with
        /// @param comparer comparer used to compare elements
        /// @return true if element is present in the collection
        mpublic virtual bool Contains(const ElementT ref element, const EqualityComparerT ref comparer) const noexcept abstract;

        /// @brief adds element to collection
        /// @param element element to store
        /// @note position of element is implementation dependent
        mpublic virtual void Insert(const ElementT ref element) abstract;

        /// @brief removed element from collection
        /// @param element element to remove
        mpublic virtual void Remove(const ElementT ref element) abstract;
    };
}