#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/IForwardIterator.hpp"

namespace Atom
{
    /// Object to iterate over container elements.
    /// \n IBidirectionalIterator provides functionality to move iterator backward and forward.
    ///
    /// @tparam ElementT Type of element IIterator iterates over.
    template <typename ElementT>
    interface IBidirectionalIterator: public virtual IForwardIterator<ElementT>
    {
        using ThisT = IBidirectionalIterator<ElementT>;

        /// Moves IIterator backward to point to previous element.
        virtual void MoveBwd() const noexcept abstract;

        /// Moves IIterator backward to point to previous element.
        ///
        /// @note
        /// - Calls MoveBwd()
        const ThisT& operator -- () const noexcept
        {
            MoveBwd();
            return *this;
        }

        /// Moves IIterator backward to point to previous element.
        ///
        /// @note
        /// - Calls MoveBwd()
        ThisT& operator -- () noexcept
        {
            MoveBwd();
            return *this;
        }

        /// Moves IIterator backward to point to previous element.
        ///
        /// @note
        /// - Does not follow postfix definations, works same as prefix.
        /// - Calls MoveBwd()
        const ThisT& operator -- (int) const noexcept
        {
            MoveBwd();
            return *this;
        }

        /// Moves IIterator backward to point to previous element.
        ///
        /// @note
        /// - Does not follow postfix definations, works same as prefix.
        /// - Calls MoveBwd()
        ThisT& operator -- (int) noexcept
        {
            MoveBwd();
            return *this;
        }
    };
}