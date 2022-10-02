#pragma once
#include "SSEngine/Core.hpp"
#include "SSEngine/Collections/Iterable.hpp"
#include "SSEngine/Collections/Collection.hpp"
#include <stdexcept>

namespace SSEngine
{
    template <typename TValueType, umax TSize>
    class StackArray;

    template <typename TValueType>
    class StackArrayIterator;

    /// @brief stack allocated non-resiable array
    /// @tparam TValueType type of value stored in array
    /// @tparam TSize size of array, this cannot be changed
    template <typename TValueType, umax TSize>
    class StackArray : public DynamicList<TValueType>
    {
        using CollectionT = Collection<TValueType>;

    public:
        using SizeT = typename CollectionT::SizeT;
        using ValueTypeT = typename CollectionT::ValueTypeT;
        using IteratorT = StackArrayIterator<TValueType>;
        using IteratorPointerT = IteratorPointer<TValueType>;

        // ************************************************************************
        // * Iterable<TValueType> | BEGIN

    protected:

        virtual IteratorPointerT Iterable_begin() noexcept override
        {
            return IteratorPointerT(new IteratorT(_array + 0), _allocator);
        }

        virtual IteratorPointerT Iterable_end() noexcept override
        {
            return IteratorPointerT(new IteratorT(_array + (_count - 1)), _allocator);
        }

        // * Iterable<TValueType> | END
        // ************************************************************************

        // ************************************************************************
        // * Collection<TValueType> | BEGIN

    public:

        virtual void Push(const ValueTypeT lref value) override
        {
            // TODO: implement this
        }

        virtual void Remove(const ValueTypeT lref value) override
        {
            // TODO: implement this
        }

        virtual bool Contains(const ValueTypeT lref value) const noexcept override
        {
            for (SizeT i = 0; i < _count; i++)
            {
                if (value == _array[i])
                {
                    return true;
                }
            }

            return false;
        }

        virtual SizeT Count() const noexcept override
        {
            return _count;
        }

        // * Collection<TValueType> | END
        // ************************************************************************

        // ************************************************************************
        // * DynamicCollection<TValueType> | BEGIN

    public:

        virtual void Resize(const SizeT count) override { }

        virtual SizeT Reserve(const SizeT count) override { return 0; }

        virtual SizeT Capacity() override { return 0; }

        // ************************************************************************
        // * DynamicCollection<TValueType> | END

        // * List<TValueType> | BEGIN
        // ************************************************************************

    public:

        virtual const ValueTypeT lref ElementAt(const SizeT index) const override
        {
            AssertIndex(index);

            return _array[index];
        }

        virtual SizeT IndexOf(const ValueTypeT lref element) const override
        {
            for (SizeT i = 0; i < _count; i++)
            {
                if (_array[i] iseq element)
                {
                    return i;
                }
            }

            return -1;
        }

        virtual ValueTypeT lref ElementAt(const SizeT index) override
        {
            AssertIndex(index);

            return _array[index];
        }

        virtual void InsertAt(const SizeT index, const ValueTypeT lref element) override { }

        virtual void RemoveAt(const SizeT index) override { }

        // ************************************************************************
        // * List<TValueType> | END

    protected:
        void AssertIndex(const SizeT index) const
        {
            if (index > (_count - 1))
            {
                throw std::out_of_range("index was out of range");
            }
        }

    protected:
        Allocator _allocator;
        TValueType _array[TSize];
        SizeT _count;
    };

    /// @brief iterator for stack array
    /// @tparam TValueType type of value stack array holds
    template <typename TValueType>
    class StackArrayIterator : public Iterator<TValueType>
    {
        using ValueTypeT = typename StackArray<TValueType, 0>::ValueTypeT;
        using ThisT = StackArrayIterator<ValueTypeT>;
        using BaseT = Iterator<TValueType>;

    public:
        StackArrayIterator(TValueType ptr valuePtr)
            : _ptr(valuePtr) { }

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

        bool operator ==(const StackArrayIterator<TValueType> lref rhs)
        {
            return _ptr == rhs._ptr;
        }

    protected:
        ValueTypeT ptr _ptr;
    };
}

template <typename TValueType, umax TSize>
using SSStackArray = SSEngine::StackArray<TValueType, TSize>;