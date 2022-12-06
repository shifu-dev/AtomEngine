#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/IIterator.hpp"
#include "AtomEngine/Memory/BoxedObject.hpp"
#include "AtomEngine/Memory/DefaultAllocator.hpp"

namespace Atom
{
    /// Pointer to iterator to provide iterface ability to IIterable.
    ///
    /// @tparam TElement Type of value iterator points to.
    ///
    /// @note
    /// - This class acts like a unique ptr with functionality of iterators.
    template <typename TElement>
    class BoxedIterator : public BoxedObject<DefaultAllocator, 500>,
        public virtual IIterator<TElement>
    {
        using ThisT = BoxedIterator<TElement>;
        using BaseT = BoxedObject<DefaultAllocator, 500>;
        using ElementT = TElement;
        using IIteratorT = IIterator<ElementT>;

        /// ----------------------------------------------------------------------------

        mpublic BoxedIterator() : BaseT(null) { }

        mpublic BoxedIterator(const ThisT ref other) noexcept :
            BaseT(other) { }

        mpublic BoxedIterator(ThisT rref other) noexcept :
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
            BoxedIterator(const TIterator ref iterator) noexcept :
            BaseT(iterator)
        {
            StaticAssertSubClass<IIteratorT, TIterator>();
        }

        mpublic template <typename TIterator>
            BoxedIterator(TIterator rref iterator) noexcept :
            BaseT(move(iterator))
        {
            StaticAssertSubClass<IIteratorT, TIterator>();
        }

        mpublic template <typename TIterator>
            ThisT ref operator = (const TIterator ref iterator) noexcept
        {
            StaticAssertSubClass<IIteratorT, TIterator>();
            BaseT::operator = (iterator);

            return ptr this;
        }

        mpublic template <typename TIterator>
            ThisT ref operator = (TIterator rref iterator) noexcept
        {
            StaticAssertSubClass<IIteratorT, TIterator>();
            BaseT::operator = (move(iterator));

            return ptr this;
        }

        /// ----------------------------------------------------------------------------

        mpublic IIteratorT ref GetIterator() noexcept
        {
            return BaseT::GetObject<IIteratorT>();
        }

        mpublic const IIteratorT ref GetIterator() const noexcept
        {
            return BaseT::GetObject<IIteratorT>();
        }

        mpublic virtual ElementT ref Value() noexcept final
        {
            return GetIterator().Value();
        }

        mpublic virtual const ElementT ref Value() const noexcept final
        {
            return GetIterator().Value();
        }

        mpublic virtual int Compare(const IIteratorT ref rhs) const noexcept final
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