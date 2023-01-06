#pragma once
#include "AtomEngine/Containers/IIterable.hpp"

namespace Atom
{
    template <typename ElementT>
    interface IConstBidirectionalIterable:
        public virtual IConstIterable<ElementT>
    {
        using IConstIterableT = IConstIterable<ElementT>;
        using IConstBidirectionalIteratorT = IConstIterator<ElementT>;
        using ConstIterateActionT = IInvokable<void(const IConstBidirectionalIteratorT&)>;

    public:
        using IConstIterableT::Iterate;

        virtual void Iterate(ConstIterateActionT& action) const = 0;
    };

    template <typename ElementT>
    interface IBidirectionalIterable:
        public virtual IConstBidirectionalIterable<ElementT>,
        public virtual IIterable<ElementT>
    {
        using IIterableT = IIterable<ElementT>;
        using IBidirectionalIteratorT = IConstIterator<ElementT>;
        using ConstIterateActionT = IInvokable<void(const IBidirectionalIteratorT&)>;

    public:
        using IIterableT::Iterate;

        virtual void Iterate(ConstIterateActionT& action) const = 0;
    };
}