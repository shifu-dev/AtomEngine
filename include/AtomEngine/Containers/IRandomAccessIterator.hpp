#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/IBidirectionalIterator.hpp"

namespace Atom
{
    /// Object to iterate over container elements.
    /// \n IConstRandomAccessIterator provides functionality to move randomly to any element.
    ///
    /// @tparam ElementT Type of element IIterator iterates over.
    template <typename ElementT>
    interface IConstRandomAccessIterator:
        public virtual IConstBidirectionalIterator<ElementT>
    {
        using ThisT = IConstRandomAccessIterator<ElementT>;

        /// Moves iterator forward by count \p{steps}.
        ///
        /// @param steps Count of steps to move iterator by.
        virtual void MoveBwdBy(sizet steps) noexcept abstract;

        /// Moves iterator backward by count \p{steps}.
        ///
        /// @param steps Count of steps to move iterator by.
        virtual void MoveFwdBy(sizet steps) noexcept abstract;

        void MoveFwd() noexcept final { MoveFwdBy(1); }
        void MoveBwd() noexcept final { MoveBwdBy(1); }

        /// Moves iterator forward by count \p{steps}.
        /// 
        /// @param steps Count of steps to move iterator by.
        /// @return & to this object.
        ThisT& operator += (sizet steps) noexcept
        {
            MoveFwdBy(steps);
            return *this;
        }

        /// Moves iterator backward by count \p{steps}.
        /// 
        /// @param steps Count of steps to move iterator by.
        /// @return & to this object.
        ThisT& operator -= (sizet steps) noexcept
        {
            MoveBwdBy(steps);
            return *this;
        }
    };

    template <typename ElementT>
    interface IRandomAccessIterator:
        public virtual IConstRandomAccessIterator<ElementT>,
        public virtual IBidirectionalIterator<ElementT> { };
}