#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/IDynamicArray.hpp"
#include "AtomEngine/Containers/Internal/ArrayImpl.hpp"

namespace Atom
{
    template <typename ElementT>
    class DynamicArray: public Internal::ArrayImpl<ElementT>,
        public IDynamicArray<ElementT>
    {
        using ThisT = DynamicArray<ElementT>;
        using BaseT = Internal::ArrayImpl<ElementT>;
        using IDynamicArrayT = IDynamicArray<ElementT>;
        using InitializerListT = InitializerList<ElementT>;
        using IForwardIteratorT = IForwardIterator<ElementT>;
        using IConstIterableT = IConstIterable<ElementT>;
        using IConstCollectionT = IConstCollection<ElementT>;

    /// ----------------------------------------------------------------------------
    public:
        DynamicArray() noexcept:
            _allocator(DefaultAllocatorInstance)
        {
            _array = nullptr;
            _count = 0;
            _capacity = 0;
        }

        DynamicArray(sizet count): ThisT()
        {
            Resize(count);
        }

        DynamicArray(const InitializerListT list): ThisT()
        {
            InsertFront(list);
        }

        DynamicArray(const IForwardIteratorT& it, sizet count): ThisT()
        {
            InsertFront(it, count);
        }

        DynamicArray(const IForwardIteratorT& begin, const IForwardIteratorT& end): ThisT()
        {
            InsertFront(begin, end);
        }

        DynamicArray(const IConstIterableT& elements, sizet count): ThisT()
        {
            InsertFront(elements, count);
        }

        DynamicArray(const IConstIterableT& elements): ThisT()
        {
            InsertFront(elements);
        }

        DynamicArray(const IConstCollectionT& elements): ThisT()
        {
            InsertFront(elements);
        }

        DynamicArray(const ThisT& other) noexcept = default;
        DynamicArray(ThisT&& other) noexcept = default;

        ThisT& operator = (const ThisT& other) noexcept = default;
        ThisT& operator = (ThisT&& other) noexcept = default;

        ~DynamicArray()
        {
            Clear();
            ShrinkToFit();
        }

    /// ----------------------------------------------------------------------------
    /// IDynamicCollection
    public:
        using BaseT::Clear;

        void Resize(sizet count) final
        {
            count = max(count, _count);
            if (count != _capacity)
            {
                _array = _allocator.Reallocate<ElementT>(_array, count);
            }
        }

        sizet Reserve(sizet count) final
        {
            if (_capacity - _count < count)
            {
                _allocator.Reallocate<ElementT>(_array, _capacity - _count + count);
            }

            return _capacity - _count;
        }

        void ShrinkToFit() final
        {
            return Resize(_count);
        }

    protected:
        using BaseT::_array;
        using BaseT::_count;
        using BaseT::_capacity;

        IAllocator& _allocator;
    };
}