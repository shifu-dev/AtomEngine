#pragma once
#include "SSEngine/Core.hpp"

namespace SSEngine
{
    /// @brief base abstract class for all iterators
    /// @tparam TValueType value type provided by iterator
    template <typename TValueType>
    class Iterator
    {
    public:
        /// @brief value type provided by iterator
        using ValueType = TValueType;

    public:

        /// @brief ptr operator to return current iteration value
        /// @return value of current iteration
        virtual TValueType lref operator *() abstract;

        /// @brief operator++ to move to next iteration
        /// @return returns the iterator to continue the iteration
        virtual Iterator lref operator ++() abstract;

        /// @brief operator== to check the state of current iterator
        /// @param rhs other iterator to compare with
        /// @return true if both iterators represent same value
        /// 
        /// generally used to check if the iteration has reached its end
        virtual bool operator ==(const Iterator<TValueType> lref rhs) abstract;

        /// @brief operator== to check the state of current iterator
        /// @param rhs other iterator to compare with
        /// @return true if both iterators represent same value
        /// 
        /// generally used to check if the iteration has reached its end
        /// this is the acutal operator used for c++ range-based for loop
        /// to check the end of iteration
        virtual bool operator !=(const Iterator<TValueType> lref rhs)
        {
            return (ptr this == rhs) == false;
        }
    };
}

// TODO: inherit doc from actual type
template <typename TValueType>
using SSIterator = SSEngine::Iterator<TValueType>;