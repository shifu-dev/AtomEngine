#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/BidirectionalIteratorBox.hpp"
#include "AtomEngine/Containers/IRandomAccessIterator.hpp"

namespace Atom
{
    template <typename ElementT>
    class RandomAccessIteratorBox:
        public virtual BidirectionalIteratorBox<ElementT>,
        public virtual IRandomAccessIterator<ElementT>
    {
        using ThisT = RandomAccessIteratorBox<ElementT>;
        using BaseT = BidirectionalIteratorBox<ElementT>;
        using RandomAccessIteratorT = IRandomAccessIterator<ElementT>;

    /// ----------------------------------------------------------------------------
    public:
        RandomAccessIteratorBox(): BaseT(nullptr) { }

        RandomAccessIteratorBox(const ThisT& other) noexcept:
            BaseT(other) { }

        RandomAccessIteratorBox(ThisT&& other) noexcept:
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

        template <typename ParamRandomAccessIteratorT>
        RandomAccessIteratorBox(const ParamRandomAccessIteratorT& iterator) noexcept:
            BaseT(iterator)
        {
            StaticAssertSubClass<IteratorT, ParamRandomAccessIteratorT>();
        }

        template <typename ParamRandomAccessIteratorT>
        RandomAccessIteratorBox(ParamRandomAccessIteratorT&& iterator) noexcept:
            BaseT(move(iterator))
        {
            StaticAssertSubClass<IteratorT, ParamRandomAccessIteratorT>();
        }

    /// ----------------------------------------------------------------------------
    public:
        RandomAccessIteratorT& GetIterator() noexcept
        {
            return RCAST(IteratorT&, BaseT::GetIterator());
        }

        const RandomAccessIteratorT& GetIterator() const noexcept
        {
            return RCAST(const RandomAccessIteratorT&, BaseT::GetIterator());
        }

        void MoveFwdBy(sizet steps) const noexcept final
        {
            GetIterator().MoveFwdBy(steps);
        }

        void MoveBwdBy(sizet steps) const noexcept final
        {
            GetIterator().MoveBwdBy(steps);
        }

    /// ----------------------------------------------------------------------------

        operator BaseT () const noexcept
        {
            return BaseT(*this);
        }
    };
}