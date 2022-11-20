#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/BidirectionalIterator.hpp"

namespace Atom
{
    /// ----------------------------------------------------------------------------
    /// Object to iterate over container elements.
    /// \n RandomAccessIterator provides functionality to move randomly to any element.
    ///
    /// @tparam TElement Type of element Iterator iterates over.
    template <typename TElement>
    class RandomAccessIterator : public virtual BidirectionalIterator<TElement>
    {
        using ThisT = BidirectionalIterator<TElement>;      ///< ----

        /// ----------------------------------------------------------------------------
        /// Moves iterator forward by count \p{steps}.
        ///
        /// @param steps Count of steps to move iterator by.
        mpublic virtual void MoveBwdBy(const sizet steps) const noexcept abstract;

        /// ----------------------------------------------------------------------------
        /// Moves iterator backward by count \p{steps}.
        ///
        /// @param steps Count of steps to move iterator by.
        mpublic virtual void MoveFwdBy(const sizet steps) const noexcept abstract;

        mpublic virtual void MoveFwd() const noexcept override { MoveFwdBy(1); }
        mpublic virtual void MoveBwd() const noexcept override { MoveBwdBy(1); }

        /// ----------------------------------------------------------------------------
        /// Moves iterator forward by count \p{steps}.
        /// 
        /// @param steps Count of steps to move iterator by.
        /// @return ref to this object.
        mpublic ThisT ref operator + (const sizet steps) noexcept
        {
            MoveFwdBy(steps);
            return ptr this;
        }

        /// ----------------------------------------------------------------------------
        /// Moves iterator forward by count \p{steps}.
        /// 
        /// @param steps Count of steps to move iterator by.
        /// @return const ref to this object.
        mpublic const ThisT ref operator + (const sizet steps) const noexcept
        {
            MoveFwdBy(steps);
            return ptr this;
        }

        /// ----------------------------------------------------------------------------
        /// Moves iterator backward by count \p{steps}.
        /// 
        /// @param steps Count of steps to move iterator by.
        /// @return ref to this object.
        mpublic ThisT ref operator - (const sizet steps) noexcept
        {
            MoveBwdBy(steps);
            return ptr this;
        }

        /// ----------------------------------------------------------------------------
        /// Moves iterator backward by count \p{steps}.
        /// 
        /// @param steps Count of steps to move iterator by.
        /// @return const ref to this object.
        mpublic const ThisT ref operator - (const sizet steps) const noexcept
        {
            MoveBwdBy(steps);
            return ptr this;
        }
    };
}