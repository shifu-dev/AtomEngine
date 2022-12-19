#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/ForwardIteratorBox.hpp"
#include "AtomEngine/Containers/IBidirectionalIterator.hpp"

namespace Atom
{
    template <typename ElementT>
    class BidirectionalIteratorBox: public ForwardIteratorBox<ElementT>,
        public virtual IBidirectionalIterator<ElementT>
    {
        using ThisT = BidirectionalIteratorBox<ElementT>;
        using BaseT = ForwardIteratorBox<ElementT>;
        using BidirectionalIteratorT = IBidirectionalIterator<ElementT>;

    /// ----------------------------------------------------------------------------
    public:
        BidirectionalIteratorBox():
            BaseT(nullptr) { }

        BidirectionalIteratorBox(const ThisT& other) noexcept:
            BaseT(other) { }

        BidirectionalIteratorBox(ThisT&& other) noexcept:
            BaseT(move(other)) { }

        ThisT& operator = (const ThisT& other) noexcept
        {
            BaseT::operator = (other);
            return *this;
        }

        ThisT& operator = (ThisT&& other) noexcept
        {
            BaseT::operator = (move(other));
            return *this;
        }

        template <typename IteratorT>
        BidirectionalIteratorBox(const IteratorT& iterator) noexcept:
            BaseT(iterator)
        {
            StaticAssertSubClass<IteratorT, IteratorT>();
        }

        template <typename IteratorT>
        BidirectionalIteratorBox(IteratorT&& iterator) noexcept:
            BaseT(move(iterator))
        {
            StaticAssertSubClass<IteratorT, IteratorT>();
        }

    /// ----------------------------------------------------------------------------
    public:
        BidirectionalIteratorT& GetIterator() noexcept
        {
            return RCAST(IteratorT&, BaseT::GetIterator());
        }

        const BidirectionalIteratorT& GetIterator() const noexcept
        {
            return RCAST(const BidirectionalIteratorT&, BaseT::GetIterator());
        }

        void MoveBwd() const noexcept final
        {
            GetIterator().MoveBwd();
        }

    /// ----------------------------------------------------------------------------

        operator BaseT () const noexcept
        {
            return BaseT(*this);
        }
    };
}