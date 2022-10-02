#pragma once
#include "SSEngine/Core.hpp"

namespace SSEngine
{
    /// @brief pointer to iterator to provide iterface ability to Iterable
    /// @note this class acts like a unique ptr with functionality of iterators
    /// @tparam TValueType 
    template <typename TValueType>
    class IteratorPointer : public Iterator<TValueType>
    {
    public:
        /// @brief type of impl iterator
        using TIterator = Iterator<TValueType>;

        /// @todo inherit doc from base class
        using ValueType = typename TIterator::ValueType;

    protected:
        /// @brief pointer to the implementation iterator
        TIterator ptr _iterator;

        /// @brief alloctor to manage impl iterator reference
        Allocator lref _allocator;

    public:
        /// @brief default constructor initializes impl iterator with null
        IteratorPointer() : IteratorPointer(nullptr) { }

        /// @brief initializes impl iterator with specified iterator pointer
        /// @param iterator pointer to iterator
        /// @param allocator allocator used to manage pointer to iterator
        IteratorPointer(TIterator ptr iterator, Allocator lref allocator)
            : _iterator(iterator), _allocator(allocator) { }

        /// @brief destructor destroys impl iterator using @param _allocator 
        dtor IteratorPointer()
        {
            // _allocator.Deallocate(_iterator);
        }

        virtual TIterator lref operator ++() override
        {
            return ++(ptr _iterator);
        }

        virtual bool operator ==(const TIterator lref rhs) override
        {
            return (ptr this == rhs);
        }

        virtual TValueType lref operator ptr() override
        {
            return ptr(ptr _iterator);
        }
    };
}

template <typename TValueType>
using SSIteratorPointer = SSEngine::IteratorPointer<TValueType>;