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
        using ThisT = IteratorPointer<TValueType>;

    public:
        /// @brief type of impl iterator
        using IteratorT = Iterator<TValueType>;

        /// @todo inherit doc from base class
        using ValueTypeT = typename IteratorT::ValueTypeT;

        /// @brief allocator type used to manage iterator ptr
        using AllocatorT = Allocator;

    public:

        /// @brief construct iterator within IteratorPointer
        /// @tparam TIterator type of iterator
        /// @tparam ...TArgs type of arguments to construct iterator
        /// @param ...args arguments to construct iterator
        template <typename TIterator, typename... TArgs>
        static ThisT Create(TArgs rref... args) noexcept
        {
            ThisT itPtr;
            itPtr.Construct<TIterator>(forward<TArgs>(args)...);
            return itPtr;
        }

    protected:
        template <typename TIterator, typename... TArgs>
        void Construct(TArgs rref... args) noexcept
        {
            _allocator = AllocatorT();
            _iterator = _allocator.Construct<TIterator>(forward<TArgs>(args)...);
        }

    public:

        // *******************************************************************

        /// @brief default constructor initializes impl iterator with null
        IteratorPointer() : _allocator(), _iterator(nullptr) { }

        /// @brief destructor destroys impl iterator using @param _allocator 
        dtor IteratorPointer()
        {
            _allocator.Destruct(_iterator);
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
    };

    /// @extends IteratorPointer
    template <typename TValueType>
    class ForwardIteratorPointer :
        public virtual IteratorPointer<TValueType>,
        public virtual ForwardIterator<TValueType>
    {
        using ThisT = ForwardIteratorPointer<TValueType>;
        using BaseT = IteratorPointer<TValueType>;
        using IteratorT = ForwardIterator<TValueType>;

    public:
        using typename BaseT::AllocatorT;

    public:

        /// @brief construct iterator within IteratorPointer
        /// @tparam TIterator type of iterator
        /// @tparam ...TArgs type of arguments to construct iterator
        /// @param ...args arguments to construct iterator
        template <typename TIterator, typename... TArgs>
        static ThisT Create(TArgs rref... args) noexcept
        {
            ThisT itPtr;
            itPtr.Construct<TIterator>(forward<TArgs>(args)...);

            return itPtr;
        }

    protected:
        template <typename TIterator, typename... TArgs>
        void Construct(TArgs rref... args) noexcept
        {
            BaseT:: template Construct<TIterator>(forward<TArgs>(args)...);

            _iterator = dynamic_cast<IteratorT ptr>(BaseT::_iterator);
        }

    public:

        /// @brief default constructor initializes impl iterator with null
        ForwardIteratorPointer() : BaseT(), _iterator(nullptr) { }

        // *******************************************************************

        virtual void MoveFwd() const noexcept override
        {
            _iterator->MoveFwd();
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

        IteratorT ptr _iterator;
    };

    /// @extends ForwardIteratorPointer
    template <typename TValueType>
    class BidirectionalIteratorPointer :
        public virtual ForwardIteratorPointer<TValueType>,
        public virtual BidirectionalIterator<TValueType>
    {
        using ThisT = BidirectionalIteratorPointer<TValueType>;
        using BaseT = ForwardIteratorPointer<TValueType>;
        using IteratorT = BidirectionalIterator<TValueType>;

    public:

        /// @brief construct iterator within IteratorPointer
        /// @tparam TIterator type of iterator
        /// @tparam ...TArgs type of arguments to construct iterator
        /// @param ...args arguments to construct iterator
        template <typename TIterator, typename... TArgs>
        static ThisT Create(TArgs rref... args) noexcept
        {
            ThisT itPtr;
            itPtr.Construct<TIterator>(forward<TArgs>(args)...);

            return itPtr;
        }

    protected:
        template <typename TIterator, typename... TArgs>
        void Construct(TArgs rref... args) noexcept
        {
            BaseT:: template Construct<TIterator>(forward<TArgs>(args)...);

            _iterator = dynamic_cast<IteratorT ptr>(BaseT::_iterator);
        }

    public:

        /// @brief default constructor initializes impl iterator with null
        BidirectionalIteratorPointer() : BaseT(), _iterator(nullptr) { }

        // *******************************************************************

        virtual void MoveBwd() const noexcept override
        {
            _iterator->MoveBwd();
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

        IteratorT ptr _iterator;
    };

    /// @extends ForwardIteratorPointer
    template <typename TValueType>
    class RandomAccessIteratorPointer :
        public virtual BidirectionalIteratorPointer<TValueType>,
        public virtual RandomAccessIterator<TValueType>
    {
        using SizeT = sizet;
        using ThisT = RandomAccessIteratorPointer<TValueType>;
        using BaseT = BidirectionalIteratorPointer<TValueType>;
        using IteratorT = RandomAccessIterator<TValueType>;

    public:

        /// @brief construct iterator within IteratorPointer
        /// @tparam TIterator type of iterator
        /// @tparam ...TArgs type of arguments to construct iterator
        /// @param ...args arguments to construct iterator
        template <typename TIterator, typename... TArgs>
        static ThisT Create(TArgs rref... args) noexcept
        {
            ThisT itPtr;
            itPtr.Construct<TIterator>(forward<TArgs>(args)...);

            return itPtr;
        }

    protected:
        template <typename TIterator, typename... TArgs>
        void Construct(TArgs rref... args) noexcept
        {
            BaseT:: template Construct<TIterator>(forward<TArgs>(args)...);

            _iterator = dynamic_cast<IteratorT ptr>(BaseT::_iterator);
        }

    public:

        /// @brief default constructor initializes impl iterator with null
        RandomAccessIteratorPointer() : BaseT(), _iterator(nullptr) { }

        // *******************************************************************

        virtual void MoveFwdBy(const SizeT steps) const noexcept override
        {
            _iterator->MoveFwdBy(steps);
        }

        virtual void MoveBwdBy(const SizeT steps) const noexcept override
        {
            _iterator->MoveBwdBy(steps);
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

        IteratorT ptr _iterator;
    };
}