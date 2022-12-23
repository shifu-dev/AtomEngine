#pragma once
#include "AtomEngine/Core.hpp"

namespace Atom
{
    /// Object to iterate over a collection of elements.
    /// This Iterator does not modifies the collection or its elements.
    /// 
    /// @tparam ElementT Type of element Iterator iterates over.
    template <typename ElementT>
    interface IConstIterator
    {
        /// Get const reference to current element.
        virtual const ElementT& Value() const noexcept abstract;

        /// Get const reference to current element.
        const ElementT& operator * () const noexcept
        {
            return Value();
        }

        /// Get const pointer to current element.
        const ElementT* operator -> () const noexcept
        {
            return Value();
        }

        /// Compares itself with other iterator.
        /// 
        /// @param other Other iterator to compare with.
        /// @return
        /// - = 0 if equal.
        /// - > 0 if this is greater.
        /// - < 0 if this is smaller.
        /// 
        /// @note
        /// - This does not compares the element, but the Iterator.
        virtual int Compare(const IConstIterator& other) const noexcept abstract;

        /// @returns Compare(other) == 0;
        bool operator == (const IConstIterator& other) const noexcept
        {
            return Compare(other) == 0;
        }

        /// @returns Compare(other) != 0;
        bool operator != (const IConstIterator& other) const noexcept
        {
            return Compare(other) != 0;
        }
    };

    /// Object to iterate over container elements.
    /// 
    /// @tparam ElementT Type of element IIterator iterates over.
    template <typename ElementT>
    interface IIterator:
        public virtual IConstIterator<ElementT>
    {
        /// Get reference to current element.
        virtual ElementT& Value() noexcept abstract;

        /// Get reference to current element.
        ElementT& operator * () noexcept
        {
            return Value();
        }

        /// Get pointer to current element.
        ElementT* operator -> () noexcept
        {
            return &Value();
        }
    };
}