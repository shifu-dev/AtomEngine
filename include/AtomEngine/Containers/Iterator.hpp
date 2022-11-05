#pragma once
#include "AtomEngine/Core.hpp"

namespace Atom
{
    template <typename TElement>
    class ContainerDefination;

    template <typename TElement>
    class InputIterator {};

    template <typename TElement>
    class OutputIterator {};

    template <typename TElement>
    class Iterator : public virtual InputIterator<TElement>, public virtual OutputIterator<TElement>
    {
        using ThisT = Iterator<TElement>;
        using ElementT = TElement;

    public:

        // **************************************************************

        /// @brief current element value
        /// @return return current element value by const ref
        virtual const ElementT ref Value() const noexcept abstract;

        /// @brief current element value
        /// @return return current element value by ref
        virtual ElementT ref Value() noexcept abstract;

        /// @brief ptr operator to return current iteration value by const ref
        /// @return value of current iteration
        const ElementT ref operator *() const noexcept
        {
            return Value();
        }

        /// @brief ptr operator to return current iteration value by ref
        /// @return value of current iteration
        ElementT ref operator *() noexcept
        {
            return Value();
        }

        // **************************************************************

        /// @brief compares with other iterator
        /// @param rhs other iterator to compare with
        /// @return 0 if equal, greater than 0 if this is greater else less than 0
        virtual int Compare(const ThisT ref rhs) const noexcept abstract;

        /// @brief compares with other iterator
        /// @param rhs other iterator to compare with
        /// @return true if both iterators represent same value
        virtual bool operator ==(const ThisT ref rhs) const noexcept
        {
            return Compare(rhs) is 0;
        }

        /// @brief compares with other iterator
        /// @param rhs other iterator to compare with
        /// @return false if both iterators represent same value
        /// 
        /// @note this operator is used by c++ range-based for loop
        /// to check the end of iteration
        virtual bool operator !=(const ThisT ref rhs) const noexcept
        {
            return Compare(rhs) isnot 0;
        }

        // **************************************************************
    };

    template <typename TElement>
    class ForwardIterator : public virtual Iterator<TElement>
    {
        using ThisT = ForwardIterator<TElement>;

    public:

        // **************************************************************

        /// @brief move iterator to point to next element
        virtual void MoveFwd() const noexcept abstract;

        /// @brief move iterator to point to next element
        /// @note calls MoveFwd()
        const ThisT ref operator ++() const noexcept
        {
            MoveFwd();
            return ptr this;
        }

        /// @brief move iterator to point to next element
        /// @note calls MoveFwd()
        ThisT ref operator ++() noexcept
        {
            MoveFwd();
            return ptr this;
        }

        /// @brief move iterator to point to next element
        /// @note calls MoveFwd()
        const ThisT ref operator ++(int) const noexcept
        {
            MoveFwd();
            return ptr this;
        }

        /// @brief move iterator to point to next element
        /// @note calls MoveFwd()
        ThisT ref operator ++(int) noexcept
        {
            MoveFwd();
            return ptr this;
        }

        // **************************************************************
    };

    template <typename TElement>
    class BidirectionalIterator : public virtual ForwardIterator<TElement>
    {
        using ThisT = BidirectionalIterator<TElement>;

    public:

        // **************************************************************

        virtual void MoveBwd() const noexcept abstract;

        /// @brief move iterator to point to previous element
        /// @note calls MoveBwd()
        const ThisT ref operator --() const noexcept
        {
            MoveBwd();
            return ptr this;
        }

        /// @brief move iterator to point to previous element
        /// @note calls MoveBwd()
        ThisT ref operator --() noexcept
        {
            MoveBwd();
            return ptr this;
        }

        /// @brief move iterator to point to previous element
        /// @note calls MoveBwd()
        const ThisT ref operator --(int) const noexcept
        {
            MoveBwd();
            return ptr this;
        }

        /// @brief move iterator to point to previous element
        /// @note calls MoveBwd()
        ThisT ref operator --(int) noexcept
        {
            MoveBwd();
            return ptr this;
        }

        // **************************************************************
    };

    template <typename TElement>
    class RandomAccessIterator : public virtual BidirectionalIterator<TElement>
    {
        using ThisT = BidirectionalIterator<TElement>;

    public:

        // **************************************************************

        virtual void MoveBwdBy(const sizet steps) const noexcept abstract;
        virtual void MoveFwdBy(const sizet steps) const noexcept abstract;

        virtual void MoveFwd() const noexcept override { MoveFwdBy(1); }
        virtual void MoveBwd() const noexcept override { MoveBwdBy(1); }

        ThisT ref operator + (const sizet steps) noexcept
        {
            MoveFwdBy(steps);
            return ptr this;
        }

        const ThisT ref operator + (const sizet steps) const noexcept
        {
            MoveFwdBy(steps);
            return ptr this;
        }

        ThisT ref operator - (const sizet steps) noexcept
        {
            MoveBwdBy(steps);
            return ptr this;
        }

        const ThisT ref operator - (const sizet steps) const noexcept
        {
            MoveBwdBy(steps);
            return ptr this;
        }

        // **************************************************************
    };
}