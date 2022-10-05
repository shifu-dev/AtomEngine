#pragma once
#include "SSEngine/Core.hpp"

namespace SSEngine
{
    template <typename TValueType>
    class InputIterator {};

    template <typename TValueType>
    class OutputIterator {};

    template <typename TValueType>
    class Iterator : public virtual InputIterator<TValueType>, public virtual OutputIterator<TValueType>
    {
        using ThisT = Iterator<TValueType>;

    public:
        using ValueTypeT = TValueType;

    public:

        // **************************************************************

        /// @brief current element value
        /// @return return current element value by const ref
        virtual const ValueTypeT lref Value() const noexcept abstract;

        /// @brief current element value
        /// @return return current element value by ref
        virtual ValueTypeT lref Value() noexcept abstract;

        /// @brief ptr operator to return current iteration value by const ref
        /// @return value of current iteration
        const ValueTypeT lref operator *() const noexcept
        {
            return Value();
        }

        /// @brief ptr operator to return current iteration value by ref
        /// @return value of current iteration
        ValueTypeT lref operator *() noexcept
        {
            return Value();
        }

        // **************************************************************

        /// @brief compares with other iterator
        /// @param rhs other iterator to compare with
        /// @return 0 if equal, greater than 0 if this is greater else less than 0
        virtual int Compare(const ThisT lref rhs) const noexcept abstract;

        /// @brief compares with other iterator
        /// @param rhs other iterator to compare with
        /// @return true if both iterators represent same value
        virtual bool operator ==(const ThisT lref rhs) const noexcept
        {
            return Compare(rhs) iseq 0;
        }

        /// @brief compares with other iterator
        /// @param rhs other iterator to compare with
        /// @return false if both iterators represent same value
        /// 
        /// @note this operator is used by c++ range-based for loop
        /// to check the end of iteration
        virtual bool operator !=(const ThisT lref rhs) const noexcept
        {
            return Compare(rhs) isnot 0;
        }

        // **************************************************************
    };

    template <typename TValueType>
    class ForwardIterator : public virtual Iterator<TValueType>
    {
        using ThisT = ForwardIterator<TValueType>;

    public:

        // **************************************************************

        /// @brief move iterator to point to next element
        virtual void MoveFwd() const noexcept abstract;

        /// @brief move iterator to point to next element
        /// @note calls MoveFwd()
        const ThisT lref operator ++() const noexcept
        {
            MoveFwd();
            return ptr this;
        }

        /// @brief move iterator to point to next element
        /// @note calls MoveFwd()
        ThisT lref operator ++() noexcept
        {
            MoveFwd();
            return ptr this;
        }

        /// @brief move iterator to point to next element
        /// @note calls MoveFwd()
        const ThisT lref operator ++(int) const noexcept
        {
            MoveFwd();
            return ptr this;
        }

        /// @brief move iterator to point to next element
        /// @note calls MoveFwd()
        ThisT lref operator ++(int) noexcept
        {
            MoveFwd();
            return ptr this;
        }

        // **************************************************************
    };

    template <typename TValueType>
    class BidirectionalIterator : public virtual ForwardIterator<TValueType>
    {
        using ThisT = BidirectionalIterator<TValueType>;

    public:

        // **************************************************************

        virtual void MoveBwd() const noexcept abstract;

        /// @brief move iterator to point to previous element
        /// @note calls MoveBwd()
        const ThisT lref operator --() const noexcept
        {
            MoveBwd();
            return ptr this;
        }

        /// @brief move iterator to point to previous element
        /// @note calls MoveBwd()
        ThisT lref operator --() noexcept
        {
            MoveBwd();
            return ptr this;
        }

        /// @brief move iterator to point to previous element
        /// @note calls MoveBwd()
        const ThisT lref operator --(int) const noexcept
        {
            MoveBwd();
            return ptr this;
        }

        /// @brief move iterator to point to previous element
        /// @note calls MoveBwd()
        ThisT lref operator --(int) noexcept
        {
            MoveBwd();
            return ptr this;
        }

        // **************************************************************
    };

    template <typename TValueType>
    class RandomAccessIterator : public virtual BidirectionalIterator<TValueType>
    {
        using ThisT = BidirectionalIterator<TValueType>;
        using SizeT = sizet;

    public:

        // **************************************************************

        virtual void MoveBwdBy(const SizeT steps) const noexcept abstract;
        virtual void MoveFwdBy(const SizeT steps) const noexcept abstract;

        virtual void MoveFwd() const noexcept override { MoveFwdBy(1); }
        virtual void MoveBwd() const noexcept override { MoveBwdBy(1); }

        ThisT lref operator + (const SizeT steps) noexcept
        {
            MoveFwdBy(steps);
            return ptr this;
        }

        const ThisT lref operator + (const SizeT steps) const noexcept
        {
            MoveFwdBy(steps);
            return ptr this;
        }

        ThisT lref operator - (const SizeT steps) noexcept
        {
            MoveBwdBy(steps);
            return ptr this;
        }

        const ThisT lref operator - (const SizeT steps) const noexcept
        {
            MoveBwdBy(steps);
            return ptr this;
        }

        // **************************************************************
    };
}