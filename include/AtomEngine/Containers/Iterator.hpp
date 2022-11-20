#pragma once
#include "AtomEngine/Core.hpp"

namespace Atom
{
    template <typename TElement>
    class InputIterator {};

    template <typename TElement>
    class OutputIterator {};

    template <typename TElement>
    class Iterator : public virtual InputIterator<TElement>, public virtual OutputIterator<TElement>
    {
        using ThisT = Iterator<TElement>;
        using ElementT = TElement;

        // **************************************************************

        /// @brief current element value
        /// @return return current element value by const ref
        mpublic virtual const ElementT ref Value() const noexcept abstract;

        /// @brief current element value
        /// @return return current element value by ref
        mpublic virtual ElementT ref Value() noexcept abstract;

        /// @brief ptr operator to return current iteration value by const ref
        /// @return value of current iteration
        mpublic const ElementT ref operator *() const noexcept
        {
            return Value();
        }

        /// @brief ptr operator to return current iteration value by ref
        /// @return value of current iteration
        mpublic ElementT ref operator *() noexcept
        {
            return Value();
        }

        // **************************************************************

        /// @brief compares with other iterator
        /// @param rhs other iterator to compare with
        /// @return 0 if equal, greater than 0 if this is greater else less than 0
        mpublic virtual int Compare(const ThisT ref rhs) const noexcept abstract;

        /// @brief compares with other iterator
        /// @param rhs other iterator to compare with
        /// @return true if both iterators represent same value
        mpublic virtual bool operator ==(const ThisT ref rhs) const noexcept
        {
            return Compare(rhs) is 0;
        }

        /// @brief compares with other iterator
        /// @param rhs other iterator to compare with
        /// @return false if both iterators represent same value
        /// 
        /// @note this operator is used by c++ range-based for loop
        /// to check the end of iteration
        mpublic virtual bool operator !=(const ThisT ref rhs) const noexcept
        {
            return Compare(rhs) isnot 0;
        }
    };
}