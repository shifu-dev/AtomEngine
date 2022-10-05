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
    /// @tparam TValueType type of element stored in array
    template <typename TValueType>
    class Array : public virtual List<TValueType>, public virtual IteratorIterable<ArrayIterator<TValueType>>
    {
        using ListT = List<TValueType>;

    public:
        using SizeT = typename ListT::SizeT;
        using ValueTypeT = typename ListT::ValueTypeT;
        using ComparerT = typename ListT::ComparerT;
        using EqualityComparerT = typename ListT::EqualityComparerT;
        using IterableT = Iterable<ValueTypeT>;
        using IteratorT = ArrayIterator<ValueTypeT>;
        using ForwardIteratorT = ForwardIterator<ValueTypeT>;
        using IteratorPointerT = typename ListT::IteratorPointerT;
        using ListT::NPOS;

    public:

        // *******************************************************************

        Array() noexcept = default;

        Array(const Iterable<ValueTypeT> lref iterable) noexcept
        {
            InsertBack(iterable);
        }

        Array(const Collection<ValueTypeT> lref list) noexcept
        {
            InsertBack(list);
        }

    public:

        // *******************************************************************

        virtual const ValueTypeT lref operator[](SizeT index) const noexcept
        {
            return _array[index];
        }

        virtual ValueTypeT lref operator[](SizeT index) noexcept
        {
            return _array[index];
        }

        // *******************************************************************

        virtual IteratorT Begin() noexcept override
        {
            return IteratorT(_array + 0);
        }

        virtual const IteratorT Begin() const noexcept override
        {
            return IteratorT(_array + 0);
        }

        virtual IteratorT End() noexcept override
        {
            return IteratorT(_array + _count);
        }

        virtual const IteratorT End() const noexcept override
        {
            return IteratorT(_array + _count);
        }

        // *******************************************************************

        virtual ValueTypeT lref ElementAt(const SizeT index) override
        {
            AssertIndex(index);

            return _array[index];
        }

        virtual const ValueTypeT lref ElementAt(const SizeT index) const override
        {
            AssertIndex(index);

            return _array[index];
        }

        // *******************************************************************

        ValueTypeT ptr RawData() noexcept
        {
            return _array;
        }

        const ValueTypeT ptr RawData() const noexcept
        {
            return _array;
        }

        // *******************************************************************

        virtual SizeT FirstIndexOf(const ValueTypeT lref element, const EqualityComparerT lref comparer) const override
        {
            for (SizeT i = 0; i < _count; i++)
            {
                if (comparer.Compare(_array[i], element) iseq true)
                {
                    return i;
                }
            }

            return NPOS;
        }

        virtual SizeT LastIndexOf(const ValueTypeT lref element, const EqualityComparerT lref comparer) const override
        {
            for (SizeT i = _count; i >= 0; i--)
            {
                if (comparer.Compare(_array[i], element) iseq true)
                {
                    return i;
                }
            }

            return NPOS;
        }

        // *******************************************************************

        virtual SizeT Count() const noexcept override
        {
            return _count;
        }

        // *******************************************************************

        virtual void InsertAt(const SizeT index, const ValueTypeT lref element) override
        {
            AssertIndex(index);
            AssertCapacityFor(1);

            for (SizeT i = _count; i >= index; i--)
            {
                std::swap(_array[i], _array[i - 1]);
            }

            _count++;
            _array[index] = element;
        }

        virtual void InsertBack(const ValueTypeT lref element) override
        {
            AssertCapacityFor(1);
            _array[_count] = element;
            _count++;
        }

        virtual void RemoveBack() override
        {
            AssertIndex(0);

            _array[_count] = ValueTypeT();
            _count--;
        }

        // *******************************************************************

        virtual void InsertAt(const SizeT index, const ForwardIteratorT lref it, const SizeT count) override
        {
            AssertIndex(index);
            AssertCapacityFor(count);

            for (SizeT i = _count; i >= index; i--)
            {
                std::swap(_array[i], _array[i + count]);
            }

            _count += count;
            for (SizeT i = index; i < count; i++)
            {
                _array[index] = ptr it;
                it++;
            }
        }

        // *******************************************************************

        virtual void RemoveAt(const SizeT index) override
        {
            AssertIndex(index);

            for (SizeT i = index; i < _count; i++)
            {
                std::swap(_array[i], _array[i + 1]);
            }

            _array[_count] = ValueTypeT();
            _count--;
        }

        // *******************************************************************

        virtual void RemoveFrom(const SizeT from, const SizeT to)
        {
            const SizeT count = to - from;
            for (SizeT i = from; i < (_count - count); i++)
            {
                _array[i] = _array[i + count];
            }

            for (SizeT i = (_count - count); i < _count; i++)
            {
                _array[i] = ValueTypeT();
            }
            _count -= count;
        }

    protected:

        // *******************************************************************

        void AssertIndex(const SizeT index) const
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
        void AssertCapacityFor(const SizeT count)
        {
            if (_count >= _capacity)
            {
                throw std::runtime_error("could not allocate memory for " + (_count + 1));
            }
        }

        // *******************************************************************

    protected:
        TValueType ptr _array;
        SizeT _capacity;
        SizeT _count;
    };
}

template <typename TValueType>
using SSArray = SSEngine::Array<TValueType>;