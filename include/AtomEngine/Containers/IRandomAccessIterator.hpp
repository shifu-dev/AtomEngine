#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/IBidirectionalIterator.hpp"

namespace Atom
{
    /// Object to iterate over container elements.
    /// \n IRandomAccessIterator provides functionality to move randomly to any element.
    ///
    /// @tparam ElementT Type of element IIterator iterates over.
    template <typename ElementT>
    interface IRandomAccessIterator:
        public virtual IBidirectionalIterator<ElementT>
    {
        using ThisT = IBidirectionalIterator<ElementT>;

        /// Moves iterator forward by count \p{steps}.
        ///
        /// @param steps Count of steps to move iterator by.
        virtual void MoveBwdBy(sizet steps) const noexcept abstract;

        /// Moves iterator backward by count \p{steps}.
        ///
        /// @param steps Count of steps to move iterator by.
        virtual void MoveFwdBy(sizet steps) const noexcept abstract;

        void MoveFwd() const noexcept final { MoveFwdBy(1); }
        void MoveBwd() const noexcept final { MoveBwdBy(1); }

        /// Moves iterator forward by count \p{steps}.
        /// 
        /// @param steps Count of steps to move iterator by.
        /// @return & to this object.
        ThisT& operator += (sizet steps) noexcept
        {
            MoveFwdBy(steps);
            return *this;
        }

        /// Moves iterator forward by count \p{steps}.
        /// 
        /// @param steps Count of steps to move iterator by.
        /// @return const & to this object.
        const ThisT& operator += (sizet steps) const noexcept
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

        /// Moves iterator backward by count \p{steps}.
        /// 
        /// @param steps Count of steps to move iterator by.
        /// @return const & to this object.
        const ThisT& operator -= (sizet steps) const noexcept
        {
            MoveBwdBy(steps);
            return *this;
        }
    };
}