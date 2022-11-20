#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/Iterator.hpp"

namespace Atom
{
    template <typename TElement>
    class ForwardIterator : public virtual Iterator<TElement>
    {
        using ThisT = ForwardIterator<TElement>;

        /// @brief move iterator to point to next element
        mpublic virtual void MoveFwd() const noexcept abstract;

        /// @brief move iterator to point to next element
        /// @note calls MoveFwd()
        mpublic const ThisT ref operator ++() const noexcept
        {
            MoveFwd();
            return ptr this;
        }

        /// @brief move iterator to point to next element
        /// @note calls MoveFwd()
        mpublic ThisT ref operator ++() noexcept
        {
            MoveFwd();
            return ptr this;
        }

        /// @brief move iterator to point to next element
        /// @note calls MoveFwd()
        mpublic const ThisT ref operator ++(int) const noexcept
        {
            MoveFwd();
            return ptr this;
        }

        /// @brief move iterator to point to next element
        /// @note calls MoveFwd()
        mpublic ThisT ref operator ++(int) noexcept
        {
            MoveFwd();
            return ptr this;
        }
    };
}