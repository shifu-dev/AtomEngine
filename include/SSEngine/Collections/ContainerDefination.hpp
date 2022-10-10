#pragma once
#include "SSEngine/Core.hpp"

namespace SSEngine
{
    template <typename TElement>
    class ContainerDefination
    {
    public:
        using SizeT = sizet;
        using ElementT = TElement;

        using IterableT = Iterable<ElementT>;
        using CollectionT = Collection<ElementT>;
        using ListT = List<ElementT>;
        using ArrayT = Array<ElementT>;

        using IteratorT = Iterator<ElementT>;
        using ForwardIteratorT = ForwardIterator<ElementT>;
        using BidirectionalIteratorT = BidirectionalIterator<ElementT>;
        using RandomAccessIteratorT = RandomAccessIterator<ElementT>;
        using ArrayIteratorT = ArrayIterator<ElementT>;

        using IteratorPointerT = IteratorPointer<ElementT>;
        using ForwardIteratorPointerT = ForwardIteratorPointer<ElementT>;
        using BidirectionalIteratorPointerT = BidirectionalIteratorPointer<ElementT>;
        using RandomAccessIteratorPointerT = RandomAccessIteratorPointer<ElementT>;

        using ComparerT = Comparer<ElementT>;
        using EqualityComparerT = EqualityComparer<ElementT>;
        using DefaultEqualityComparerT = DefaultEqualityComparer<ElementT>;

        using AllocatorT = Allocator;

        using InitializerListT = std::initializer_list<ElementT>;

        static constexpr SizeT NPOS = -1;
    };
}