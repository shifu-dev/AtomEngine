#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/Iterator.hpp"
#include "AtomEngine/Memory/BoxedObject.hpp"
#include "AtomEngine/Memory/LegacyAllocator.hpp"

namespace Atom
{
    /// @brief pointer to iterator to provide iterface ability to Iterable
    /// @note this class acts like a unique ptr with functionality of iterators
    /// @tparam TElement type of value iterator points to
    template <typename TElement>
    class BoxedIterator : public virtual Iterator<TElement>,
        public BoxedObject<LegacyAllocator, 500>
    {
        using ThisT = BoxedIterator<TElement>;
        using BoxedObjectT = BoxedObject<LegacyAllocator, 500>;
        using ElementT = TElement;
        using IteratorT = Iterator<ElementT>;
        using AllocatorT = LegacyAllocator;

        ////////////////////////////////////////////////////////////////////////////////

        mpublic BoxedIterator() : BoxedObjectT(null) { }

        mpublic BoxedIterator(const ThisT ref other) noexcept :
            BoxedObjectT(other) { }

        mpublic BoxedIterator(ThisT rref other) noexcept :
            BoxedObjectT(move(other)) { }

        mpublic ThisT ref operator = (const ThisT ref other) noexcept
        {
            BoxedObjectT::operator = (other);
            return ptr this;
        }

        mpublic ThisT ref operator = (ThisT rref other) noexcept
        {
            BoxedObjectT::operator = (move(other));
            return ptr this;
        }

        mpublic template <typename TIterator>
            BoxedIterator(const TIterator ref iterator) noexcept :
            BoxedObjectT(iterator)
        {
            StaticAssertSubClass<IteratorT, TIterator>();
        }

        mpublic template <typename TIterator>
            BoxedIterator(TIterator rref iterator) noexcept :
            BoxedObjectT(move(iterator))
        {
            StaticAssertSubClass<IteratorT, TIterator>();
        }

        ////////////////////////////////////////////////////////////////////////////////

        mpublic IteratorT ref GetIterator() noexcept
        {
            return BoxedObjectT::GetObject<IteratorT>();
        }

        mpublic const IteratorT ref GetIterator() const noexcept
        {
            return BoxedObjectT::GetObject<IteratorT>();
        }

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

        ////////////////////////////////////////////////////////////////////////////////

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

    template <typename TElement>
    class BoxedForwardIterator :
        public virtual BoxedIterator<TElement>,
        public virtual ForwardIterator<TElement>
    {
        using ThisT = BoxedForwardIterator<TElement>;
        using BaseT = BoxedIterator<TElement>;
        using IteratorT = ForwardIterator<TElement>;

        ////////////////////////////////////////////////////////////////////////////////

        mpublic BoxedForwardIterator() : BaseT(null) { }

        mpublic BoxedForwardIterator(const ThisT ref other) noexcept :
            BaseT(other) { }

        mpublic BoxedForwardIterator(ThisT rref other) noexcept :
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

        mpublic template <typename TIterator>
            BoxedForwardIterator(const TIterator ref iterator) noexcept :
            BaseT(iterator)
        {
            StaticAssertSubClass<IteratorT, TIterator>();
        }

        mpublic template <typename TIterator>
            BoxedForwardIterator(TIterator rref iterator) noexcept :
            BaseT(move(iterator))
        {
            StaticAssertSubClass<IteratorT, TIterator>();
        }

        ////////////////////////////////////////////////////////////////////////////////

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

        ////////////////////////////////////////////////////////////////////////////////

        mpublic operator BaseT () const noexcept
        {
            return BaseT(ptr this);
        }
    };

    template <typename TElement>
    class BoxedBidirectionalIterator :
        public virtual BoxedForwardIterator<TElement>,
        public virtual BidirectionalIterator<TElement>
    {
        using ThisT = BoxedBidirectionalIterator<TElement>;
        using BaseT = BoxedForwardIterator<TElement>;
        using IteratorT = BidirectionalIterator<TElement>;

        ////////////////////////////////////////////////////////////////////////////////

        mpublic BoxedBidirectionalIterator() : BaseT(null) { }

        mpublic BoxedBidirectionalIterator(const ThisT ref other) noexcept :
            BaseT(other) { }

        mpublic BoxedBidirectionalIterator(ThisT rref other) noexcept :
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

        mpublic template <typename TIterator>
            BoxedBidirectionalIterator(const TIterator ref iterator) noexcept :
            BaseT(iterator)
        {
            StaticAssertSubClass<IteratorT, TIterator>();
        }

        mpublic template <typename TIterator>
            BoxedBidirectionalIterator(TIterator rref iterator) noexcept :
            BaseT(move(iterator))
        {
            StaticAssertSubClass<IteratorT, TIterator>();
        }

        ////////////////////////////////////////////////////////////////////////////////

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

        ////////////////////////////////////////////////////////////////////////////////

        mpublic operator BaseT () const noexcept
        {
            return BaseT(ptr this);
        }
    };

    template <typename TElement>
    class BoxedRandomAccessIterator :
        public virtual BoxedBidirectionalIterator<TElement>,
        public virtual RandomAccessIterator<TElement>
    {
        using ThisT = BoxedRandomAccessIterator<TElement>;
        using BaseT = BoxedBidirectionalIterator<TElement>;
        using IteratorT = RandomAccessIterator<TElement>;

        ////////////////////////////////////////////////////////////////////////////////

        mpublic BoxedRandomAccessIterator() : BaseT(null) { }

        mpublic BoxedRandomAccessIterator(const ThisT ref other) noexcept :
            BaseT(other) { }

        mpublic BoxedRandomAccessIterator(ThisT rref other) noexcept :
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

        mpublic template <typename TIterator>
            BoxedRandomAccessIterator(const TIterator ref iterator) noexcept :
            BaseT(iterator)
        {
            StaticAssertSubClass<IteratorT, TIterator>();
        }

        mpublic template <typename TIterator>
            BoxedRandomAccessIterator(TIterator rref iterator) noexcept :
            BaseT(move(iterator))
        {
            StaticAssertSubClass<IteratorT, TIterator>();
        }

        ////////////////////////////////////////////////////////////////////////////////

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

        ////////////////////////////////////////////////////////////////////////////////

        mpublic operator BaseT () const noexcept
        {
            return BaseT(ptr this);
        }
    };
}