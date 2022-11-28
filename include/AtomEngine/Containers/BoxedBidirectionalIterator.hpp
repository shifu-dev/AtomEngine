#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/BoxedForwardIterator.hpp"
#include "AtomEngine/Containers/IBidirectionalIterator.hpp"

namespace Atom
{
    template <typename TElement>
    class BoxedBidirectionalIterator : public BoxedForwardIterator<TElement>,
        public virtual IBidirectionalIterator<TElement>
    {
        using ThisT = BoxedBidirectionalIterator<TElement>;
        using BaseT = BoxedForwardIterator<TElement>;
        using IBidirectionalIteratorT = IBidirectionalIterator<TElement>;

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

        mpublic IBidirectionalIteratorT ref GetIterator() noexcept
        {
            return RCAST(IteratorT ref, BaseT::GetIterator());
        }

        mpublic const IBidirectionalIteratorT ref GetIterator() const noexcept
        {
            return RCAST(const IBidirectionalIteratorT ref, BaseT::GetIterator());
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