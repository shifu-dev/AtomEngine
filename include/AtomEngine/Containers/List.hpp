#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/Collection.hpp"

namespace Atom
{
    /// @brief a list like structure manage elements,
    /// elements can be acessed using indexes
    /// @tparam TElement type of element to store
    template <typename TElement>
    class List : public virtual Collection<TElement>
    {
        using ThisT = List<TElement>;
        using ElementT = TElement;
        using IterableT = Iterable<ElementT>;
        using CollectionT = Collection<ElementT>;
        using ComparerT = Comparer<ElementT>;
        using EqualityComparerT = EqualityComparer<ElementT>;
        using DefaultEqualityComparerT = DefaultEqualityComparer<ElementT>;
        using ForwardIteratorT = ForwardIterator<ElementT>;
        using PredicateT = Predicate<const ElementT ref, sizet>;
        using CollectionT::Count;

        mpublic virtual const ElementT ref operator[](const sizet index) const noexcept abstract;
        mpublic virtual ElementT ref operator[](const sizet index) noexcept abstract;

        // **********************************************************************

        /// @brief access element by const ref at index
        /// @param index index of the element to access
        /// @return reference to element at index
        mpublic virtual const ElementT ref ElementAt(const sizet index) const abstract;

        /// @brief access element by ref at index
        /// @param index index of the element to access
        /// @return reference to element at index
        mpublic virtual ElementT ref ElementAt(const sizet index) abstract;

        /// @brief access element by const ref at index
        /// @return reference last element
        mpublic virtual const ElementT ref ElementFront() const
        {
            return ElementAt(0);
        }

        /// @brief access element by ref at index
        /// @return reference last element
        mpublic virtual ElementT ref ElementFront()
        {
            return ElementAt(0);
        }

        /// @brief access element by const ref at index
        /// @return reference first element
        mpublic virtual const ElementT ref ElementBack() const
        {
            return ElementAt(Count() - 1);
        }

        /// @brief access element by ref at index
        /// @return reference first element
        mpublic virtual ElementT ref ElementBack()
        {
            return ElementAt(Count() - 1);
        }

        // **********************************************************************

        /// @brief finds the first index of element
        /// @param element element to find
        /// @return index of element, NPOS if not found
        mpublic virtual sizet FirstIndexOf(const ElementT ref element, const EqualityComparerT ref comparer) const abstract;

        /// @brief finds the last index of element
        /// @param element element to find
        /// @return index of element, NPOS if not found
        mpublic virtual sizet LastIndexOf(const ElementT ref element, const EqualityComparerT ref comparer) const abstract;

        mpublic virtual sizet FirstIndexOf(const ElementT ref element) const
        {
            return FirstIndexOf(element, DefaultEqualityComparerT());
        }

        mpublic virtual sizet LastIndexOf(const ElementT ref element) const
        {
            return FirstIndexOf(element, DefaultEqualityComparerT());
        }

        // **********************************************************************

        mpublic virtual bool Contains(const ElementT ref element, const EqualityComparerT ref comparer) const noexcept override
        {
            return FirstIndexOf(element, comparer) isnot NPOS;
        }

        // **********************************************************************

        /// @brief insert element at given index
        /// @param index index to insert element at
        /// @param element element to insert
        mpublic virtual void InsertAt(const sizet index, const ElementT ref element) abstract;

        /// @brief inserts element at begining
        /// @param element element to insert
        /// @note calls InsertAt(0, element)
        mpublic virtual void InsertFront(const ElementT ref element)
        {
            InsertAt(0, element);
        }

        /// @brief inserts element at las
        /// @param element element to insert
        /// @note calls InsertAt(Count() - 1, element)
        mpublic virtual void InsertBack(const ElementT ref element)
        {
            InsertAt(Count() - 1, element);
        }

        mpublic virtual void Insert(const ElementT ref element) override
        {
            InsertBack(element);
        }

        // **********************************************************************

        mpublic virtual void InsertAt(const sizet index, const ForwardIteratorT ref it, const sizet count) abstract;

        mpublic virtual void InsertAt(const sizet index, const ForwardIteratorT ref begin, const ForwardIteratorT ref end)
        {
            sizet count = 0;
            for (auto ref it = begin; it isnot end; it++)
            {
                count++;
            }

            InsertAt(index, begin, count);
        }

