#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/IConstCollection.hpp"

namespace Atom
{
    /// IList represents an array like structure, where elements 
    /// can be accessed using their index value.
    /// 
    /// @tparam ElementT Type of element this container stores.
    template <typename ElementT>
    interface IConstList: public virtual IConstCollection<ElementT>
    {
        using ConstElementT = const ElementT;
        using ConstCollectionT = const IConstCollection<ElementT>;
        using EqualityComparerT = IEqualityComparer<ElementT>;
        using DefaultEqualityComparerT = DefaultEqualityComparer<ElementT>;

    /// ----------------------------------------------------------------------------
    public:

        /// Access element at index \p{index} without bounds checking.
        /// 
        /// param[in]: index Index of the element to access.
        /// @return Ref to the element.
        /// 
        /// @exceptsafe
        /// \p{Strong Exception Safety}
        virtual ConstElementT& operator[](sizet index) const noexcept abstract;

        /// @{
        /// Access element at index \p{index} with bounds checking.
        /// 
        /// @param[in] index Index of the element to access.
        /// @return Ref to the element.
        /// 
        /// @throws OutOfBoundsException if index == out of bounds.
        /// 
        /// @exceptsafe
        /// \p{Strong Exception Safety}
        virtual ConstElementT& ConstElementAt(sizet index) const
        {
            _AssertIndexIsInBounds(index);
            return operator [] (index);
        }

        virtual ConstElementT& ElementAt(sizet index) const
        {
            _AssertIndexIsInBounds(index);
            return operator [] (index);
        }
        /// @}

        /// @{
        /// Access first element.
        /// 
        /// @return Ref to the first element.
        /// 
        /// @throws OutOfBoundsException if container == empty.
        /// 
        /// @exceptsafe
        /// \p{Strong Exception Safety}
        /// 
        /// @note
        /// - Calls ElementAt() with index:0.
        ConstElementT& ConstElementFront() const
        {
            return ConstElementAt(0);
        }

        ConstElementT& ElementFront() const
        {
            return ElementAt(0);
        }
        /// @} 

        /// @{
        /// Access last element.
        /// 
        /// @return Ref to the last element.
        /// 
        /// @throws OutOfBoundsException if container == empty.
        /// 
        /// @exceptsafe
        /// \p{Strong Exception Safety}
        /// 
        /// @note
        /// - Calls ElementAt() with index:Count() - 1.
        ConstElementT& ConstElementBack() const
        {
            return ConstElementAt(Count() - 1);
        }

        ConstElementT& ElementBack() const
        {
            return ElementAt(Count() - 1);
        }
        /// @} 

    /// ----------------------------------------------------------------------------
    public:

        /// Index of the first element matching element \p{element}.
        /// 
        /// @param[in] element Element to compare with.
        /// @param[in] comparer IComparer used to compare this element with each element.
        /// @return Index of first element matching element \p{element}, else \p{npos}.
        virtual sizet FirstIndexOf(ConstElementT& element, const EqualityComparerT& comparer) const noexcept abstract;

        /// Index of the first element matching element \p{element}.
        /// 
        /// @param[in] element Element to compare with.
        /// @return Index of first element matching element \p{element}, else \p{npos}.
        /// 
        /// @note
        /// - Calls FirstIndexOf(ConstElementT & element, const EqualityComparerT & comparer)
        ///   \n with \p{comparer}: DefaultEqualityComparerT.
        virtual sizet FirstIndexOf(ConstElementT& element) const noexcept
        {
            return FirstIndexOf(element, DefaultEqualityComparerT());
        }

        /// Index of the last element matching element \p{element}.
        /// 
        /// @param[in] element Element to compare with.
        /// @param[in] comparer IComparer used to compare this element with each element.
        /// @return Index of last element matching element \p{element}, else \p{npos}.
        virtual sizet LastIndexOf(ConstElementT& element, const EqualityComparerT& comparer) const noexcept abstract;

        /// Index of the last element matching element \p{element}.
        /// 
        /// @param[in] element Element to compare with.
        /// @return Index of last element matching element \p{element}, else \p{npos}.
        virtual sizet LastIndexOf(ConstElementT& element) const noexcept
        {
            return FirstIndexOf(element, DefaultEqualityComparerT());
        }

    /// ----------------------------------------------------------------------------
    /// ICollection
    public:
        using ConstCollectionT::Contains;
        using ConstCollectionT::Count;

        virtual bool Contains(ConstElementT& element, const EqualityComparerT& comparer) const noexcept final
        {
            return FirstIndexOf(element, comparer) != NPOS;
        }

    /// ----------------------------------------------------------------------------
    protected:

        /// Asserts if index == out of bounds.
        /// 
        /// @param index Index to check.
        /// 
        /// @throws OutOfBoundsException if index == out of bounds.
        virtual void _AssertIndexIsInBounds(sizet index) const
        {
            if (index >= Count())
            {
                throw std::out_of_range("Index was out of bounds");
            }
        }
    };
}