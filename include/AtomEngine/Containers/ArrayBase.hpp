#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/IArray.hpp"
#include "AtomEngine/Containers/ConstArrayBase.hpp"

namespace Atom
{
    /// Represents a collection that holds memory in contiguous order.
    /// 
    /// @tparam ElementT Type of element this array contains.
    template <typename ElementT>
    class ArrayBase: public ConstArrayBase<ElementT>,
        public virtual IArray<ElementT>
    {
        using ThisT = ArrayBase<ElementT>;
        using BaseT = ConstArrayBase<ElementT>;
        using ConstElementT = const ElementT;
        using PredicateT = IPredicate<ConstElementT&, sizet>;
        using FwdIteratorT = IForwardIterator<ElementT>;
        using FwdIteratorBoxT = ForwardIteratorBox<ElementT>;
        using ArrayIteratorT = ArrayIterator<ElementT>;
        using ForEachActionT = ILoopAction<ElementT&>;

    /// ----------------------------------------------------------------------------
    /// IArray
    public:
        /// @return Pointer to the underlying array.
        ElementT* Data() noexcept final
        {
            return _array;
        }

        ArrayIteratorT Begin() noexcept final
        {
            return ArrayIteratorT(_array + 0);
        }

        ArrayIteratorT End() noexcept final
        {
            return ArrayIteratorT(_array + _count);
        }

    /// ----------------------------------------------------------------------------
    /// IList
    public:
        ElementT& operator[](sizet index) noexcept final
        {
            return _array[index];
        }

        void InsertAt(sizet index, ConstElementT& element) final
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

        void InsertBack(ConstElementT& element) final
        {
            _AssertCapacityFor(1);

            _array[_count] = element;
            _count++;
        }

        void RemoveBack() final
        {
            _AssertIndexIsInBounds(0);

            _array[_count] = ElementT();
            _count--;
        }

        void InsertAt(sizet index, const FwdIteratorT& it, sizet count) final
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

        void RemoveAt(sizet index) final
        {
            _AssertIndexIsInBounds(index);

            for (sizet i = index; i < _count; i++)
            {
                swap(_array[i], _array[i + 1]);
            }

            _array[_count] = ElementT();
            _count--;
        }

        void RemoveFrom(sizet from, sizet to) final
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

        void RemoveIfCallable(const PredicateT& pred) noexcept final
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
        sizet Capacity() const noexcept final
        {
            return _capacity;
        }

    /// ----------------------------------------------------------------------------
    /// IIterable
    public:
        void ForEach(ForEachActionT& callback) final
        {
            for (sizet i = 0; i < _count; i++)
            {
                callback(_array[i]);
            }
        }

    protected:
        FwdIteratorBoxT _IterableBegin() noexcept final
        {
            return FwdIteratorBoxT(Begin());
        }

        FwdIteratorBoxT _IterableEnd() noexcept final
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