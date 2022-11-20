#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/BoxedBidirectionalIterator.hpp"
#include "AtomEngine/Containers/RandomAccessIterator.hpp"

namespace Atom
{
    template <typename TElement>
    class BoxedRandomAccessIterator :
        public virtual BoxedBidirectionalIterator<TElement>,
        public virtual RandomAccessIterator<TElement>
    {
        using ThisT = BoxedRandomAccessIterator<TElement>;
        using BaseT = BoxedBidirectionalIterator<TElement>;
        using IteratorT = RandomAccessIterator<TElement>;

        /// ----------------------------------------------------------------------------

        mpublic BoxedRandomAccessIterator() : BaseT(null) { }

        mpublic BoxedRandomAccessIterator(const ThisT ref other) noexcept :
            BaseT(other) { }

        mpublic BoxedRandomAccessIterator(ThisT rref other) noexcept :
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
            BoxedRandomAccessIterator(const TIterator ref iterator) noexcept :
            BaseT(iterator)
        {
            StaticAssertSubClass<IteratorT, TIterator>();
        }

        mpublic template <typename TIterator>
            BoxedRandomAccessIterator(TIterator rref iterator) noexcept :
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

        mpublic virtual void MoveFwdBy(const sizet steps) const noexcept override
        {
            GetIterator().MoveFwdBy(steps);
        }

        mpublic virtual void MoveBwdBy(const sizet steps) const noexcept override
        {
            GetIterator().MoveBwdBy(steps);
        }

        /// ----------------------------------------------------------------------------

        mpublic operator BaseT () const noexcept
        {
            return BaseT(ptr this);
        }
    };
}