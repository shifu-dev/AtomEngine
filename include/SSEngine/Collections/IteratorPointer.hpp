#pragma once
#include "SSEngine/Core.hpp"

namespace SSEngine
{
    /// @brief pointer to iterator to provide iterface ability to Iterable
    /// @note this class acts like a unique ptr with functionality of iterators
    /// @tparam TValueType type of value iterator points to
    template <typename TValueType>
    class IteratorPointer :
        public virtual Iterator<TValueType>
    {
        using SizeT = sizet;
        using ThisT = IteratorPointer<TValueType>;

    public:
        /// @brief type of impl iterator
        using IteratorT = Iterator<TValueType>;

        /// @todo inherit doc from base class
        using ValueTypeT = typename IteratorT::ValueTypeT;

        /// @brief allocator type used to manage iterator ptr
        using AllocatorT = Allocator;

    public:

        // *******************************************************************

        /// @brief default constructor initializes impl iterator with null
        IteratorPointer() noexcept :
            _allocator(), _iterator(nullptr) { }

        template <typename TIterator>
        IteratorPointer(const TIterator lref iterator) noexcept :
            ThisT(lref iterator, sizeof(TIterator)) { }

        IteratorPointer(const IteratorT ptr iterator, const SizeT size) noexcept
        {
            _allocator = AllocatorT();
            _iteratorSize = size;
            _iterator = static_cast<IteratorT ptr>(
                _allocator.AllocateRaw(_iteratorSize, false));
        }

        IteratorPointer(const ThisT lref other) noexcept
        {
            _allocator = AllocatorT();
            _iteratorSize = other._iteratorSize;
            _iterator = static_cast<IteratorT ptr>(
                _allocator.AllocateRaw(_iteratorSize, false));

            mempcpy(_iterator, other._iterator, _iteratorSize);
        }

        IteratorPointer(ThisT rref other) noexcept
        {
            if (other isnot ptr this)
            {
                _allocator.DeallocateRaw(_iterator, _iteratorSize);

                _iteratorSize = other._iteratorSize;
                _iterator = static_cast<IteratorT ptr>(
                    _allocator.AllocateRaw(other._iteratorSize, false));

                memcpy(_iterator, other._iterator, other._iteratorSize);

                memset(_iterator, 0, other._iteratorSize);
                other._iterator = nullptr;
                other._iteratorSize = 0;
            }
        }

        ThisT lref operator = (const ThisT lref other) noexcept
        {
            if (other isnot ptr this)
            {
                _allocator.DeallocateRaw(_iterator, _iteratorSize);

                _iteratorSize = other._iteratorSize;
                _iterator = static_cast<IteratorT ptr>(
                    _allocator.AllocateRaw(other._iteratorSize, false));

                mempcpy(_iterator, other._iterator, _iteratorSize);
            }

            return ptr this;
        }

        ThisT lref operator = (ThisT rref other) noexcept
        {
            if (other isnot ptr this)
            {
                _allocator.DeallocateRaw(_iterator, _iteratorSize);

                _iterator = static_cast<IteratorT ptr>(
                    _allocator.AllocateRaw(other._iteratorSize, false));
                _iteratorSize = other._iteratorSize;
                memcpy(_iterator, other._iterator, other._iteratorSize);

                memset(_iterator, 0, other._iteratorSize);
                other._iterator = nullptr;
                other._iteratorSize = 0;
            }

            return ptr this;
        }

        /// @brief destructor destroys impl iterator using @param _allocator 
        dtor IteratorPointer()
        {
            _allocator.DeallocateRaw(_iterator, _iteratorSize);
        }

        // *******************************************************************

        virtual ValueTypeT lref Value() noexcept final override
        {
            return _iterator->Value();
        }

        virtual const ValueTypeT lref Value() const noexcept final override
        {
            return _iterator->Value();
        }

        virtual int Compare(const IteratorT lref rhs) const noexcept final override
        {
            return _iterator->Compare(rhs);
        }

        // *******************************************************************

        IteratorT lref operator -> () noexcept
        {
            return ptr _iterator;
        }

        const IteratorT lref operator -> () const noexcept
        {
            return ptr _iterator;
        }

        // *******************************************************************

    protected:
        /// @brief pointer to the implementation iterator
        IteratorT ptr _iterator;

        /// @brief alloctor to manage impl iterator reference
        AllocatorT _allocator;

        SizeT _iteratorSize;
    };

