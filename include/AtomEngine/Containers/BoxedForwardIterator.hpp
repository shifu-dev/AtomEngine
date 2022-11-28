#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/BoxedIterator.hpp"
#include "AtomEngine/Containers/IForwardIterator.hpp"

namespace Atom
{
    template <typename TElement>
    class BoxedForwardIterator : public BoxedIterator<TElement>,
        public virtual IForwardIterator<TElement>
    {
        using ThisT = BoxedForwardIterator<TElement>;
        using BaseT = BoxedIterator<TElement>;
        using IForwardIteratorT = IForwardIterator<TElement>;

        /// ----------------------------------------------------------------------------

        mpublic BoxedForwardIterator() : BaseT(null) { }

        mpublic BoxedForwardIterator(const ThisT ref other) noexcept :
            BaseT(other) { }

        mpublic BoxedForwardIterator(ThisT rref other) noexcept :
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
            BoxedForwardIterator(const TIterator ref iterator) noexcept :
            BaseT(iterator)
        {
            StaticAssertSubClass<IForwardIteratorT, TIterator>();
        }

        mpublic template <typename TIterator>
            BoxedForwardIterator(TIterator rref iterator) noexcept :
            BaseT(move(iterator))
        {
            StaticAssertSubClass<IForwardIteratorT, TIterator>();
        }

        /// ----------------------------------------------------------------------------

        mpublic IForwardIteratorT ref GetIterator() noexcept
        {
            return RCAST(IForwardIteratorT ref, BaseT::GetIterator());
        }

        mpublic const IForwardIteratorT ref GetIterator() const noexcept
        {
            return RCAST(const IForwardIteratorT ref, BaseT::GetIterator());
        }

        mpublic virtual void MoveFwd() const noexcept override
        {
            GetIterator().MoveFwd();
        }

        /// ----------------------------------------------------------------------------

        mpublic operator BaseT () const noexcept
        {
            return BaseT(ptr this);
        }
    };
}