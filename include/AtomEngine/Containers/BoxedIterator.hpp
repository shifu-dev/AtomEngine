#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/Iterator.hpp"
#include "AtomEngine/Memory/BoxedObject.hpp"
#include "AtomEngine/Memory/LegacyAllocator.hpp"

namespace Atom
{
    /// Pointer to iterator to provide iterface ability to Iterable.
    ///
    /// @tparam TElement Type of value iterator points to.
    ///
    /// @note
    /// - This class acts like a unique ptr with functionality of iterators.
    template <typename TElement>
    class BoxedIterator : public virtual Iterator<TElement>,
        public BoxedObject<LegacyAllocator, 500>
    {
        using ThisT = BoxedIterator<TElement>;
        using BoxedObjectT = BoxedObject<LegacyAllocator, 500>;
        using ElementT = TElement;
        using IteratorT = Iterator<ElementT>;
        using AllocatorT = LegacyAllocator;

        /// ----------------------------------------------------------------------------

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

        mpublic template <typename TIterator>
            ThisT ref operator = (const TIterator ref iterator) noexcept
        {
            StaticAssertSubClass<IteratorT, TIterator>();
            BoxedObjectT::operator = (iterator);

            return ptr this;
        }

        mpublic template <typename TIterator>
            ThisT ref operator = (TIterator rref iterator) noexcept
        {
            StaticAssertSubClass<IteratorT, TIterator>();
            BoxedObjectT::operator = (move(iterator));

            return ptr this;
        }

        /// ----------------------------------------------------------------------------

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

        /// ----------------------------------------------------------------------------

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
}