    /// @extends IteratorPointer
    template <typename TValueType>
    class ForwardIteratorPointer :
        public virtual IteratorPointer<TValueType>,
        public virtual ForwardIterator<TValueType>
    {
        using SizeT = sizet;
        using ThisT = ForwardIteratorPointer<TValueType>;
        using BaseT = IteratorPointer<TValueType>;
        using IteratorT = ForwardIterator<TValueType>;

        using BaseT::_iterator;

    public:

        /// @brief default constructor initializes impl iterator with null
        ForwardIteratorPointer() noexcept :
            BaseT() { }

        template <typename TIterator>
        ForwardIteratorPointer(const TIterator lref iterator) noexcept :
            ThisT(lref iterator, sizeof(TIterator)) { }

        ForwardIteratorPointer(const IteratorT ptr iterator, const SizeT size) noexcept :
            BaseT(iterator, size) { }

        ForwardIteratorPointer(const ThisT lref other) noexcept :
            BaseT(other) { }

        ForwardIteratorPointer(ThisT rref other) noexcept :
            BaseT(other) { }

        ThisT lref operator = (const ThisT lref other) noexcept
        {
            BaseT::operator = (other);
        }

        ThisT lref operator = (ThisT rref other) noexcept
        {
            BaseT::operator = (other);
        }

        // *******************************************************************

        virtual void MoveFwd() const noexcept override
        {
            dynamic_cast<IteratorT ptr>(_iterator)->MoveFwd();
        }

        // *******************************************************************

        IteratorT lref operator -> () noexcept
        {
            return ptr dynamic_cast<IteratorT ptr>(_iterator);
        }

        const IteratorT lref operator -> () const noexcept
        {
            return ptr dynamic_cast<IteratorT ptr>(_iterator);
        }

        // *******************************************************************

        operator BaseT () const noexcept
        {
            return BaseT(ptr this);
        }
    };

    /// @extends ForwardIteratorPointer
    template <typename TValueType>
    class BidirectionalIteratorPointer :
        public virtual ForwardIteratorPointer<TValueType>,
        public virtual BidirectionalIterator<TValueType>
    {
        using SizeT = sizet;
        using ThisT = BidirectionalIteratorPointer<TValueType>;
        using BaseT = ForwardIteratorPointer<TValueType>;
        using IteratorT = BidirectionalIterator<TValueType>;

        using BaseT::_iterator;

    public:

        /// @brief default constructor initializes impl iterator with null
        BidirectionalIteratorPointer() noexcept :
            BaseT() { }

        template <typename TIterator>
        BidirectionalIteratorPointer(const TIterator lref iterator) noexcept :
            ThisT(lref iterator, sizeof(TIterator)) { }

        BidirectionalIteratorPointer(const IteratorT ptr iterator, const SizeT size) noexcept :
            BaseT(iterator, size) { }

        BidirectionalIteratorPointer(const ThisT lref other) noexcept :
            BaseT(other) { }

        BidirectionalIteratorPointer(ThisT rref other) noexcept :
            BaseT(other) { }

        ThisT lref operator = (const ThisT lref other) noexcept
        {
            BaseT::operator = (other);
        }

        ThisT lref operator = (ThisT rref other) noexcept
        {
            BaseT::operator = (other);
        }

        // *******************************************************************

        virtual void MoveBwd() const noexcept override
        {
            dynamic_cast<IteratorT ptr>(_iterator)->MoveBwd();
        }

        // *******************************************************************

        IteratorT lref operator -> () noexcept
        {
            return ptr dynamic_cast<IteratorT ptr>(_iterator);
        }

        const IteratorT lref operator -> () const noexcept
        {
            return ptr dynamic_cast<IteratorT ptr>(_iterator);
        }

        // *******************************************************************

        operator BaseT () const noexcept
        {
            return BaseT(ptr this);
        }
    };

    /// @extends BidirectionalIteratorPointer
    template <typename TValueType>
    class RandomAccessIteratorPointer :
        public virtual BidirectionalIteratorPointer<TValueType>,
        public virtual RandomAccessIterator<TValueType>
    {
        using SizeT = sizet;
        using ThisT = RandomAccessIteratorPointer<TValueType>;
        using BaseT = BidirectionalIteratorPointer<TValueType>;
        using IteratorT = RandomAccessIterator<TValueType>;

        using BaseT::_iterator;

    public:

        /// @brief default constructor initializes impl iterator with null
        RandomAccessIteratorPointer() noexcept :
            BaseT() { }

        template <typename TIterator>
        RandomAccessIteratorPointer(const TIterator lref iterator) noexcept :
            ThisT(lref iterator, sizeof(TIterator)) { }

        RandomAccessIteratorPointer(const IteratorT ptr iterator, const SizeT size) noexcept :
            BaseT(iterator, size) { }

        RandomAccessIteratorPointer(const ThisT lref other) noexcept :
            BaseT(other) { }

        RandomAccessIteratorPointer(ThisT rref other) noexcept :
            BaseT(other) { }

        ThisT lref operator = (const ThisT lref other) noexcept
        {
            BaseT::operator = (other);
        }

        ThisT lref operator = (ThisT rref other) noexcept
        {
            BaseT::operator = (other);
        }

        // *******************************************************************

        virtual void MoveFwdBy(const SizeT steps) const noexcept override
        {
            dynamic_cast<IteratorT ptr>(_iterator)->MoveFwdBy(steps);
        }

        virtual void MoveBwdBy(const SizeT steps) const noexcept override
        {
            dynamic_cast<IteratorT ptr>(_iterator)->MoveBwdBy(steps);
        }

        // *******************************************************************

        IteratorT lref operator -> () noexcept
        {
            return ptr dynamic_cast<IteratorT ptr>(_iterator);
        }

        const IteratorT lref operator -> () const noexcept
        {
            return ptr dynamic_cast<IteratorT ptr>(_iterator);
        }

        // *******************************************************************

        operator BaseT () const noexcept
        {
            return BaseT(ptr this);
        }
    };
}