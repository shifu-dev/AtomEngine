#pragma once
#include "SSEngine/Core.hpp"
#include "SSEngine/Collections/Collection.hpp"

namespace SSEngine
{
    /// @brief a list like structure manage elements,
    /// elements can be acessed using indexes
    /// @tparam TElement type of element to store
    template <typename TElement>
    class List : public virtual Collection<TElement>
    {
        using CollectionT = Collection<TElement>;
        using CollectionT::Count;

    public:
        using SizeType = typename CollectionT::SizeType;
        using ElementType = typename CollectionT::ElementType;
        using ComparerT = typename CollectionT::ComparerT;
        using EqualityComparerT = typename CollectionT::EqualityComparerT;
        using DefaultEqualityComparerT = typename CollectionT::DefaultEqualityComparerT;
        using IterableT = Iterable<ElementType>;
        using IteratorT = Iterator<ElementType>;
        using ForwardIteratorT = ForwardIterator<ElementType>;
        using PredicateT = Predicate<const ElementType lref, SizeType>;
        using CollectionT::NPOS;

    public:
        virtual const ElementType lref operator[](const SizeType index) const noexcept abstract;
        virtual ElementType lref operator[](const SizeType index) noexcept abstract;

        // **********************************************************************

        /// @brief access element by const ref at index
        /// @param index index of the element to access
        /// @return reference to element at index
        virtual const ElementType lref ElementAt(const SizeType index) const abstract;

        /// @brief access element by ref at index
        /// @param index index of the element to access
        /// @return reference to element at index
        virtual ElementType lref ElementAt(const SizeType index) abstract;

        /// @brief access element by const ref at index
        /// @return reference last element
        virtual const ElementType lref ElementFront() const
        {
            return ElementAt(0);
        }

        /// @brief access element by ref at index
        /// @return reference last element
        virtual ElementType lref ElementFront()
        {
            return ElementAt(0);
        }

        /// @brief access element by const ref at index
        /// @return reference first element
        virtual const ElementType lref ElementBack() const
        {
            return ElementAt(Count() - 1);
        }

        /// @brief access element by ref at index
        /// @return reference first element
        virtual ElementType lref ElementBack()
        {
            return ElementAt(Count() - 1);
        }

        // **********************************************************************

        /// @brief finds the first index of element
        /// @param element element to find
        /// @return index of element, NPOS if not found
        virtual SizeType FirstIndexOf(const ElementType lref element, const EqualityComparerT lref comparer) const abstract;

        /// @brief finds the last index of element
        /// @param element element to find
        /// @return index of element, NPOS if not found
        virtual SizeType LastIndexOf(const ElementType lref element, const EqualityComparerT lref comparer) const abstract;

        virtual SizeType FirstIndexOf(const ElementType lref element) const
        {
            return FirstIndexOf(element, DefaultEqualityComparerT());
        }

        virtual SizeType LastIndexOf(const ElementType lref element) const
        {
            return FirstIndexOf(element, DefaultEqualityComparerT());
        }

        // **********************************************************************

        virtual bool Contains(const ElementType lref element, const EqualityComparerT lref comparer) const noexcept override
        {
            return FirstIndexOf(element, comparer) isnot NPOS;
        }

        // **********************************************************************

        /// @brief insert element at given index
        /// @param index index to insert element at
        /// @param element element to insert
        virtual void InsertAt(const SizeType index, const ElementType lref element) abstract;

        /// @brief inserts element at begining
        /// @param element element to insert
        /// @note calls InsertAt(0, element)
        virtual void InsertFront(const ElementType lref element)
        {
            InsertAt(0, element);
        }

        /// @brief inserts element at las
        /// @param element element to insert
        /// @note calls InsertAt(Count() - 1, element)
        virtual void InsertBack(const ElementType lref element)
        {
            InsertAt(Count() - 1, element);
        }

        virtual void Insert(const ElementType lref element) override
        {
            InsertBack(element);
        }

        // **********************************************************************

        virtual void InsertAt(const SizeType index, const ForwardIteratorT lref it, const SizeType count) abstract;

        virtual void InsertAt(const SizeType index, const ForwardIteratorT lref begin, const ForwardIteratorT lref end)
        {
            SizeType count = 0;
            for (auto lref it = begin; it isnot end; it++)
            {
                count++;
            }

            InsertAt(index, begin, count);
        }

        virtual void InsertAt(const SizeType index, const IterableT lref elements, const SizeType count)
        {
            InsertAt(index, elements.Begin(), count);
        }

        virtual void InsertAt(const SizeType index, const IterableT lref elements)
        {
            InsertAt(index, elements.Begin(), elements.End());
        }

        virtual void InsertAt(const SizeType index, const CollectionT lref elements)
        {
            InsertAt(index, static_cast<const IterableT lref>(elements), elements.Count());
        }

        template <ElementType... TElements>
        void InsertAt(const SizeType index)
        {
            constexpr ElementType arr{ TElements... };
            InsertAt(ArrayIterator(arr), sizeof...(TElements));
        }

        virtual void InsertFront(const ForwardIteratorT lref it, const SizeType count)
        {
            InsertAt(0, it, count);
        }

        virtual void InsertFront(const ForwardIteratorT lref begin, const ForwardIteratorT lref end)
        {
            InsertAt(0, begin, end);
        }

        virtual void InsertFront(const IterableT lref elements, const SizeType count)
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

        template <ElementType... TElements>
        void InsertFront(const SizeType index)
        {
            InsertAt<TElements...>(0);
        }

        virtual void InsertBack(const ForwardIteratorT lref it, const SizeType count)
        {
            InsertAt(Count() - 1, it, count);
        }

        virtual void InsertBack(const ForwardIteratorT lref begin, const ForwardIteratorT lref end)
        {
            InsertAt(Count() - 1, begin, end);
        }

        virtual void InsertBack(const IterableT lref elements, const SizeType count)
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

        template <ElementType... TElements>
        void InsertBack(const SizeType index)
        {
            InsertAt<TElements...>(Count() - 1);
        }

        // **********************************************************************

        /// @brief remove element at index
        /// @param index index of element to remove
        virtual void RemoveAt(const SizeType index) abstract;

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

        virtual void RemoveFront(const ElementType lref element)
        {
            if (SizeType index = FirstIndexOf(element) isnot NPOS)
            {
                RemoveAt(index);
            }
        }

        virtual void RemoveBack(const ElementType lref element)
        {
            if (SizeType index = LastIndexOf(element) isnot NPOS)
            {
                RemoveAt(index);
            }
        }

        virtual void Remove(const ElementType lref element) override
        {
            RemoveFront(element);
        }

        // **********************************************************************

        virtual void RemoveFrom(const SizeType indexFrom, const SizeType indexTo) abstract;

        virtual void RemoveFrom(const SizeType indexFrom)
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