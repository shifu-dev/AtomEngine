#pragma once
#include "SSEngine/Core.hpp"
#include "SSEngine/Containers/Iterator.hpp"
#include "SSEngine/Memory/ObjectPointer.hpp"
#include "SSEngine/Memory/LegacyAllocator.hpp"

namespace SSEngine
{
    /// @brief pointer to iterator to provide iterface ability to Iterable
    /// @note this class acts like a unique ptr with functionality of iterators
    /// @tparam TElement type of value iterator points to
    template <typename TElement>
    class IteratorPointer : public virtual Iterator<TElement>,
        protected Core::ObjectPointer<Iterator<TElement>, LegacyAllocator, 500>
    {
        using ThisT = IteratorPointer<TElement>;
        using BaseT = Core::ObjectPointer<Iterator<TElement>, LegacyAllocator, 500>;
        using ElementT = TElement;
        using IteratorT = Iterator<ElementT>;
        using AllocatorT = LegacyAllocator;

    public:

        /// @brief default constructor initializes impl iterator with null
        IteratorPointer() noexcept : BaseT() { }

        IteratorPointer(const ThisT lref other) noexcept :
            BaseT(other) { }

        IteratorPointer(ThisT rref other) noexcept :
            BaseT(move(other)) { }

        ThisT lref operator = (const ThisT lref other) noexcept
        {
            BaseT::operator = (other);
            return ptr this;
        }

        ThisT lref operator = (ThisT rref other) noexcept
        {
            BaseT::operator = (move(other));
            return ptr this;
        }

        template <typename TIterator, EnableIf<IsSubClass<ThisT, TIterator> == false> = true>
        IteratorPointer(const TIterator lref iterator) noexcept
        {
            BaseT::SetObject(iterator);
        }

        template <typename TIterator, EnableIf<IsSubClass<ThisT, TIterator> == false> = true>
        IteratorPointer(TIterator rref iterator) noexcept
        {
            BaseT::SetObject(move(iterator));
        }

        // *******************************************************************

        IteratorT lref GetIterator() noexcept
        {
            return ptr BaseT::mObject;
        }

        const IteratorT lref GetIterator() const noexcept
        {
            return ptr BaseT::mObject;
        }

        // *******************************************************************

        virtual ElementT lref Value() noexcept final override
        {
            return GetIterator().Value();
        }

        virtual const ElementT lref Value() const noexcept final override
        {
            return GetIterator().Value();
        }

        virtual int Compare(const IteratorT lref rhs) const noexcept final override
        {
            return GetIterator().Compare(rhs);
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
        virtual bool operator !=(const ThisT lref rhs) const noexcept
        {
            return Compare(rhs) isnot 0;
        }

        // this overload is necessary to avoid comparing iterator with iterator pointer 
        virtual int Compare(const ThisT lref rhs) const noexcept
        {
            return GetIterator().Compare(rhs.GetIterator());
        }
    };

    /// @extends IteratorPointer
    template <typename TElement>
    class ForwardIteratorPointer :
        public virtual IteratorPointer<TElement>,
        public virtual ForwardIterator<TElement>
    {
        using ThisT = ForwardIteratorPointer<TElement>;
        using BaseT = IteratorPointer<TElement>;
        using IteratorT = ForwardIterator<TElement>;

    public:

        /// @brief default constructor initializes impl iterator with null
        ForwardIteratorPointer() noexcept : BaseT() { }

        template <typename TIterator>
        ForwardIteratorPointer(const TIterator lref iterator) noexcept :
            BaseT(lref iterator, sizeof(TIterator)) { }

        ForwardIteratorPointer(const IteratorT ptr iterator, const sizet size) noexcept :
            BaseT(iterator, size) { }

        ForwardIteratorPointer(const ThisT lref other) noexcept :
            BaseT(other) { }

        ForwardIteratorPointer(ThisT rref other) noexcept :
            BaseT(other) { }

        // *******************************************************************

        IteratorT lref GetIterator() noexcept
        {
            return rcast<IteratorT lref>(BaseT::GetIterator());
        }

        const IteratorT lref GetIterator() const noexcept
        {
            return rcast<const IteratorT lref>(BaseT::GetIterator());
        }

        virtual void MoveFwd() const noexcept override
        {
            GetIterator().MoveFwd();
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
        using ThisT = BidirectionalIteratorPointer<TElement>;
        using BaseT = ForwardIteratorPointer<TElement>;
        using IteratorT = BidirectionalIterator<TElement>;

    public:

        /// @brief default constructor initializes impl iterator with null
        BidirectionalIteratorPointer() noexcept : BaseT() { }

        template <typename TIterator>
        BidirectionalIteratorPointer(const TIterator lref iterator) noexcept :
            BaseT(lref iterator, sizeof(TIterator)) { }

        BidirectionalIteratorPointer(const IteratorT ptr iterator, const sizet size) noexcept :
            BaseT(iterator, size) { }

        BidirectionalIteratorPointer(const ThisT lref other) noexcept :
            BaseT(other) { }

        BidirectionalIteratorPointer(ThisT rref other) noexcept :
            BaseT(other) { }

        // *******************************************************************

        IteratorT lref GetIterator() noexcept
        {
            return rcast<IteratorT lref>(BaseT::GetIterator());
        }

        const IteratorT lref GetIterator() const noexcept
        {
            return rcast<const IteratorT lref>(BaseT::GetIterator());
        }

        virtual void MoveBwd() const noexcept override
        {
            GetIterator().MoveBwd();
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
        using ElementT = TElement;
        using IteratorT = RandomAccessIterator<ElementT>;

    public:

        /// @brief default constructor initializes impl iterator with null
        RandomAccessIteratorPointer() noexcept : BaseT() { }

        template <typename TIterator>
        RandomAccessIteratorPointer(const TIterator lref iterator) noexcept :
            BaseT(lref iterator, sizeof(TIterator)) { }

        RandomAccessIteratorPointer(const IteratorT ptr iterator, const sizet size) noexcept :
            BaseT(iterator, size) { }

        RandomAccessIteratorPointer(const ThisT lref other) noexcept :
            BaseT(other) { }

        RandomAccessIteratorPointer(ThisT rref other) noexcept :
            BaseT(other) { }

        // *******************************************************************

        IteratorT lref GetIterator() noexcept
        {
            return rcast<IteratorT lref>(BaseT::GetIterator());
        }

        const IteratorT lref GetIterator() const noexcept
        {
            return rcast<const IteratorT lref>(BaseT::GetIterator());
        }

        virtual void MoveFwdBy(const sizet steps) const noexcept override
        {
            GetIterator().MoveFwdBy(steps);
        }

        virtual void MoveBwdBy(const sizet steps) const noexcept override
        {
            GetIterator().MoveBwdBy(steps);
        }

        // *******************************************************************

        operator BaseT () const noexcept
        {
            return BaseT(ptr this);
        }
    };
}