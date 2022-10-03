#pragma once
#include "SSEngine/Core.hpp"

namespace SSEngine
{
    template <typename TValueType>
    class InputIterator {};

    template <typename TValueType>
    class OutputIterator {};

    template <typename TValueType>
    class ForwardIterator :
        public virtual InputIterator<TValueType>,
        public virtual OutputIterator<TValueType>
    {
        using ThisT = ForwardIterator<TValueType>;

    public:
        using ValueTypeT = TValueType;

    public:
        /// @brief current element value
        /// @return return current element value by ref
        virtual ValueTypeT lref Value() abstract;

        /// @brief current element value
        /// @return return current element value by const ref
        virtual const ValueTypeT lref Value() const abstract;

        /// @brief move iterator to point to next element
        virtual void MoveFwd() noexcept abstract;

        /// @brief compares with other iterator
        /// @param rhs other iterator to compare with
        /// @return 0 if equal, greater than 0 if this is greater else less than 0
        virtual int Compare(const ThisT lref rhs) const noexcept abstract;

        /// @brief ptr operator to return current iteration value
        /// @return value of current iteration
        ValueTypeT lref operator *()
        {
            return Value();
        }

        /// @brief move iterator to point to next element
        /// @note calls MoveFwd()
        ThisT lref operator ++()
        {
            MoveFwd();
            return ptr this;
        }

        /// @brief compares with other iterator
        /// @param rhs other iterator to compare with
        /// @return true if both iterators represent same value
        virtual bool operator ==(const ThisT lref rhs)
        {
            return Compare(rhs) == 0;
        }

        /// @brief compares with other iterator
        /// @param rhs other iterator to compare with
        /// @return false if both iterators represent same value
        /// 
        /// @note this operator is used by c++ range-based for loop
        /// to check the end of iteration
        virtual bool operator !=(const ThisT lref rhs)
        {
            return Compare(rhs) isnot 0;
        }
    };

    template <typename TValueType>
    class BidirectionalIterator : public virtual ForwardIterator<TValueType>
    {
        using ThisT = BidirectionalIterator<TValueType>;

    public:
        virtual void MoveBwd() noexcept abstract;

        /// @brief move iterator to point to previous element
        /// @note calls MoveBwd()
        ThisT lref operator --()
        {
            MoveBwd();
            return ptr this;
        }
    };

    template <typename TValueType>
    class RandomAccessIterator : public virtual BidirectionalIterator<TValueType>
    {
        using ThisT = BidirectionalIterator<TValueType>;
        using SizeT = umax;

    public:
        virtual void MoveBwdBy(const SizeT steps) noexcept abstract;
        virtual void MoveFwdBy(const SizeT steps) noexcept abstract;

        virtual void MoveFwd() noexcept { MoveFwdBy(1); }
        virtual void MoveBwd() noexcept { MoveBwdBy(1); }

        ThisT lref operator + (const SizeT steps)
        {
            MoveFwdBy(steps);
            return ptr this;
        }

        ThisT lref operator - (const SizeT steps)
        {
            MoveBwdBy(steps);
            return ptr this;
        }
    };

    template <typename TValueType>
    using Iterator = ForwardIterator<TValueType>;
}

// TODO: inherit doc from actual type
template <typename TValueType>
using SSIterator = SSEngine::Iterator<TValueType>;