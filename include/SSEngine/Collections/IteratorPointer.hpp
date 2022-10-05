#pragma once
#include "SSEngine/Core.hpp"

namespace SSEngine
{
    /// @brief pointer to iterator to provide iterface ability to Iterable
    /// @note this class acts like a unique ptr with functionality of iterators
    /// @tparam TValueType 
    template <typename TValueType>
    class ForwardIteratorPointer : public ForwardIterator<TValueType>
    {
    public:
        /// @brief type of impl iterator
        using IteratorT = Iterator<TValueType>;

        /// @brief type of impl iterator
        using ForwardIteratorT = ForwardIterator<TValueType>;

        /// @todo inherit doc from base class
        using ValueTypeT = typename ForwardIteratorT::ValueTypeT;

        using AllocatorT = Allocator;

    protected:
        /// @brief pointer to the implementation iterator
        ForwardIteratorT ptr _iterator;

        /// @brief alloctor to manage impl iterator reference
        AllocatorT lref _allocator;

    public:
        /// @brief default constructor initializes impl iterator with null
        ForwardIteratorPointer() : ForwardIteratorPointer(nullptr) { }

        /// @brief initializes impl iterator with specified iterator pointer
        /// @param iterator pointer to iterator
        /// @param allocator allocator used to manage pointer to iterator
        ForwardIteratorPointer(ForwardIteratorT ptr iterator, AllocatorT lref allocator)
            : _iterator(iterator), _allocator(allocator) { }

        /// @brief destructor destroys impl iterator using @param _allocator 
        dtor ForwardIteratorPointer()
        {
            // _allocator.Deallocate(_iterator);
        }

        virtual ValueTypeT lref Value() noexcept override
        {
            return _iterator->Value();
        }

        virtual const ValueTypeT lref Value() const noexcept override
        {
            return _iterator->Value();
        }

        virtual void MoveFwd() const noexcept override
        {
            _iterator->MoveFwd();
        }

        virtual int Compare(const IteratorT lref rhs) const noexcept override
        {
            return _iterator->Compare(rhs);
        }
    };
}