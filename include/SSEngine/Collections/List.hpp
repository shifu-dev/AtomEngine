#pragma once
#include "SSEngine/Core.hpp"
#include "SSEngine/Collections/Collection.hpp"

namespace SSEngine
{
    /// @brief a read only list, elements can accessed using indexes
    /// @tparam TValueType type of element to store
    template <typename TValueType>
    class ReadOnlyList : public virtual ReadOnlyCollection<TValueType>
    {
        using IterableT = Iterable<TValueType>;

    public:
        using SizeT = typename IterableT::SizeT;
        using ValueTypeT = typename IterableT::ValueTypeT;

    public:

        /// @brief access element by const ref at index
        /// @param index index of the element to access
        /// @return reference to element at index
        virtual const ValueTypeT lref ElementAt(const SizeT index) const abstract;

        /// @brief finds the index of element
        /// @param element element to find
        /// @return index of element, npos if not found
        virtual SizeT IndexOf(const ValueTypeT lref element) const abstract;
    };

    /// @brief a list like structure manage elements,
    /// elements can be acessed using indexes
    /// @tparam TValueType type of element to store
    template <typename TValueType>
    class List : public virtual ReadOnlyList<TValueType>,
        public virtual Collection<TValueType>
    {
        using ReadOnlyListT = ReadOnlyList<TValueType>;

    public:
        using SizeT = typename ReadOnlyListT::SizeT;
        using ValueTypeT = typename ReadOnlyListT::ValueTypeT;

    public:

        /// @brief access element by ref at index
        /// @param index index of the element to access
        /// @return reference to element at index
        virtual ValueTypeT lref ElementAt(const SizeT index) abstract;

        /// @brief insert element at given index
        /// @param index index to insert element at
        /// @param element element to insert
        virtual void InsertAt(const SizeT index, const ValueTypeT lref element) abstract;

        /// @brief remove element at index
        /// @param index index of element to remove
        virtual void RemoveAt(const SizeT index) abstract;
    };

    /// @brief list like structure that can manage memory dynamically
    /// @tparam TValueType type of element to store
    template <typename TValueType>
    class DynamicList : public virtual List<TValueType>,
        public virtual DynamicCollection<TValueType>
    {
        using ListT = List<TValueType>;

    public:
        using SizeT = typename ListT::SizeT;
        using ValueTypeT = typename ListT::ValueTypeT;
    };
}