#pragma once
#include "AtomEngine/Core.hpp"

namespace Atom
{
    template <typename ElementT>
    interface IInputIterator {};

    template <typename ElementT>
    interface IOutputIterator {};

    /// Object to iterate over container elements.
    ///
    /// @tparam ElementT Type of element IIterator iterates over.
    template <typename ElementT>
    interface IIterator:
        public virtual IInputIterator<ElementT>,
        public virtual IOutputIterator<ElementT>
    {
        using ThisT = IIterator<ElementT>;
        using ConstElementT = const ElementT;

        /// Get cuurrent element by &.
        ///
        /// @return @const & to current element.
        virtual ConstElementT& Value() const noexcept abstract;

        /// Get cuurrent element by &.
        ///
        /// @return & to current element.
        virtual ElementT& Value() noexcept abstract;

        /// Get cuurrent element by &.
        ///
        /// @return @const & to current element.
        ConstElementT& operator *() const noexcept
        {
            return Value();
        }

        /// Get cuurrent element by &.
        ///
        /// @return & to current element.
        ElementT& operator *() noexcept
        {
            return Value();
        }

        /// Compares itself with other iterator.
        ///
        /// @param other Other IIterator to compare with.
        /// @return
        /// - = 0 if equal.
        /// - > 0 if this == greater.
        /// - < 0 if this == smaller.
        /// 
        /// @note
        /// - This does not compares the element, but the IIterator.
        virtual int Compare(const ThisT& other) const noexcept abstract;

        /// Compares itself with other iterator.
        ///
        /// @param other Other iterator to compare with.
        /// @return @true if both iterators represent same value.
        ///
        /// @note
        /// - Calls \p{Compare(other) == 0;}
        /// 
        /// @see
        /// - Compare()
        virtual bool operator == (const ThisT& other) const noexcept
        {
            return Compare(other) == 0;
        }

        /// Compares itself with other iterator.
        ///
        /// @param other Other iterator to compare with.
        /// @return @true if both iterators represent same value.
        ///
        /// @note
        /// - Calls \p{Compare(other) != 0;}
        /// 
        /// @see
        /// - Compare()
        virtual bool operator != (const ThisT& other) const noexcept
        {
            return Compare(other) != 0;
        }
    };
}