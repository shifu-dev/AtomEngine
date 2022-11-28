#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/IForwardIterator.hpp"

namespace Atom
{
    /// ----------------------------------------------------------------------------
    /// Object to iterate over container elements.
    /// \n IBidirectionalIterator provides functionality to move iterator backward and forward.
    ///
    /// @tparam TElement Type of element IIterator iterates over.
    template <typename TElement>
    interface IBidirectionalIterator : public virtual IForwardIterator<TElement>
    {
        using ThisT = IBidirectionalIterator<TElement>;          ///< ----

        /// ----------------------------------------------------------------------------
        /// Moves IIterator backward to point to previous element.
        mpublic virtual void MoveBwd() const noexcept abstract;

        /// ----------------------------------------------------------------------------
        /// Moves IIterator backward to point to previous element.
        ///
        /// @note
        /// - Calls MoveBwd()
        mpublic const ThisT ref operator --() const noexcept
        {
            MoveBwd();
            return ptr this;
        }

        /// ----------------------------------------------------------------------------
        /// Moves IIterator backward to point to previous element.
        ///
        /// @note
        /// - Calls MoveBwd()
        mpublic ThisT ref operator --() noexcept
        {
            MoveBwd();
            return ptr this;
        }

        /// ----------------------------------------------------------------------------
        /// Moves IIterator backward to point to previous element.
        ///
        /// @note
        /// - Does not follow postfix definations, works same as prefix.
        /// - Calls MoveBwd()
        mpublic const ThisT ref operator --(int) const noexcept
        {
            MoveBwd();
            return ptr this;
        }

        /// ----------------------------------------------------------------------------
        /// Moves IIterator backward to point to previous element.
        ///
        /// @note
        /// - Does not follow postfix definations, works same as prefix.
        /// - Calls MoveBwd()
        mpublic ThisT ref operator --(int) noexcept
        {
            MoveBwd();
            return ptr this;
        }
    };
}