        mpublic virtual void InsertAt(const sizet index, const IterableT ref elements, const sizet count)
        {
            InsertAt(index, elements.Begin(), count);
        }

        mpublic virtual void InsertAt(const sizet index, const IterableT ref elements)
        {
            InsertAt(index, elements.Begin(), elements.End());
        }

        mpublic virtual void InsertAt(const sizet index, const CollectionT ref elements)
        {
            InsertAt(index, scast<const IterableT ref>(elements), elements.Count());
        }

        mpublic template <ElementT... TElements>
            void InsertAt(const sizet index)
        {
            constexpr ElementT arr{ TElements... };
            InsertAt(ArrayIterator(arr), sizeof...(TElements));
        }

        mpublic virtual void InsertFront(const ForwardIteratorT ref it, const sizet count)
        {
            InsertAt(0, it, count);
        }

        mpublic virtual void InsertFront(const ForwardIteratorT ref begin, const ForwardIteratorT ref end)
        {
            InsertAt(0, begin, end);
        }

        mpublic virtual void InsertFront(const IterableT ref elements, const sizet count)
        {
            InsertAt(0, elements, count);
        }

        mpublic virtual void InsertFront(const IterableT ref elements)
        {
            InsertAt(0, elements);
        }

        mpublic virtual void InsertFront(const CollectionT ref elements)
        {
            InsertAt(0, elements);
        }

        mpublic template <ElementT... TElements>
            void InsertFront(const sizet index)
        {
            InsertAt<TElements...>(0);
        }

        mpublic virtual void InsertBack(const ForwardIteratorT ref it, const sizet count)
        {
            InsertAt(Count() - 1, it, count);
        }

        mpublic virtual void InsertBack(const ForwardIteratorT ref begin, const ForwardIteratorT ref end)
        {
            InsertAt(Count() - 1, begin, end);
        }

        mpublic virtual void InsertBack(const IterableT ref elements, const sizet count)
        {
            InsertAt(Count() - 1, elements, count);
        }

        mpublic virtual void InsertBack(const IterableT ref elements)
        {
            InsertAt(Count() - 1, elements);
        }

        mpublic virtual void InsertBack(const CollectionT ref elements)
        {
            InsertAt(Count() - 1, elements);
        }

        mpublic template <ElementT... TElements>
            void InsertBack(const sizet index)
        {
            InsertAt<TElements...>(Count() - 1);
        }

        // **********************************************************************

        /// @brief remove element at index
        /// @param index index of element to remove
        mpublic virtual void RemoveAt(const sizet index) abstract;

        /// @brief remove element from begining
        /// @note calls RemoveAt(0)
        mpublic virtual void RemoveFront()
        {
            RemoveAt(0);
        }

        /// @brief remove element from begining
        /// @note calls RemoveAt(Count() - 1)
        mpublic virtual void RemoveBack()
        {
            RemoveAt(Count() - 1);
        }

        mpublic virtual void RemoveFront(const ElementT ref element)
        {
            if (sizet index = FirstIndexOf(element) isnot NPOS)
            {
                RemoveAt(index);
            }
        }

        mpublic virtual void RemoveBack(const ElementT ref element)
        {
            if (sizet index = LastIndexOf(element) isnot NPOS)
            {
                RemoveAt(index);
            }
        }

        mpublic virtual void Remove(const ElementT ref element) override
        {
            RemoveFront(element);
        }

        // **********************************************************************

        mpublic virtual void RemoveFrom(const sizet indexFrom, const sizet indexTo) abstract;

        mpublic virtual void RemoveFrom(const sizet indexFrom)
        {
            RemoveFrom(indexFrom, Count() - 1);
        }

        // **********************************************************************

        mpublic virtual void RemoveIfCallable(const PredicateT ref pred) noexcept abstract;

        mpublic template <typename TFunctor>
            void RemoveIf(const TFunctor ref func) noexcept
        {
            RemoveIfCallable(PredicateT::Create(func));
        }
    };

    /// @brief list like structure that can manage memory dynamically
    /// @tparam TElement type of element to store
    template <typename TElement>
    class DynamicList : public virtual List<TElement>, public virtual DynamicCollection<TElement> {};
}