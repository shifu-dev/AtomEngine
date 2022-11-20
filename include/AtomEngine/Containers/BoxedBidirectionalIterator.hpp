#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/BoxedForwardIterator.hpp"
#include "AtomEngine/Containers/BidirectionalIterator.hpp"

namespace Atom
{
    template <typename TElement>
    class BoxedBidirectionalIterator :
        public virtual BoxedForwardIterator<TElement>,
        public virtual BidirectionalIterator<TElement>
    {
        using ThisT = BoxedBidirectionalIterator<TElement>;
        using BaseT = BoxedForwardIterator<TElement>;
        using IteratorT = BidirectionalIterator<TElement>;

        /// ----------------------------------------------------------------------------

        mpublic BoxedBidirectionalIterator() : BaseT(null) { }

        mpublic BoxedBidirectionalIterator(const ThisT ref other) noexcept :
            BaseT(other) { }

        mpublic BoxedBidirectionalIterator(ThisT rref other) noexcept :
            BaseT(move(other)) { }

        mpublic ThisT ref operator = (const ThisT ref other) noexcept
        {
            BaseT::operator = (other);
            return ptr this;
        }

        mpublic ThisT ref operator = (ThisT rref other) noexcept
        {
            BaseT::operator = (move(other));
            return ptr this;
        }

        mpublic template <typename TIterator>
            BoxedBidirectionalIterator(const TIterator ref iterator) noexcept :
            BaseT(iterator)
        {
            StaticAssertSubClass<IteratorT, TIterator>();
        }

        mpublic template <typename TIterator>
            BoxedBidirectionalIterator(TIterator rref iterator) noexcept :
            BaseT(move(iterator))
        {
            StaticAssertSubClass<IteratorT, TIterator>();
        }

        /// ----------------------------------------------------------------------------

        mpublic IteratorT ref GetIterator() noexcept
        {
            return rcast<IteratorT ref>(BaseT::GetIterator());
        }

        mpublic const IteratorT ref GetIterator() const noexcept
        {
            return rcast<const IteratorT ref>(BaseT::GetIterator());
        }

        mpublic virtual void MoveBwd() const noexcept override
        {
            GetIterator().MoveBwd();
        }

        /// ----------------------------------------------------------------------------

        mpublic operator BaseT () const noexcept
        {
            return BaseT(ptr this);
        }
    };
}