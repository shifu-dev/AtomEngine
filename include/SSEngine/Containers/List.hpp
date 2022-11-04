#pragma once
#include "SSEngine/Core.hpp"
#include "SSEngine/Containers/Collection.hpp"

namespace SSEngine
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
        using PredicateT = Predicate<const ElementT lref, sizet>;
        using CollectionT::Count;

    public:
        virtual const ElementT lref operator[](const sizet index) const noexcept abstract;
        virtual ElementT lref operator[](const sizet index) noexcept abstract;

        // **********************************************************************

        /// @brief access element by const ref at index
        /// @param index index of the element to access
        /// @return reference to element at index
        virtual const ElementT lref ElementAt(const sizet index) const abstract;

        /// @brief access element by ref at index
        /// @param index index of the element to access
        /// @return reference to element at index
        virtual ElementT lref ElementAt(const sizet index) abstract;

        /// @brief access element by const ref at index
        /// @return reference last element
        virtual const ElementT lref ElementFront() const
        {
            return ElementAt(0);
        }

        /// @brief access element by ref at index
        /// @return reference last element
        virtual ElementT lref ElementFront()
        {
            return ElementAt(0);
        }

        /// @brief access element by const ref at index
        /// @return reference first element
        virtual const ElementT lref ElementBack() const
        {
            return ElementAt(Count() - 1);
        }

        /// @brief access element by ref at index
        /// @return reference first element
        virtual ElementT lref ElementBack()
        {
            return ElementAt(Count() - 1);
        }

        // **********************************************************************

        /// @brief finds the first index of element
        /// @param element element to find
        /// @return index of element, NPOS if not found
        virtual sizet FirstIndexOf(const ElementT lref element, const EqualityComparerT lref comparer) const abstract;

        /// @brief finds the last index of element
        /// @param element element to find
        /// @return index of element, NPOS if not found
        virtual sizet LastIndexOf(const ElementT lref element, const EqualityComparerT lref comparer) const abstract;

        virtual sizet FirstIndexOf(const ElementT lref element) const
        {
            return FirstIndexOf(element, DefaultEqualityComparerT());
        }

        virtual sizet LastIndexOf(const ElementT lref element) const
        {
            return FirstIndexOf(element, DefaultEqualityComparerT());
        }

        // **********************************************************************

        virtual bool Contains(const ElementT lref element, const EqualityComparerT lref comparer) const noexcept override
        {
            return FirstIndexOf(element, comparer) isnot NPOS;
        }

        // **********************************************************************

        /// @brief insert element at given index
        /// @param index index to insert element at
        /// @param element element to insert
        virtual void InsertAt(const sizet index, const ElementT lref element) abstract;

        /// @brief inserts element at begining
        /// @param element element to insert
        /// @note calls InsertAt(0, element)
        virtual void InsertFront(const ElementT lref element)
        {
            InsertAt(0, element);
        }

        /// @brief inserts element at las
        /// @param element element to insert
        /// @note calls InsertAt(Count() - 1, element)
        virtual void InsertBack(const ElementT lref element)
        {
            InsertAt(Count() - 1, element);
        }

        virtual void Insert(const ElementT lref element) override
        {
            InsertBack(element);
        }

        // **********************************************************************

        virtual void InsertAt(const sizet index, const ForwardIteratorT lref it, const sizet count) abstract;

        virtual void InsertAt(const sizet index, const ForwardIteratorT lref begin, const ForwardIteratorT lref end)
        {
            sizet count = 0;
            for (auto lref it = begin; it isnot end; it++)
            {
                count++;
            }

            InsertAt(index, begin, count);
        }

        virtual void InsertAt(const sizet index, const IterableT lref elements, const sizet count)
        {
            InsertAt(index, elements.Begin(), count);
        }

        virtual void InsertAt(const sizet index, const IterableT lref elements)
        {
            InsertAt(index, elements.Begin(), elements.End());
        }

        virtual void InsertAt(const sizet index, const CollectionT lref elements)
        {
            InsertAt(index, scast<const IterableT lref>(elements), elements.Count());
        }

        template <ElementT... TElements>
        void InsertAt(const sizet index)
        {
            constexpr ElementT arr{ TElements... };
            InsertAt(ArrayIterator(arr), sizeof...(TElements));
        }

        virtual void InsertFront(const ForwardIteratorT lref it, const sizet count)
        {
            InsertAt(0, it, count);
        }

        virtual void InsertFront(const ForwardIteratorT lref begin, const ForwardIteratorT lref end)
        {
            InsertAt(0, begin, end);
        }

        virtual void InsertFront(const IterableT lref elements, const sizet count)
        {
            InsertAt(0, elements, count);
        }

        virtual void InsertFront(const IterableT lref elements)
        {
            InsertAt(0, elements);
        }

        virtual void InsertFront(const CollectionT lref elements)
        {
            InsertAt(0, elements);
        }

        template <ElementT... TElements>
        void InsertFront(const sizet index)
        {
            InsertAt<TElements...>(0);
        }

        virtual void InsertBack(const ForwardIteratorT lref it, const sizet count)
        {
            InsertAt(Count() - 1, it, count);
        }

        virtual void InsertBack(const ForwardIteratorT lref begin, const ForwardIteratorT lref end)
        {
            InsertAt(Count() - 1, begin, end);
        }

        virtual void InsertBack(const IterableT lref elements, const sizet count)
        {
            InsertAt(Count() - 1, elements, count);
        }

        virtual void InsertBack(const IterableT lref elements)
        {
            InsertAt(Count() - 1, elements);
        }

        virtual void InsertBack(const CollectionT lref elements)
        {
            InsertAt(Count() - 1, elements);
        }

        template <ElementT... TElements>
        void InsertBack(const sizet index)
        {
            InsertAt<TElements...>(Count() - 1);
        }

        // **********************************************************************

        /// @brief remove element at index
        /// @param index index of element to remove
        virtual void RemoveAt(const sizet index) abstract;

        /// @brief remove element from begining
        /// @note calls RemoveAt(0)
        virtual void RemoveFront()
        {
            RemoveAt(0);
        }

        /// @brief remove element from begining
        /// @note calls RemoveAt(Count() - 1)
        virtual void RemoveBack()
        {
            RemoveAt(Count() - 1);
        }

        virtual void RemoveFront(const ElementT lref element)
        {
            if (sizet index = FirstIndexOf(element) isnot NPOS)
            {
                RemoveAt(index);
            }
        }

        virtual void RemoveBack(const ElementT lref element)
        {
            if (sizet index = LastIndexOf(element) isnot NPOS)
            {
                RemoveAt(index);
            }
        }

        virtual void Remove(const ElementT lref element) override
        {
            RemoveFront(element);
        }

        // **********************************************************************

        virtual void RemoveFrom(const sizet indexFrom, const sizet indexTo) abstract;

        virtual void RemoveFrom(const sizet indexFrom)
        {
            RemoveFrom(indexFrom, Count() - 1);
        }

        // **********************************************************************

        virtual void RemoveIfCallable(const PredicateT lref pred) noexcept abstract;

        template <typename TFunctor>
        void RemoveIf(const TFunctor lref func) noexcept
        {
            RemoveIfCallable(PredicateT::Create(func));
        }
    };

    /// @brief list like structure that can manage memory dynamically
    /// @tparam TElement type of element to store
    template <typename TElement>
    class DynamicList : public virtual List<TElement>, public virtual DynamicCollection<TElement> {};
}