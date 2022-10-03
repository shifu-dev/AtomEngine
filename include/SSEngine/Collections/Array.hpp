#pragma once
#include "SSEngine/Core.hpp"
#include "SSEngine/Collections/Comparer.hpp"
#include "SSEngine/Collections/Iterable.hpp"
#include "SSEngine/Collections/Collection.hpp"
#include <stdexcept>

namespace SSEngine
{
    template <typename TValueType>
    class ArrayIterator;

    /// @brief represents a collection that holds memory in contiguous order
    /// @tparam TValueType type of element stored in array
    template <typename TValueType>
    class Array : public List<TValueType>
    {
        using CollectionT = Collection<TValueType>;

    public:
        using SizeT = typename CollectionT::SizeT;
        using ValueTypeT = typename CollectionT::ValueTypeT;
        using ComparerT = typename CollectionT::ComparerT;
        using IteratorT = ArrayIterator<TValueType>;
        using IteratorPointerT = IteratorPointer<TValueType>;
        static constexpr SizeT npos = -1;

    public:
        virtual IteratorT Begin()
        {
            return IteratorT(_array + 0);
        }

        virtual IteratorT End()
        {
            return IteratorT(_array + _count);
        }

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

        ValueTypeT ptr RawData() noexcept
        {
            return _array;
        }

        const ValueTypeT ptr RawData() const noexcept
        {
            return _array;
        }

        virtual SizeT IndexOf(const ValueTypeT lref element, const ComparerT lref comparer) const override
        {
            for (SizeT i = 0; i < _count; i++)
            {
                if (comparer.Compare(_array[i], element) iseq true)
                {
                    return i;
                }
            }

            return npos;
        }

        virtual SizeT Count() const noexcept override
        {
            return _count;
        }

        virtual void Insert(const ValueTypeT lref element) override
        {
            InsertBack(element);
        }

        virtual void Remove(const ValueTypeT lref element) override
        {
            // RemoveFront(element);
        }

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

        virtual void InsertBack(const ValueTypeT lref element)
        {
            AssertCapacityFor(1);
            _array[_count] = element;
            _count++;
        }

        virtual void RemoveBack(const ValueTypeT lref element)
        {
            if (_count > 0)
            {
                _array[_count] = ValueTypeT();
                _count--;
            }
        }

        virtual void Resize(const SizeT count)
        {
        }

    protected:
        virtual IteratorPointerT Iterable_begin() noexcept override
        {
            return IteratorPointerT(new IteratorT(_array + 0), _allocator);
        }

        virtual IteratorPointerT Iterable_end() noexcept override
        {
            return IteratorPointerT(new IteratorT(_array + (_count - 1)), _allocator);
        }

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
                Resize(_count + count);

                if (_count >= _capacity)
                {
                    throw std::runtime_error("could not allocate memory " + (_count + 1));
                }
            }
        }

    protected:
        Allocator _allocator;
        TValueType ptr _array;
        SizeT _capacity;
        SizeT _count;
    };

    /// @brief iterator for stack array
    /// @tparam TValueType type of element stack array holds
    template <typename TValueType>
    class ArrayIterator : public Iterator<TValueType>
    {
        using ValueTypeT = typename Array<TValueType>::ValueTypeT;
        using ThisT = ArrayIterator<ValueTypeT>;
        using BaseT = Iterator<TValueType>;

    public:
        ArrayIterator(TValueType ptr elementPtr)
            : _ptr(elementPtr) { }

        virtual TValueType lref operator *() override
        {
            return (ptr _ptr);
        }

        virtual Iterator<TValueType> lref operator ++() override
        {
            _ptr++;
            return (ptr this);
        }

        virtual bool operator ==(const Iterator<TValueType> lref rhs) override
        {
            // we convert to pointer to avoid exception try catch when cast fails
            auto rhsPtr = dynamic_cast<const ThisT ptr>(lref rhs);
            if (rhsPtr isnot nullptr)
            {
                return (ptr this) == (ptr rhsPtr);
            }

            return false;
        }

        bool operator ==(const ArrayIterator<TValueType> lref rhs)
        {
            return _ptr == rhs._ptr;
        }

    protected:
        ValueTypeT ptr _ptr;
    };
}

template <typename TValueType>
using SSArray = SSEngine::Array<TValueType>;