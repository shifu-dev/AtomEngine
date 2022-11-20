#pragma once
#include "AtomEngine/Core.hpp"

namespace Atom
{
    template <typename TElement>
    class InputIterator {};

    template <typename TElement>
    class OutputIterator {};

    /// ----------------------------------------------------------------------------
    /// Object used to iterate over container elements.
    ///
    /// @tparam TElement Type of element Iterator iterates over.
    template <typename TElement>
    class Iterator : public virtual InputIterator<TElement>, public virtual OutputIterator<TElement>
    {
        using ThisT = Iterator<TElement>;           ///< ----
        using ElementT = TElement;                  ///< ----
    
        /// ----------------------------------------------------------------------------
        /// Get cuurrent element by ref.
        ///
        /// @return @const ref to current element.
        mpublic virtual const ElementT ref Value() const noexcept abstract;

        /// ----------------------------------------------------------------------------
        /// Get cuurrent element by ref.
        ///
        /// @return ref to current element.
        mpublic virtual ElementT ref Value() noexcept abstract;

        /// ----------------------------------------------------------------------------
        /// Get cuurrent element by ref.
        ///
        /// @return @const ref to current element.
        mpublic const ElementT ref operator *() const noexcept
        {
            return Value();
        }

        /// ----------------------------------------------------------------------------
        /// Get cuurrent element by ref.
        ///
        /// @return ref to current element.
        mpublic ElementT ref operator *() noexcept
        {
            return Value();
        }

        /// ----------------------------------------------------------------------------
        /// Compares itself with other iterator.
        ///
        /// @param other Other Iterator to compare with.
        /// @return
        /// - = 0 if equal.
        /// - > 0 if this is greater.
        /// - < 0 if this is smaller.
        /// 
        /// @note
        /// - This does not compares the element, but the Iterator.
        mpublic virtual int Compare(const ThisT ref other) const noexcept abstract;

        /// ----------------------------------------------------------------------------
        /// Compares itself with other iterator.
        ///
        /// @param other Other iterator to compare with.
        /// @return @true if both iterators represent same value.
        ///
        /// @note
        /// - Calls \p{Compare(other) is 0;}
        /// 
        /// @see
        /// - Compare()
        mpublic virtual bool operator ==(const ThisT ref other) const noexcept
        {
            return Compare(other) is 0;
        }

        /// ----------------------------------------------------------------------------
        /// Compares itself with other iterator.
        ///
        /// @param other Other iterator to compare with.
        /// @return @true if both iterators represent same value.
        ///
        /// @note
        /// - Calls \p{Compare(other) isnot 0;}
        /// 
        /// @see
        /// - Compare()
        mpublic virtual bool operator !=(const ThisT ref other) const noexcept
        {
            return Compare(other) isnot 0;
        }
    };
}