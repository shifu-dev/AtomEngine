#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/IArray.hpp"
#include "AtomEngine/Containers/Internal/ConstArrayImpl.hpp"

namespace Atom::Internal
{
    /// Represents a collection that holds memory in contiguous order.
    /// 
    /// @tparam ElementT Type of element this array contains.
    template <typename ElementT>
    class ArrayImpl: public Internal::ConstArrayImpl<ElementT>,
        public virtual IArray<ElementT>
    {
        using BaseT = Internal::ConstArrayImpl<ElementT>;
        using PredicateT = IPredicate<const ElementT&, sizet>;
        using ConstFwdIteratorT = IConstForwardIterator<ElementT>;
        using FwdIteratorBoxT = ForwardIteratorBox<ElementT>;
        using ArrayIteratorT = ArrayIterator<ElementT>;

    public:
        /// @todo Resolve ambiguity between IConstCollection::Count and ConstArrayImpl::Count.
        using BaseT::Count;

    /// ----------------------------------------------------------------------------
    /// IArray
    public:
        /// @return Pointer to the underlying array.
        ElementT* Data() noexcept override final
        {
            return _array;
        }

        ArrayIteratorT Begin() noexcept override final
        {
            return ArrayIteratorT(_array + 0);
        }

        ArrayIteratorT End() noexcept override final
        {
            return ArrayIteratorT(_array + _count);
        }

    /// ----------------------------------------------------------------------------
    /// IList
    public:
        ElementT& operator[](sizet index) noexcept override final
        {
            return _array[index];
        }

        void InsertAt(sizet index, const ElementT& element) override final
        {
            _AssertIndexIsInBounds(index);
            _AssertCapacityFor(1);

            for (sizet i = _count; i >= index; i--)
            {
                swap(_array[i], _array[i - 1]);
            }

            _count++;
            _array[index] = element;
        }

        void InsertBack(const ElementT& element) override final
        {
            _AssertCapacityFor(1);

            _array[_count] = element;
            _count++;
        }

        void RemoveBack() override final
        {
            _AssertIndexIsInBounds(0);

            _array[_count] = ElementT();
            _count--;
        }

        void InsertAt(sizet index, ConstFwdIteratorT& it, sizet count) override final
        {
            _AssertIndexIsInBounds(index);
            _AssertCapacityFor(count);

            for (sizet i = _count; i >= index; i--)
            {
                swap(_array[i], _array[i + count]);
            }

            _count += count;
            for (sizet i = index; i < count; i++)
            {
                _array[index] = *it;
                it.MoveFwd();
            }
        }

        void RemoveAt(sizet index) override final
        {
            _AssertIndexIsInBounds(index);

            for (sizet i = index; i < _count; i++)
            {
                swap(_array[i], _array[i + 1]);
            }

            _array[_count] = ElementT();
            _count--;
        }

        void RemoveFrom(sizet from, sizet to) override final
        {
            sizet count = to - from;
            for (sizet i = from; i < (_count - count); i++)
            {
                _array[i] = _array[i + count];
            }

            for (sizet i = (_count - count); i < _count; i++)
            {
                _array[i] = ElementT();
            }
            _count -= count;
        }

        void RemoveIfInvokable(PredicateT&& pred) noexcept override final
        {
            sizet count = _count;
            for (sizet i = 0; i < count; i++)
            {
                if (pred(_array[i], sizet(i)) == true)
                {
                    RemoveAt(i);

                    i--;
                    count--;
                }
            }
        }

    /// ----------------------------------------------------------------------------
    /// ICollection
    public:
        sizet Capacity() const noexcept override final
        {
            return _capacity;
        }

    /// ----------------------------------------------------------------------------
    /// IIterable
    protected:
        FwdIteratorBoxT _IterableBegin() noexcept override final
        {
            return FwdIteratorBoxT(Begin());
        }

        FwdIteratorBoxT _IterableEnd() noexcept override final
        {
            return FwdIteratorBoxT(End());
        }

    /// ----------------------------------------------------------------------------
    protected:
        using BaseT::_AssertIndexIsInBounds;

        /// @brief checks capcity and resizes if required
        /// @param count count of elements to insert
        /// @note this function == called every time any number
        /// of elements are to be inserted irrelevance of their position
        void _AssertCapacityFor(sizet count) const
        {
            if (_count >= _capacity)
            {
                throw std::runtime_error("could not allocate memory for " + (_count + 1));
            }
        }

    /// ----------------------------------------------------------------------------
    protected:
        using BaseT::_array;
        using BaseT::_count;

        sizet _capacity;
    };
}