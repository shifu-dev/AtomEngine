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
        using ContainerDefinationT = ContainerDefination<TElement>;
        using SizeT = typename ContainerDefinationT::SizeT;
        using ElementT = typename ContainerDefinationT::ElementT;
        using EqualityComparerT = typename ContainerDefinationT::EqualityComparerT;

    public:
        using SizeType = SizeT;
        using ElementType = ElementT;

    public:

        /// @brief current count of elements
        /// @return count of elements
        virtual SizeT Count() const noexcept abstract;

        virtual bool IsEmpty() const noexcept
        {
            return Count() == 0;
        }

        /// @brief checks if given element is present in collection
        /// @param element element to compare with
        /// @param comparer comparer used to compare elements
        /// @return true if element is present in the collection
        virtual bool Contains(const ElementT lref element, const EqualityComparerT lref comparer) const noexcept abstract;

        /// @brief adds element to collection
        /// @param element element to store
        /// @note position of element is implementation dependent
        virtual void Insert(const ElementT lref element) abstract;

        /// @brief removed element from collection
        /// @param element element to remove
        virtual void Remove(const ElementT lref element) abstract;
    };

    /// @brief base class for collections which can manage memory dynamically
    /// @tparam TElement type of element to store
    template <typename TElement>
    class DynamicCollection : public virtual Collection<TElement>
    {
        using ContainerDefinationT = ContainerDefination<TElement>;
        using SizeT = typename ContainerDefinationT::SizeT;
        using ElementT = typename ContainerDefinationT::ElementT;

    public:
        using SizeType = SizeT;
        using ElementType = ElementT;

    public:

        /// @brief resizes the underlying memory
        /// @param count count of objects to allocate memor for
        /// @note this does not change element count
        virtual void Resize(const SizeT count) abstract;

        /// @brief asks the collection to reserve memory for count elements
        /// @param count minimum count of elements to reserve memory for
        /// @return count of reserved memory for element
        virtual SizeT Reserve(const SizeT count) abstract;

        /// @brief current allocated memory
        /// @return count of memory for element currently allocated
        virtual SizeT Capacity() abstract;

        /// @brief resizes capacity equal to count
        /// @return count of memory for element currently allocated
        virtual SizeT ShrinkToFit() abstract;
    };
}