#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/IIterator.hpp"

namespace Atom
{
    /// ----------------------------------------------------------------------------
    /// Object to iterate over container elements.
    /// \n IForwardIterator provides functionality to move iterator forward.
    ///
    /// @tparam TElement Type of element IIterator iterates over.
    template <typename TElement>
    interface IForwardIterator : public virtual IIterator<TElement>
    {
        using ThisT = IForwardIterator<TElement>;    ///< ----

        /// ----------------------------------------------------------------------------
        /// Moves IIterator forward to point to next element.
        mpublic virtual void MoveFwd() const noexcept abstract;

        /// ----------------------------------------------------------------------------
        /// Moves IIterator forward to point to next element.
        ///
        /// @note
        /// - Calls MoveFwd()
        mpublic const ThisT ref operator ++() const noexcept
        {
            MoveFwd();
            return ptr this;
        }

        /// ----------------------------------------------------------------------------
        /// Moves IIterator forward to point to next element.
        ///
        /// @note
        /// - Calls MoveFwd()
        mpublic ThisT ref operator ++() noexcept
        {
            MoveFwd();
            return ptr this;
        }

        /// ----------------------------------------------------------------------------
        /// Moves IIterator forward to point to next element.
        ///
        /// @note
        /// - Does not follow postfix definations, works same as prefix.
        /// - Calls MoveFwd()
        mpublic const ThisT ref operator ++(int) const noexcept
        {
            MoveFwd();
            return ptr this;
        }

        /// ----------------------------------------------------------------------------
        /// Moves IIterator forward to point to next element.
        ///
        /// @note
        /// - Does not follow postfix definations, works same as prefix.
        /// - Calls MoveFwd()
        mpublic ThisT ref operator ++(int) noexcept
        {
            MoveFwd();
            return ptr this;
        }
    };
}