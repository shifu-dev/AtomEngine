#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/IForwardIterator.hpp"

namespace Atom
{
    /// Object to iterate over container elements.
    /// \n IConstBidirectionalIterator provides functionality to move iterator backward and forward.
    ///
    /// @tparam ElementT Type of element IIterator iterates over.
    template <typename ElementT>
    interface IConstBidirectionalIterator:
        public virtual IConstForwardIterator<ElementT>
    {
        using ThisT = IConstBidirectionalIterator<ElementT>;

        /// Moves Iterator backward to point to previous element.
        virtual void MoveBwd() const noexcept = 0;

        /// @copydetail MoveBwd()
        /// @note
        /// - Calls MoveBwd()
        const ThisT& operator -- () const noexcept
        {
            MoveBwd();
            return *this;
        }

        /// @copydetail MoveBwd()
        /// @note
        /// - Does not follow postfix definations, works same as prefix.
        /// - Calls MoveBwd()
        const ThisT& operator -- (int) const noexcept
        {
            MoveBwd();
            return *this;
        }
    };

    /// Object to iterate over container elements.
    /// \n IBidirectionalIterator provides functionality to move iterator backward and forward.
    ///
    /// @tparam ElementT Type of element IIterator iterates over.
    template <typename ElementT>
    interface IBidirectionalIterator:
        public virtual IConstBidirectionalIterator<ElementT>,
        public virtual IForwardIterator<ElementT> { };
}