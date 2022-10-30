#pragma once
#include "SSEngine/Core.hpp"
#include "SSEngine/Containers/Iterator.hpp"

namespace SSEngine
{
    /// @brief pointer to iterator to provide iterface ability to Iterable
    /// @note this class acts like a unique ptr with functionality of iterators
    /// @tparam TElement type of value iterator points to
    template <typename TElement>
    class IteratorPointer :
        public virtual Iterator<TElement>
    {
        using ThisT = IteratorPointer<TElement>;
        using ContainerDefinationT = ContainerDefination<TElement>;
        using SizeT = typename ContainerDefinationT::SizeT;
        using ElementT = typename ContainerDefinationT::ElementT;
        using IteratorT = typename ContainerDefinationT::IteratorT;
        using AllocatorT = typename ContainerDefinationT::AllocatorT;

    public:
        using ElementType = ElementT;
        using AllocatorType = AllocatorT;

    public:

        // *******************************************************************

        /// @brief default constructor initializes impl iterator with null
        IteratorPointer() noexcept :
            mAllocator(), mIterator(nullptr) { }

        template <typename TIterator>
        IteratorPointer(const TIterator lref iterator) noexcept :
            ThisT(lref iterator, sizeof(TIterator)) { }

        IteratorPointer(const IteratorT ptr iterator, const SizeT size) noexcept
        {
            mAllocator = AllocatorT();
            mIteratorSize = size;
            mIterator = scast<IteratorT ptr>(
                mAllocator.AllocateRaw(mIteratorSize, false));

            mempcpy(mIterator, iterator, size);
        }

        IteratorPointer(const ThisT lref other) noexcept
        {
            mAllocator = AllocatorT();
            mIteratorSize = other.mIteratorSize;
            mIterator = scast<IteratorT ptr>(
                mAllocator.AllocateRaw(mIteratorSize, false));

            mempcpy(mIterator, other.mIterator, mIteratorSize);
        }

        IteratorPointer(ThisT rref other) noexcept
        {
            if (other isnot ptr this)
            {
                mAllocator.DeallocateRaw(mIterator, mIteratorSize);

                mIteratorSize = other.mIteratorSize;
                mIterator = scast<IteratorT ptr>(
                    mAllocator.AllocateRaw(other.mIteratorSize, false));

                memcpy(mIterator, other.mIterator, other.mIteratorSize);

                memset(mIterator, 0, other.mIteratorSize);
                other.mIterator = nullptr;
                other.mIteratorSize = 0;
            }
        }

        ThisT lref operator = (const ThisT lref other) noexcept
        {
            if (other isnot ptr this)
            {
                mAllocator.DeallocateRaw(mIterator, mIteratorSize);

                mIteratorSize = other.mIteratorSize;
                mIterator = scast<IteratorT ptr>(
                    mAllocator.AllocateRaw(other.mIteratorSize, false));

                mempcpy(mIterator, other.mIterator, mIteratorSize);
            }

            return ptr this;
        }

        ThisT lref operator = (ThisT rref other) noexcept
        {
            if (other isnot ptr this)
            {
                mAllocator.DeallocateRaw(mIterator, mIteratorSize);

                mIterator = scast<IteratorT ptr>(
                    mAllocator.AllocateRaw(other.mIteratorSize, false));
                mIteratorSize = other.mIteratorSize;
                memcpy(mIterator, other.mIterator, other.mIteratorSize);

                memset(mIterator, 0, other.mIteratorSize);
                other.mIterator = nullptr;
                other.mIteratorSize = 0;
            }

            return ptr this;
        }

        /// @brief destructor destroys impl iterator using @param mAllocator 
        dtor IteratorPointer()
        {
            mAllocator.DeallocateRaw(mIterator, mIteratorSize);
        }

        // *******************************************************************

        virtual ElementT lref Value() noexcept final override
        {
            return mIterator->Value();
        }

        virtual const ElementT lref Value() const noexcept final override
        {
            return mIterator->Value();
        }

        virtual int Compare(const IteratorT lref rhs) const noexcept final override
        {
            return mIterator->Compare(rhs);
        }

        // *******************************************************************

        /// @brief compares with other iterator pointer
        /// @param rhs other iterator pointer to compare with
        /// @return true if both impl iterators represent same value
        virtual bool operator ==(const ThisT lref rhs) const noexcept
        {
            return Compare(rhs) iseq 0;
        }

        /// @brief compares with other iterator pointer
        /// @param rhs other iterator pointer to compare with
        /// @return false if both iterators represent same value
        /// 
        /// @note this operator is used by c++ range-based for loop
        /// to check the end of iteration
        virtual bool operator !=(const ThisT lref rhs) const noexcept
        {
            return Compare(rhs) isnot 0;
        }

        // this overload is necessary to avoid comparing iterator with iterator pointer 
        virtual int Compare(const ThisT lref rhs) const noexcept
        {
            return mIterator->Compare(ptr rhs.mIterator);
        }

        // *******************************************************************

        IteratorT lref operator -> () noexcept
        {
            return ptr mIterator;
        }

        const IteratorT lref operator -> () const noexcept
        {
            return ptr mIterator;
        }

        // *******************************************************************

    protected:
        /// @brief pointer to the implementation iterator
        IteratorT ptr mIterator;

        /// @brief alloctor to manage impl iterator reference
        AllocatorT mAllocator;

        SizeT mIteratorSize;
    };

