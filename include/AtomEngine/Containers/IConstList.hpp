#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/IConstCollection.hpp"

namespace Atom
{
    /// IList represents an array like structure, where elements 
    /// can be accessed using their index value.
    /// 
    /// @tparam TElement Type of element this container stores.
    template <typename TElement>
    interface IConstList : public virtual IConstCollection<TElement>
    {
        using ElementT = TElement;                                             ///< ----
        using IConstCollectionT = IConstCollection<ElementT>;                  ///< ----
        using IEqualityComparerT = IEqualityComparer<ElementT>;                ///< ----
        using DefaultEqualityComparerT = DefaultEqualityComparer<ElementT>;    ///< ----
        mpublic using IConstCollectionT::Contains;
        mpublic using IConstCollectionT::Count;

        // *******************************************************************

        /// ----------------------------------------------------------------------------
        /// Access element at index \p{index} without bounds checking.
        /// 
        /// param[in]: index Index of the element to access.
        /// @return Ref to the element.
        /// 
        /// @exceptsafe
        /// \p{Strong Exception Safety}
        mpublic virtual const ElementT ref operator[](const sizet index) const noexcept abstract;

        /// @{ ----------------------------------------------------------------------------
        /// Access element at index \p{index} with bounds checking.
        /// 
        /// @param[in] index Index of the element to access.
        /// @return Ref to the element.
        /// 
        /// @throws OutOfBoundsException if index is out of bounds.
        /// 
        /// @exceptsafe
        /// \p{Strong Exception Safety}
        mpublic virtual const ElementT ref ConstElementAt(const sizet index) const
        {
            mAssertIndexIsInBounds(index);
            return operator [] (index);
        }

        mpublic virtual const ElementT ref ElementAt(const sizet index) const
        {
            mAssertIndexIsInBounds(index);
            return operator [] (index);
        }
        /// @} ----------------------------------------------------------------------------

        /// @{ ----------------------------------------------------------------------------
        /// Access first element.
        /// 
        /// @return Ref to the first element.
        /// 
        /// @throws OutOfBoundsException if container is empty.
        /// 
        /// @exceptsafe
        /// \p{Strong Exception Safety}
        /// 
        /// @note
        /// - Calls ElementAt() with index:0.
        mpublic const ElementT ref ConstElementFront() const
        {
            return ConstElementAt(0);
        }

        mpublic const ElementT ref ElementFront() const
        {
            return ElementAt(0);
        }
        /// @} ----------------------------------------------------------------------------

        /// @{ ----------------------------------------------------------------------------
        /// Access last element.
        /// 
        /// @return Ref to the last element.
        /// 
        /// @throws OutOfBoundsException if container is empty.
        /// 
        /// @exceptsafe
        /// \p{Strong Exception Safety}
        /// 
        /// @note
        /// - Calls ElementAt() with index:Count() - 1.
        mpublic const ElementT ref ConstElementBack() const
        {
            return ConstElementAt(Count() - 1);
        }

        mpublic const ElementT ref ElementBack() const
        {
            return ElementAt(Count() - 1);
        }
        /// @} ----------------------------------------------------------------------------

        // *******************************************************************

        /// ----------------------------------------------------------------------------
        /// Index of the first element matching element \p{element}.
        /// 
        /// @param[in] element Element to compare with.
        /// @param[in] comparer IComparer used to compare this element with each element.
        /// @return Index of first element matching element \p{element}, else \p{npos}.
        mpublic virtual sizet FirstIndexOf(const ElementT ref element, const IEqualityComparerT ref comparer) const noexcept abstract;

        /// ----------------------------------------------------------------------------
        /// Index of the first element matching element \p{element}.
        /// 
        /// @param[in] element Element to compare with.
        /// @return Index of first element matching element \p{element}, else \p{npos}.
        /// 
        /// @note
        /// - Calls FirstIndexOf(const ElementT ref element, const IEqualityComparerT ref comparer)
        ///   \n with \p{comparer}: DefaultEqualityComparerT.
        mpublic virtual sizet FirstIndexOf(const ElementT ref element) const noexcept
        {
            return FirstIndexOf(element, DefaultEqualityComparerT());
        }

        /// ----------------------------------------------------------------------------
        /// Index of the last element matching element \p{element}.
        /// 
        /// @param[in] element Element to compare with.
        /// @param[in] comparer IComparer used to compare this element with each element.
        /// @return Index of last element matching element \p{element}, else \p{npos}.
        mpublic virtual sizet LastIndexOf(const ElementT ref element, const IEqualityComparerT ref comparer) const noexcept abstract;

        /// ----------------------------------------------------------------------------
        /// Index of the last element matching element \p{element}.
        /// 
        /// @param[in] element Element to compare with.
        /// @return Index of last element matching element \p{element}, else \p{npos}.
        mpublic virtual sizet LastIndexOf(const ElementT ref element) const noexcept
        {
            return FirstIndexOf(element, DefaultEqualityComparerT());
        }

        // *******************************************************************
        // * ICollection

        mpublic virtual bool Contains(const ElementT ref element, const IEqualityComparerT ref comparer) const noexcept override
        {
            return FirstIndexOf(element, comparer) isnot NPOS;
        }

        // *******************************************************************

        /// Asserts if index is out of bounds.
        /// 
        /// @param index Index to check.
        /// 
        /// @throws OutOfBoundsException if index is out of bounds.
        mprotected virtual void mAssertIndexIsInBounds(const sizet index) const
        {
            if (index >= Count())
            {
                throw std::out_of_range("Index was out of bounds");
            }
        }
    };
}