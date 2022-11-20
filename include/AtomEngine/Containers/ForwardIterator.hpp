#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/Iterator.hpp"

namespace Atom
{
    /// ----------------------------------------------------------------------------
    /// Object to iterate over container elements.
    /// \n ForwardIterator provides functionality to move iterator forward.
    ///
    /// @tparam TElement Type of element Iterator iterates over.
    template <typename TElement>
    class ForwardIterator : public virtual Iterator<TElement>
    {
        using ThisT = ForwardIterator<TElement>;    ///< ----

        /// ----------------------------------------------------------------------------
        /// Moves Iterator forward to point to next element.
        mpublic virtual void MoveFwd() const noexcept abstract;

        /// ----------------------------------------------------------------------------
        /// Moves Iterator forward to point to next element.
        ///
        /// @note
        /// - Calls MoveFwd()
        mpublic const ThisT ref operator ++() const noexcept
        {
            MoveFwd();
            return ptr this;
        }

        /// ----------------------------------------------------------------------------
        /// Moves Iterator forward to point to next element.
        ///
        /// @note
        /// - Calls MoveFwd()
        mpublic ThisT ref operator ++() noexcept
        {
            MoveFwd();
            return ptr this;
        }

        /// ----------------------------------------------------------------------------
        /// Moves Iterator forward to point to next element.
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
        /// Moves Iterator forward to point to next element.
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