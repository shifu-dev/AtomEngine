#pragma once
#include "SSEngine/Core.hpp"
#include "SSEngine/Collections/Iterable.hpp"

namespace SSEngine
{
    /// @brief a read only data structure
    /// @tparam TValueType type of element to store
    template <typename TValueType>
    class ReadOnlyCollection : public Iterable<TValueType>
    {
        using IterableT = Iterable<TValueType>;

    public:
        using SizeT = typename IterableT::SizeT;
        using ValueTypeT = typename IterableT::ValueTypeT;

    public:

        /// @brief current count of elements
        /// @return count of elements
        virtual SizeT Count() const noexcept abstract;

        /// @brief checks if given element is present in collection
        /// @param element element to compare with
        /// @return true if element is present in the collection 
        virtual bool Contains(const ValueTypeT lref element) const noexcept abstract;
    };

    /// @brief a data structure that can modify elements
    /// @tparam TValueType type of element to store
    template <typename TValueType>
    class Collection : public ReadOnlyCollection<TValueType>
    {
        using ReadOnlyCollectionT = ReadOnlyCollection<TValueType>;

    public:
        using SizeT = typename ReadOnlyCollectionT::SizeT;
        using ValueTypeT = typename ReadOnlyCollectionT::ValueTypeT;

    public:

        /// @brief adds element to collection
        /// @param element element to store
        /// @note position of element is implementation dependent
        virtual void Push(const ValueTypeT lref element) abstract;

        /// @brief removed element from collection
        /// @param element element to remove
        virtual void Remove(const ValueTypeT lref element) abstract;
    };

    /// @brief base class for collections which can manage memory dynamically
    /// @tparam TValueType type of element to store
    template <typename TValueType>
    class DynamicCollection : public Collection<TValueType>
    {
        using CollectionT = Collection<TValueType>;

    public:
        using SizeT = typename CollectionT::SizeT;
        using ValueTypeT = typename CollectionT::ValueTypeT;

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
    };
}