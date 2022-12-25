#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/IConstArray.hpp"

namespace Atom::Internal
{
    template <typename ElementT>
    class ConstArrayImpl:
        public virtual IConstArray<ElementT>
    {
        using IConstListT = IConstList<ElementT>;
        using ConstForwardIteratorBoxT = ConstForwardIteratorBox<ElementT>;
        using ConstArrayIteratorT = ConstArrayIterator<ElementT>;
        using EqualityComparerT = IEqualityComparer<ElementT>;

    /// ----------------------------------------------------------------------------
    /// IConstArray
    public:
        const ElementT* Data() const noexcept override final
        {
            return _array;
        }

        ConstArrayIteratorT Begin() const noexcept override final
        {
            return ConstArrayIteratorT(_array + 0);
        }

        ConstArrayIteratorT End() const noexcept override final
        {
            return ConstArrayIteratorT(_array + _count);
        }

    /// ----------------------------------------------------------------------------
    /// IConstList
    public:
        const ElementT& operator[](sizet index) const noexcept override final
        {
            return _array[index];
        }

        using IConstListT::FirstIndexOf;

        sizet FirstIndexOf(const ElementT& element, const EqualityComparerT& comparer) const noexcept override final
        {
            for (sizet i = 0; i < _count; i++)
            {
                if (comparer.Compare(_array[i], element) == true)
                {
                    return i;
                }
            }

            return NPOS;
        }

        using IConstListT::LastIndexOf;

        sizet LastIndexOf(const ElementT& element, const EqualityComparerT& comparer) const noexcept override final
        {
            for (sizet i = _count; i >= 0; i--)
            {
                if (comparer.Compare(_array[i], element) == true)
                {
                    return i;
                }
            }

            return NPOS;
        }

    /// ----------------------------------------------------------------------------
    protected:
        void _AssertIndexIsInBounds(sizet index) const override final
        {
            _AssertIndexIsInBounds(index, "Index was out of range");
        }

        void _AssertIndexIsInBounds(sizet index, const char* msg) const
        {
            if (index >= _count)
            {
                throw std::out_of_range("Index was out of range");
            }
        }

    /// ----------------------------------------------------------------------------
    /// IConstCollection
    public:
        sizet Count() const noexcept override final
        {
            return _count;
        }

    /// ----------------------------------------------------------------------------
    /// IIterable
    protected:
        ConstForwardIteratorBoxT _IterableBegin() const noexcept override final
        {
            return ConstForwardIteratorBoxT(Begin());
        }

        ConstForwardIteratorBoxT _IterableEnd() const noexcept override final
        {
            return ConstForwardIteratorBoxT(End());
        }

    /// ----------------------------------------------------------------------------
    protected:
        ElementT* _array;
        sizet _count;
    };
}