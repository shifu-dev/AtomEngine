#pragma once
#include "SSEngine/Core.hpp"
#include "SSEngine/Collections/Collection.hpp"

namespace SSEngine
{
    /// @brief a list like structure manage elements,
    /// elements can be acessed using indexes
    /// @tparam TValueType type of element to store
    template <typename TValueType>
    class List : public virtual Collection<TValueType>
    {
        using ThisT = List<TValueType>;
        using CollectionT = Collection<TValueType>;

    public:
        using SizeT = typename CollectionT::SizeT;
        using ValueTypeT = typename CollectionT::ValueTypeT;
        using ComparerT = typename CollectionT::ComparerT;
        using EqualityComparerT = typename CollectionT::EqualityComparerT;
        using DefaultEqualityComparerT = typename CollectionT::DefaultEqualityComparerT;
        using PredicateT = int;
        using CollectionT::NPOS;

    public:
        virtual const ValueTypeT lref operator[](const SizeT index) const noexcept abstract;
        virtual ValueTypeT lref operator[](const SizeT index) noexcept abstract;

        // **********************************************************************

        /// @brief access element by const ref at index
        /// @param index index of the element to access
        /// @return reference to element at index
        virtual const ValueTypeT lref ElementAt(const SizeT index) const abstract;

        /// @brief access element by ref at index
        /// @param index index of the element to access
        /// @return reference to element at index
        virtual ValueTypeT lref ElementAt(const SizeT index) abstract;

        /// @brief access element by const ref at index
        /// @return reference last element
        virtual const ValueTypeT lref ElementFront() const
        {
            return ElementAt(0);
        }

        /// @brief access element by ref at index
        /// @return reference last element
        virtual ValueTypeT lref ElementFront()
        {
            return ElementAt(0);
        }

        /// @brief access element by const ref at index
        /// @return reference first element
        virtual const ValueTypeT lref ElementBack() const
        {
            return ElementAt(ThisT::Count() - 1);
        }

        /// @brief access element by ref at index
        /// @return reference first element
        virtual ValueTypeT lref ElementBack()
        {
            return ElementAt(ThisT::Count() - 1);
        }

        // **********************************************************************

        /// @brief finds the first index of element
        /// @param element element to find
        /// @return index of element, NPOS if not found
        virtual SizeT FirstIndexOf(const ValueTypeT lref element, const EqualityComparerT lref comparer) const abstract;

        /// @brief finds the last index of element
        /// @param element element to find
        /// @return index of element, NPOS if not found
        virtual SizeT LastIndexOf(const ValueTypeT lref element, const EqualityComparerT lref comparer) const abstract;

        virtual SizeT FirstIndexOf(const ValueTypeT lref element) const
        {
            return FirstIndexOf(element, DefaultEqualityComparerT());
        }

        virtual SizeT LastIndexOf(const ValueTypeT lref element) const
        {
            return FirstIndexOf(element, DefaultEqualityComparerT());
        }

        // **********************************************************************

        virtual bool Contains(const ValueTypeT lref element, const EqualityComparerT lref comparer) const noexcept override
        {
            return FirstIndexOf(element, comparer) isnot NPOS;
        }

        // **********************************************************************

        /// @brief insert element at given index
        /// @param index index to insert element at
        /// @param element element to insert
        virtual void InsertAt(const SizeT index, const ValueTypeT lref element) abstract;

        /// @brief inserts element at begining
        /// @param element element to insert
        /// @note calls InsertAt(0, element)
        virtual void InsertFront(const ValueTypeT lref element)
        {
            InsertAt(0, element);
        }

        /// @brief inserts element at las
        /// @param element element to insert
        /// @note calls InsertAt(Count() - 1, element)
        virtual void InsertBack(const ValueTypeT lref element)
        {
            InsertAt(ThisT::Count() - 1, element);
        }

        virtual void Insert(const ValueTypeT lref element) override
        {
            InsertBack(element);
        }

        // **********************************************************************

        virtual void InsertAt(const SizeT index, Iterator<ValueTypeT> lref it, const SizeT count) abstract;

        virtual void InsertAt(const SizeT index, Iterator<ValueTypeT> lref begin, Iterator<ValueTypeT> lref end)
        {
            SizeT count = 0;
            for (auto lref it = begin; it isnot end; it++)
            {
                count++;
            }

            InsertAt(index, begin, count);
        }

