#pragma once
#include "SSEngine/Core.hpp"
#include "SSEngine/Collections/Comparer.hpp"
#include "SSEngine/Collections/Iterable.hpp"
#include "SSEngine/Collections/Collection.hpp"
#include "SSEngine/Collections/ArrayIterator.hpp"
#include <stdexcept>

namespace SSEngine
{
    /// @brief represents a collection that holds memory in contiguous order
    /// @tparam TElement type of element stored in array
    template <typename TElement>
    class Array : public virtual List<TElement>, public virtual IteratorIterable<ArrayIterator<TElement>>
    {
        using ListT = List<TElement>;

    public:
        using SizeType = typename ListT::SizeType;
        using ElementType = typename ListT::ElementType;
        using ComparerT = typename ListT::ComparerT;
        using EqualityComparerT = typename ListT::EqualityComparerT;
        using IterableT = Iterable<ElementType>;
        using IteratorT = ArrayIterator<ElementType>;
        using ForwardIteratorT = ForwardIterator<ElementType>;
        using IteratorPointerT = typename ListT::IteratorPointerT;
        using typename ListT::PredicateT;
        using ListT::NPOS;

    public:

        // *******************************************************************

        Array() noexcept = default;

        Array(const Iterable<ElementType> lref iterable) noexcept
        {
            InsertBack(iterable);
        }

        Array(const Collection<ElementType> lref list) noexcept
        {
            InsertBack(list);
        }

    public:

        // *******************************************************************

        virtual const ElementType lref operator[](SizeType index) const noexcept final override
        {
            return _array[index];
        }

        virtual ElementType lref operator[](SizeType index) noexcept final override
        {
            return _array[index];
        }

        // *******************************************************************

        virtual void ForEach(const Callable<void(const ElementType lref)> lref callback) const final override
        {
            for (SizeType i = 0; i < _count; i++)
            {
                callback(_array[i]);
            }
        }

        virtual void ForEach(const Callable<void(ElementType lref)> lref callback) final override
        {
            for (SizeType i = 0; i < _count; i++)
            {
                callback(_array[i]);
            }
        }

        virtual IteratorT Begin() noexcept final override
        {
            return IteratorT(_array + 0);
        }

        virtual const IteratorT Begin() const noexcept final override
        {
            return IteratorT(_array + 0);
        }

        virtual IteratorT End() noexcept final override
        {
            return IteratorT(_array + _count);
        }

        virtual const IteratorT End() const noexcept final override
        {
            return IteratorT(_array + _count);
        }

        // *******************************************************************

        virtual ElementType lref ElementAt(const SizeType index) final override
        {
            AssertIndex(index);

            return _array[index];
        }

        virtual const ElementType lref ElementAt(const SizeType index) const final override
        {
            AssertIndex(index);

            return _array[index];
        }

        // *******************************************************************

        ElementType ptr RawData() noexcept
        {
            return _array;
        }

        const ElementType ptr RawData() const noexcept
        {
            return _array;
        }

        // *******************************************************************

        virtual SizeType FirstIndexOf(const ElementType lref element, const EqualityComparerT lref comparer) const final override
        {
            for (SizeType i = 0; i < _count; i++)
            {
                if (comparer.Compare(_array[i], element) iseq true)
                {
                    return i;
                }
            }

            return NPOS;
        }

        virtual SizeType LastIndexOf(const ElementType lref element, const EqualityComparerT lref comparer) const final override
        {
            for (SizeType i = _count; i >= 0; i--)
            {
                if (comparer.Compare(_array[i], element) iseq true)
                {
                    return i;
                }
            }

            return NPOS;
        }

        // *******************************************************************

        virtual SizeType Count() const noexcept final override
        {
            return _count;
        }

        // *******************************************************************

        virtual void InsertAt(const SizeType index, const ElementType lref element) final override
        {
            AssertIndex(index);
            AssertCapacityFor(1);

            for (SizeType i = _count; i >= index; i--)
            {
                std::swap(_array[i], _array[i - 1]);
            }

            _count++;
            _array[index] = element;
        }

        virtual void InsertBack(const ElementType lref element) final override
        {
            AssertCapacityFor(1);
            _array[_count] = element;
            _count++;
        }

        virtual void RemoveBack() final override
        {
            AssertIndex(0);

            _array[_count] = ElementType();
            _count--;
        }

        // *******************************************************************

        virtual void InsertAt(const SizeType index, const ForwardIteratorT lref it, const SizeType count) final override
        {
            AssertIndex(index);
            AssertCapacityFor(count);

            for (SizeType i = _count; i >= index; i--)
            {
                std::swap(_array[i], _array[i + count]);
            }

            _count += count;
            for (SizeType i = index; i < count; i++)
            {
                _array[index] = ptr it;
                it++;
            }
        }

        // *******************************************************************

        virtual void RemoveAt(const SizeType index) final override
        {
            AssertIndex(index);

            for (SizeType i = index; i < _count; i++)
            {
                std::swap(_array[i], _array[i + 1]);
            }

            _array[_count] = ElementType();
            _count--;
        }

        // *******************************************************************

        virtual void RemoveFrom(const SizeType from, const SizeType to) final override
        {
            const SizeType count = to - from;
            for (SizeType i = from; i < (_count - count); i++)
            {
                _array[i] = _array[i + count];
            }

            for (SizeType i = (_count - count); i < _count; i++)
            {
                _array[i] = ElementType();
            }
            _count -= count;
        }

        // *******************************************************************

        virtual void RemoveIfCallable(const PredicateT lref pred) noexcept final override
        {
            SizeType count = _count;
            for (SizeType i = 0; i < count; i++)
            {
                if (pred(_array[i], SizeType(i)) iseq true)
                {
                    RemoveAt(i);

                    i--;
                    count--;
                }
            }
        }

        // *******************************************************************
    protected:

        void AssertIndex(const SizeType index) const
        {
            if (index > (_count - 1))
            {
                throw std::out_of_range("index was out of range");
            }
        }

        /// @brief checks capcity and resizes if required
        /// @param count count of elements to insert
        /// @note this function is called every time any number
        /// of elements are to be inserted irrelevance of their position
        void AssertCapacityFor(const SizeType count)
        {
            if (_count >= _capacity)
            {
                throw std::runtime_error("could not allocate memory for " + (_count + 1));
            }
        }

        // *******************************************************************

    protected:
        TElement ptr _array;
        SizeType _capacity;
        SizeType _count;
    };
}

template <typename TElement>
using SSArray = SSEngine::Array<TElement>;