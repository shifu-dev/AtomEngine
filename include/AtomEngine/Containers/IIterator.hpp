#pragma once
#include "AtomEngine/Core.hpp"

namespace Atom
{
    /// Object to iterate over container elements.
    /// This Iterator does not modifies the elements.
    ///
    /// @tparam ElementT Type of element IConstIterator iterates over.
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
        /// @param other Other IConstIterator to compare with.
        /// @return
        /// - = 0 if equal.
        /// - > 0 if this == greater.
        /// - < 0 if this == smaller.
        /// 
        /// @note
        /// - This does not compares the element, but the Iterator.
        virtual int Compare(const IConstIterator& other) const noexcept abstract;

        /// @returns Compare(const IConstIterator& other) == 0;
        bool operator == (const IConstIterator& other) const noexcept
        {
            return Compare(other) == 0;
        }

        /// @returns Compare(const IConstIterator& other) != 0;
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
        using IConstIteratorT = IConstIterator<ElementT>;

        using IConstIteratorT::Value;

        /// Get reference to current element.
        virtual ElementT& Value() noexcept abstract;

        using IConstIteratorT::operator *;

        /// Get reference to current element.
        ElementT& operator * () noexcept
        {
            return Value();
        }

        using IConstIteratorT::operator ->;

        /// Get pointer to current element.
        ElementT* operator -> () noexcept
        {
            return &Value();
        }
    };
}