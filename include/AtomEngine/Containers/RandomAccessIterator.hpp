#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/BidirectionalIterator.hpp"

namespace Atom
{
    template <typename TElement>
    class RandomAccessIterator : public virtual BidirectionalIterator<TElement>
    {
        using ThisT = BidirectionalIterator<TElement>;

        mpublic virtual void MoveBwdBy(const sizet steps) const noexcept abstract;
        mpublic virtual void MoveFwdBy(const sizet steps) const noexcept abstract;

        mpublic virtual void MoveFwd() const noexcept override { MoveFwdBy(1); }
        mpublic virtual void MoveBwd() const noexcept override { MoveBwdBy(1); }

        mpublic ThisT ref operator + (const sizet steps) noexcept
        {
            MoveFwdBy(steps);
            return ptr this;
        }

        mpublic const ThisT ref operator + (const sizet steps) const noexcept
        {
            MoveFwdBy(steps);
            return ptr this;
        }

        mpublic ThisT ref operator - (const sizet steps) noexcept
        {
            MoveBwdBy(steps);
            return ptr this;
        }

        mpublic const ThisT ref operator - (const sizet steps) const noexcept
        {
            MoveBwdBy(steps);
            return ptr this;
        }
    };
}