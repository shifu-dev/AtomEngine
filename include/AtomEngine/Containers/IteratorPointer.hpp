#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/Iterator.hpp"
#include "AtomEngine/Memory/ObjectPointer.hpp"
#include "AtomEngine/Memory/LegacyAllocator.hpp"

namespace Atom
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

        /// @brief default constructor initializes impl iterator with null
        mpublic IteratorPointer() noexcept : BaseT() { }

        mpublic IteratorPointer(const ThisT ref other) noexcept :
            BaseT(other) { }

        mpublic IteratorPointer(ThisT rref other) noexcept :
            BaseT(move(other)) { }

        mpublic ThisT ref operator = (const ThisT ref other) noexcept
        {
            BaseT::operator = (other);
            return ptr this;
        }

        mpublic ThisT ref operator = (ThisT rref other) noexcept
        {
            BaseT::operator = (move(other));
            return ptr this;
        }

        mpublic template <typename TIterator, EnableIf<IsSubClass<ThisT, TIterator> == false> = true>
            IteratorPointer(const TIterator ref iterator) noexcept
        {
            BaseT::SetObject(iterator);
        }

        mpublic template <typename TIterator, EnableIf<IsSubClass<ThisT, TIterator> == false> = true>
            IteratorPointer(TIterator rref iterator) noexcept
        {
            BaseT::SetObject(move(iterator));
        }

        // *******************************************************************

        mpublic IteratorT ref GetIterator() noexcept
        {
            return ptr BaseT::mObject;
        }

        mpublic const IteratorT ref GetIterator() const noexcept
        {
            return ptr BaseT::mObject;
        }

        // *******************************************************************

        mpublic virtual ElementT ref Value() noexcept final override
        {
            return GetIterator().Value();
        }

        mpublic virtual const ElementT ref Value() const noexcept final override
        {
            return GetIterator().Value();
        }

        mpublic virtual int Compare(const IteratorT ref rhs) const noexcept final override
        {
            return GetIterator().Compare(rhs);
        }

        // *******************************************************************

        /// @brief compares with other iterator pointer
        /// @param rhs other iterator pointer to compare with
        /// @return true if both impl iterators represent same value
        mpublic virtual bool operator ==(const ThisT ref rhs) const noexcept
        {
            return Compare(rhs) is 0;
        }

        /// @brief compares with other iterator pointer
        /// @param rhs other iterator pointer to compare with
        /// @return false if both iterators represent same value
        mpublic virtual bool operator !=(const ThisT ref rhs) const noexcept
        {
            return Compare(rhs) isnot 0;
        }

        // this overload is necessary to avoid comparing iterator with iterator pointer 
        mpublic virtual int Compare(const ThisT ref rhs) const noexcept
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

        /// @brief default constructor initializes impl iterator with null
        mpublic ForwardIteratorPointer() noexcept : BaseT() { }

        mpublic template <typename TIterator>
            ForwardIteratorPointer(const TIterator ref iterator) noexcept :
            BaseT(ref iterator, sizeof(TIterator)) { }

        mpublic ForwardIteratorPointer(const IteratorT ptr iterator, const sizet size) noexcept :
            BaseT(iterator, size) { }

        mpublic ForwardIteratorPointer(const ThisT ref other) noexcept :
            BaseT(other) { }

        mpublic ForwardIteratorPointer(ThisT rref other) noexcept :
            BaseT(other) { }

        // *******************************************************************

        mpublic IteratorT ref GetIterator() noexcept
        {
            return rcast<IteratorT ref>(BaseT::GetIterator());
        }

        mpublic const IteratorT ref GetIterator() const noexcept
        {
            return rcast<const IteratorT ref>(BaseT::GetIterator());
        }

        mpublic virtual void MoveFwd() const noexcept override
        {
            GetIterator().MoveFwd();
        }

        // *******************************************************************

        mpublic operator BaseT () const noexcept
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

        /// @brief default constructor initializes impl iterator with null
        mpublic BidirectionalIteratorPointer() noexcept : BaseT() { }

        mpublic template <typename TIterator>
            BidirectionalIteratorPointer(const TIterator ref iterator) noexcept :
            BaseT(ref iterator, sizeof(TIterator)) { }

        mpublic BidirectionalIteratorPointer(const IteratorT ptr iterator, const sizet size) noexcept :
            BaseT(iterator, size) { }

        mpublic BidirectionalIteratorPointer(const ThisT ref other) noexcept :
            BaseT(other) { }

        mpublic BidirectionalIteratorPointer(ThisT rref other) noexcept :
            BaseT(other) { }

        // *******************************************************************

        mpublic IteratorT ref GetIterator() noexcept
        {
            return rcast<IteratorT ref>(BaseT::GetIterator());
        }

        mpublic const IteratorT ref GetIterator() const noexcept
        {
            return rcast<const IteratorT ref>(BaseT::GetIterator());
        }

        mpublic virtual void MoveBwd() const noexcept override
        {
            GetIterator().MoveBwd();
        }

        // *******************************************************************

        mpublic operator BaseT () const noexcept
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

        /// @brief default constructor initializes impl iterator with null
        mpublic RandomAccessIteratorPointer() noexcept : BaseT() { }

        mpublic template <typename TIterator>
            RandomAccessIteratorPointer(const TIterator ref iterator) noexcept :
            BaseT(ref iterator, sizeof(TIterator)) { }

        mpublic RandomAccessIteratorPointer(const IteratorT ptr iterator, const sizet size) noexcept :
            BaseT(iterator, size) { }

        mpublic RandomAccessIteratorPointer(const ThisT ref other) noexcept :
            BaseT(other) { }

        mpublic RandomAccessIteratorPointer(ThisT rref other) noexcept :
            BaseT(other) { }

        // *******************************************************************

        mpublic IteratorT ref GetIterator() noexcept
        {
            return rcast<IteratorT ref>(BaseT::GetIterator());
        }

        mpublic const IteratorT ref GetIterator() const noexcept
        {
            return rcast<const IteratorT ref>(BaseT::GetIterator());
        }

        mpublic virtual void MoveFwdBy(const sizet steps) const noexcept override
        {
            GetIterator().MoveFwdBy(steps);
        }

        mpublic virtual void MoveBwdBy(const sizet steps) const noexcept override
        {
            GetIterator().MoveBwdBy(steps);
        }

        // *******************************************************************

        mpublic operator BaseT () const noexcept
        {
            return BaseT(ptr this);
        }
    };
}