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
        using EqualityComparerT = typename CollectionT::EqualityComparerT;
        static constexpr SizeT npos = -1;

    public:

        /// @brief access element by const ref at index
        /// @param index index of the element to access
        /// @return reference to element at index
        virtual const ValueTypeT lref ElementAt(const SizeT index) const abstract;

        /// @brief access element by const ref at index
        /// @return reference last element
        virtual const ValueTypeT lref ElementFront() const
        {
            return ElementAt(0);
        }

        /// @brief access element by const ref at index
        /// @return reference first element
        virtual const ValueTypeT lref ElementBack() const
        {
            return ElementAt(ThisT::Count() - 1);
        }

        /// @brief finds the index of element
        /// @param element element to find
        /// @return index of element, npos if not found
        virtual SizeT IndexOf(const ValueTypeT lref element, const EqualityComparerT lref comparer) const abstract;

        virtual bool Contains(const ValueTypeT lref element, const EqualityComparerT lref comparer) const noexcept override
        {
            return IndexOf(element, comparer) isnot npos;
        }

        /// @brief access element by ref at index
        /// @param index index of the element to access
        /// @return reference to element at index
        virtual ValueTypeT lref ElementAt(const SizeT index) abstract;

        /// @brief access element by ref at index
        /// @return reference last element
        virtual ValueTypeT lref ElementFront()
        {
            return ElementAt(0);
        }

        /// @brief access element by ref at index
        /// @return reference first element
        virtual ValueTypeT lref ElementBack()
        {
            return ElementAt(ThisT::Count() - 1);
        }

        /// @brief insert element at given index
        /// @param index index to insert element at
        /// @param element element to insert
        virtual void InsertAt(const SizeT index, const ValueTypeT lref element) abstract;

        /// @brief remove element at index
        /// @param index index of element to remove
        virtual void RemoveAt(const SizeT index) abstract;

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
    };

    /// @brief list like structure that can manage memory dynamically
    /// @tparam TValueType type of element to store
    template <typename TValueType>
    class DynamicList : public virtual List<TValueType>, public virtual DynamicCollection<TValueType> {};
}