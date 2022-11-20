#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/ForwardIterator.hpp"

namespace Atom
{
    template <typename TElement>
    class BidirectionalIterator : public virtual ForwardIterator<TElement>
    {
        using ThisT = BidirectionalIterator<TElement>;

        mpublic virtual void MoveBwd() const noexcept abstract;

        /// @brief move iterator to point to previous element
        /// @note calls MoveBwd()
        mpublic const ThisT ref operator --() const noexcept
        {
            MoveBwd();
            return ptr this;
        }

        /// @brief move iterator to point to previous element
        /// @note calls MoveBwd()
        mpublic ThisT ref operator --() noexcept
        {
            MoveBwd();
            return ptr this;
        }

        /// @brief move iterator to point to previous element
        /// @note calls MoveBwd()
        mpublic const ThisT ref operator --(int) const noexcept
        {
            MoveBwd();
            return ptr this;
        }

        /// @brief move iterator to point to previous element
        /// @note calls MoveBwd()
        mpublic ThisT ref operator --(int) noexcept
        {
            MoveBwd();
            return ptr this;
        }
    };
}