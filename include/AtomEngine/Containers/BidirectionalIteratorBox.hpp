#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/ForwardIteratorBox.hpp"
#include "AtomEngine/Containers/IBidirectionalIterator.hpp"

namespace Atom
{
    template <typename TElement>
    class BidirectionalIteratorBox : public ForwardIteratorBox<TElement>,
        public virtual IBidirectionalIterator<TElement>
    {
        using ThisT = BidirectionalIteratorBox<TElement>;
        using BaseT = ForwardIteratorBox<TElement>;
        using IBidirectionalIteratorT = IBidirectionalIterator<TElement>;

        /// ----------------------------------------------------------------------------

        mpublic BidirectionalIteratorBox() : BaseT(null) { }

        mpublic BidirectionalIteratorBox(const ThisT ref other) noexcept :
            BaseT(other) { }

        mpublic BidirectionalIteratorBox(ThisT rref other) noexcept :
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
            BidirectionalIteratorBox(const TIterator ref iterator) noexcept :
            BaseT(iterator)
        {
            StaticAssertSubClass<IteratorT, TIterator>();
        }

        mpublic template <typename TIterator>
            BidirectionalIteratorBox(TIterator rref iterator) noexcept :
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