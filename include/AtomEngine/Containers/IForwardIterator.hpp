#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/IIterator.hpp"

namespace Atom
{
    /// Object to iterate over container elements.
    /// \n IForwardIterator provides functionality to move iterator forward.
    ///
    /// @tparam ElementT Type of element IIterator iterates over.
    template <typename ElementT>
    interface IForwardIterator:
        public virtual IIterator<ElementT>
    {
        using ThisT = IForwardIterator<ElementT>;

    /// ----------------------------------------------------------------------------
    public:
        /// Moves IIterator forward to point to next element.
        virtual void MoveFwd() const noexcept abstract;

        /// Moves IIterator forward to point to next element.
        ///
        /// @note
        /// - Calls MoveFwd()
        const ThisT& operator ++ () const noexcept
        {
            MoveFwd();
            return *this;
        }

        /// Moves IIterator forward to point to next element.
        ///
        /// @note
        /// - Calls MoveFwd()
        ThisT& operator ++ () noexcept
        {
            MoveFwd();
            return *this;
        }

        /// Moves IIterator forward to point to next element.
        ///
        /// @note
        /// - Does not follow postfix definations, works same as prefix.
        /// - Calls MoveFwd()
        const ThisT& operator ++ (int) const noexcept
        {
            MoveFwd();
            return *this;
        }

        /// Moves IIterator forward to point to next element.
        ///
        /// @note
        /// - Does not follow postfix definations, works same as prefix.
        /// - Calls MoveFwd()
        ThisT& operator ++ (int) noexcept
        {
            MoveFwd();
            return *this;
        }
    };
}