    /// @extends IteratorPointer
    template <typename TElement>
    class ForwardIteratorPointer :
        public virtual IteratorPointer<TElement>,
        public virtual ForwardIterator<TElement>
    {
        using SizeT = sizet;
        using ThisT = ForwardIteratorPointer<TElement>;
        using BaseT = IteratorPointer<TElement>;
        using IteratorT = ForwardIterator<TElement>;

    protected:
        using BaseT::mIterator;

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
            dcast<IteratorT ptr>(mIterator)->MoveFwd();
        }

        // *******************************************************************

        IteratorT lref operator -> () noexcept
        {
            return ptr dcast<IteratorT ptr>(mIterator);
        }

        const IteratorT lref operator -> () const noexcept
        {
            return ptr dcast<IteratorT ptr>(mIterator);
        }

        // *******************************************************************

        operator BaseT () const noexcept
        {
            return BaseT(ptr this);
        }
    };

    /// @extends ForwardIteratorPointer
    template <typename TElement>
    class BidirectionalIteratorPointer :
        public virtual ForwardIteratorPointer<TElement>,
        public virtual BidirectionalIterator<TElement>
    {
        using SizeT = sizet;
        using ThisT = BidirectionalIteratorPointer<TElement>;
        using BaseT = ForwardIteratorPointer<TElement>;
        using IteratorT = BidirectionalIterator<TElement>;

    protected:
        using BaseT::mIterator;

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
            dcast<IteratorT ptr>(mIterator)->MoveBwd();
        }

        // *******************************************************************

        IteratorT lref operator -> () noexcept
        {
            return ptr dcast<IteratorT ptr>(mIterator);
        }

        const IteratorT lref operator -> () const noexcept
        {
            return ptr dcast<IteratorT ptr>(mIterator);
        }

        // *******************************************************************

        operator BaseT () const noexcept
        {
            return BaseT(ptr this);
        }
    };

    /// @extends BidirectionalIteratorPointer
    template <typename TElement>
    class RandomAccessIteratorPointer :
        public virtual BidirectionalIteratorPointer<TElement>,
        public virtual RandomAccessIterator<TElement>
    {
        using ThisT = RandomAccessIteratorPointer<TElement>;
        using BaseT = BidirectionalIteratorPointer<TElement>;
        using ContainerDefinationT = ContainerDefination<TElement>;
        using SizeT = typename ContainerDefinationT::SizeT;
        using ElementT = typename ContainerDefinationT::ElementT;
        using RandomAccessIteratorT = typename ContainerDefinationT::RandomAccessIteratorT;
        using IteratorType = RandomAccessIteratorT;

    protected:
        using BaseT::mIterator;

    public:

        /// @brief default constructor initializes impl iterator with null
        RandomAccessIteratorPointer() noexcept :
            BaseT() { }

        template <typename TIterator>
        RandomAccessIteratorPointer(const TIterator lref iterator) noexcept :
            ThisT(lref iterator, sizeof(TIterator)) { }

        RandomAccessIteratorPointer(const IteratorType ptr iterator, const SizeT size) noexcept :
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
            dcast<IteratorType ptr>(mIterator)->MoveFwdBy(steps);
        }

        virtual void MoveBwdBy(const SizeT steps) const noexcept override
        {
            dcast<IteratorType ptr>(mIterator)->MoveBwdBy(steps);
        }

        // *******************************************************************

        IteratorType lref operator -> () noexcept
        {
            return ptr dcast<IteratorType ptr>(mIterator);
        }

        const IteratorType lref operator -> () const noexcept
        {
            return ptr dcast<IteratorType ptr>(mIterator);
        }

        // *******************************************************************

        operator BaseT () const noexcept
        {
            return BaseT(ptr this);
        }
    };
}