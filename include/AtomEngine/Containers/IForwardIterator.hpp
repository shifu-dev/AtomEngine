#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/IIterator.hpp"

namespace Atom
{
    /// Object to iterate over container elements.
    /// \n IConstForwardIterator provides functionality to move iterator forward.
    ///
    /// @tparam ElementT Type of element IIterator iterates over.
    template <typename ElementT>
    interface IConstForwardIterator:
        public virtual IConstIterator<ElementT>
    {
        using ThisT = IConstForwardIterator<ElementT>;

    /// ----------------------------------------------------------------------------
    public:
        /// Moves IIterator forward to point to next element.
        virtual void MoveFwd() noexcept abstract;

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
        ThisT& operator ++ (int) noexcept
        {
            MoveFwd();
            return *this;
        }
    };

    template <typename ElementT>
    interface IForwardIterator:
        public virtual IConstForwardIterator<ElementT>,
        public virtual IIterator<ElementT> { };
}