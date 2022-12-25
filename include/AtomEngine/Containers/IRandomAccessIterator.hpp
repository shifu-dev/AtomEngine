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
        virtual void MoveBwdBy(sizet steps) const noexcept = 0;

        /// Moves iterator backward by count \p{steps}.
        ///
        /// @param steps Count of steps to move iterator by.
        virtual void MoveFwdBy(sizet steps) const noexcept = 0;

        void MoveFwd() const noexcept override final { MoveFwdBy(1); }
        void MoveBwd() const noexcept override final { MoveBwdBy(1); }

        /// Moves iterator forward by count \p{steps}.
        /// 
        /// @param steps Count of steps to move iterator by.
        /// @return & to this object.
        const ThisT& operator += (sizet steps) const noexcept
        {
            MoveFwdBy(steps);
            return *this;
        }

        /// Moves iterator backward by count \p{steps}.
        /// 
        /// @param steps Count of steps to move iterator by.
        /// @return & to this object.
        const ThisT& operator -= (sizet steps) const noexcept
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