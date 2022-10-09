#pragma once
#include "SSEngine/Core.hpp"
#include "SSEngine/Collections/Iterable.hpp"

namespace SSEngine
{
    /// @brief a data structure that can modify elements
    /// @tparam TElement type of element to store
    template <typename TElement>
    class Collection : public virtual Iterable<TElement>
    {
        using IterableT = Iterable<TElement>;

    public:
        using SizeType = typename IterableT::SizeType;
        using ElementType = typename IterableT::ElementType;
        using ComparerT = typename IterableT::ComparerT;
        using EqualityComparerT = typename IterableT::EqualityComparerT;
        using DefaultEqualityComparerT = typename IterableT::DefaultEqualityComparerT;
        using IterableT::NPOS;

    public:

        /// @brief current count of elements
        /// @return count of elements
        virtual SizeType Count() const noexcept abstract;

        virtual bool IsEmpty() const noexcept
        {
            return Count() == 0;
        }

        /// @brief checks if given element is present in collection
        /// @param element element to compare with
        /// @param comparer comparer used to compare elements
        /// @return true if element is present in the collection
        virtual bool Contains(const ElementType lref element, const EqualityComparerT lref comparer) const noexcept abstract;

        /// @brief adds element to collection
        /// @param element element to store
        /// @note position of element is implementation dependent
        virtual void Insert(const ElementType lref element) abstract;

        /// @brief removed element from collection
        /// @param element element to remove
        virtual void Remove(const ElementType lref element) abstract;
    };

    /// @brief base class for collections which can manage memory dynamically
    /// @tparam TElement type of element to store
    template <typename TElement>
    class DynamicCollection : public virtual Collection<TElement>
    {
        using CollectionT = Collection<TElement>;

    public:
        using SizeType = typename CollectionT::SizeType;
        using ElementType = typename CollectionT::ElementType;
        using ComparerT = typename CollectionT::ComparerT;
        using EqualityComparerT = typename CollectionT::EqualityComparerT;
        using CollectionT::NPOS;

    public:

        /// @brief resizes the underlying memory
        /// @param count count of objects to allocate memor for
        /// @note this does not change element count
        virtual void Resize(const SizeType count) abstract;

        /// @brief asks the collection to reserve memory for count elements
        /// @param count minimum count of elements to reserve memory for
        /// @return count of reserved memory for element
        virtual SizeType Reserve(const SizeType count) abstract;

        /// @brief current allocated memory
        /// @return count of memory for element currently allocated
        virtual SizeType Capacity() abstract;

        /// @brief resizes capacity equal to count
        /// @return count of memory for element currently allocated
        virtual SizeType ShrinkToFit() abstract;
    };
}