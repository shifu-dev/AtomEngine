#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/BidirectionalIteratorBox.hpp"
#include "AtomEngine/Containers/IRandomAccessIterator.hpp"

namespace Atom
{
    template <typename TElement>
    class RandomAccessIteratorBox :
        public virtual BidirectionalIteratorBox<TElement>,
        public virtual IRandomAccessIterator<TElement>
    {
        using ThisT = RandomAccessIteratorBox<TElement>;
        using BaseT = BidirectionalIteratorBox<TElement>;
        using IRandomAccessIteratorT = IRandomAccessIterator<TElement>;

        /// ----------------------------------------------------------------------------

        mpublic RandomAccessIteratorBox() : BaseT(null) { }

        mpublic RandomAccessIteratorBox(const ThisT ref other) noexcept :
            BaseT(other) { }

        mpublic RandomAccessIteratorBox(ThisT rref other) noexcept :
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
            RandomAccessIteratorBox(const TIterator ref iterator) noexcept :
            BaseT(iterator)
        {
            StaticAssertSubClass<IteratorT, TIterator>();
        }

        mpublic template <typename TIterator>
            RandomAccessIteratorBox(TIterator rref iterator) noexcept :
            BaseT(move(iterator))
        {
            StaticAssertSubClass<IteratorT, TIterator>();
        }

        /// ----------------------------------------------------------------------------

        mpublic IRandomAccessIteratorT ref GetIterator() noexcept
        {
            return RCAST(IteratorT ref, BaseT::GetIterator());
        }

        mpublic const IRandomAccessIteratorT ref GetIterator() const noexcept
        {
            return RCAST(const IRandomAccessIteratorT ref, BaseT::GetIterator());
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