        virtual void InsertAt(const SizeT index, const Iterable<ValueTypeT> lref elements, const SizeT count)
        {
            // TODO: fix this, remove need of const_cast
            auto rref begin = const_cast<Iterable<ValueTypeT> lref>(elements).Begin();
            InsertAt(index, begin, count);
        }

        virtual void InsertAt(const SizeT index, const Iterable<ValueTypeT> lref elements)
        {
            // TODO: fix this, remove need of const_cast
            auto rref begin = const_cast<Iterable<ValueTypeT> lref>(elements).Begin();
            auto rref end = const_cast<Iterable<ValueTypeT> lref>(elements).End();
            InsertAt(index, begin, end);
        }

        virtual void InsertAt(const SizeT index, const Collection<ValueTypeT> lref elements)
        {
            InsertAt(index, static_cast<const Iterable<ValueTypeT> lref>(elements), elements.Count());
        }

        template <ValueTypeT... TElements>
        void InsertAt(const SizeT index)
        {
            constexpr ValueTypeT arr{ TElements... };
            InsertAt(ArrayIterator(arr), sizeof...(TElements));
        }

        virtual void InsertFront(Iterator<ValueTypeT> lref it, const SizeT count)
        {
            InsertAt(0, it, count);
        }

        virtual void InsertFront(Iterator<ValueTypeT> lref begin, Iterator<ValueTypeT> lref end)
        {
            InsertAt(0, begin, end);
        }

        virtual void InsertFront(const Iterable<ValueTypeT> lref elements, const SizeT count)
        {
            InsertAt(0, elements, count);
        }

        virtual void InsertFront(const Iterable<ValueTypeT> lref elements)
        {
            InsertAt(0, elements);
        }

        virtual void InsertFront(const Collection<ValueTypeT> lref elements)
        {
            InsertAt(0, elements);
        }

        template <ValueTypeT... TElements>
        void InsertFront(const SizeT index)
        {
            InsertAt<TElements...>(0);
        }

        virtual void InsertBack(Iterator<ValueTypeT> lref it, const SizeT count)
        {
            InsertAt(ThisT::Count() - 1, it, count);
        }

        virtual void InsertBack(Iterator<ValueTypeT> lref begin, Iterator<ValueTypeT> lref end)
        {
            InsertAt(ThisT::Count() - 1, begin, end);
        }

        virtual void InsertBack(const Iterable<ValueTypeT> lref elements, const SizeT count)
        {
            InsertAt(ThisT::Count() - 1, elements, count);
        }

        virtual void InsertBack(const Iterable<ValueTypeT> lref elements)
        {
            InsertAt(ThisT::Count() - 1, elements);
        }

        virtual void InsertBack(const Collection<ValueTypeT> lref elements)
        {
            InsertAt(ThisT::Count() - 1, elements);
        }

        template <ValueTypeT... TElements>
        void InsertBack(const SizeT index)
        {
            InsertAt<TElements...>(ThisT::Count() - 1);
        }

        // **********************************************************************

        /// @brief remove element at index
        /// @param index index of element to remove
        virtual void RemoveAt(const SizeT index) abstract;

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
            RemoveAt(ThisT::Count() - 1);
        }

        virtual void RemoveFront(const ValueTypeT lref element)
        {
            if (SizeT index = FirstIndexOf(element) isnot NPOS)
            {
                RemoveAt(index);
            }
        }

        virtual void RemoveBack(const ValueTypeT lref element)
        {
            if (SizeT index = LastIndexOf(element) isnot NPOS)
            {
                RemoveAt(index);
            }
        }

        virtual void Remove(const ValueTypeT lref element) override
        {
            RemoveFront(element);
        }

        // **********************************************************************

        virtual void RemoveFrom(const SizeT indexFrom, const SizeT indexTo) abstract;

        virtual void RemoveFrom(const SizeT indexFrom)
        {
            RemoveFrom(indexFrom, ThisT::Count() - 1);
        }

        // **********************************************************************
    };

    /// @brief list like structure that can manage memory dynamically
    /// @tparam TValueType type of element to store
    template <typename TValueType>
    class DynamicList : public virtual List<TValueType>, public virtual DynamicCollection<TValueType> {};
}