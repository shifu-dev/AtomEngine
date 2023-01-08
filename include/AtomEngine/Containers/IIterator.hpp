#pragma once
#include "AtomEngine/Core.hpp"

namespace Atom
{
    /// Object to iterate over a collection of elements.
    /// This Iterator does not modifies the collection or its elements.
    /// 
    /// @tparam ElementT Type of element Iterator iterates over.
    template <typename ElementT>
    interface IConstIterator
    {
        using ThisT = IConstIterator<ElementT>;

    /// ----------------------------------------------------------------------------

        /// Get const reference to current element.
        virtual const ElementT& Value() const = 0;

        /// Get const reference to current element.
        const ElementT& operator * () const
        {
            return Value();
        }

        /// Get const pointer to current element.
        const ElementT* operator -> () const
        {
            return &Value();
        }

        virtual void Reset() const noexcept = 0;

        /// Checks if iterator has reached its end.
        /// 
        /// @returns @true if iterator has reached its end, else @false.
        virtual bool IsEnd() const noexcept = 0;

    /// ----------------------------------------------------------------------------

        /// Moves IIterator forward to point to next element.
        virtual void MoveFwd() const = 0;

        /// @copydetail MoveFwd()
        /// @note
        /// - Calls MoveFwd()
        const ThisT& operator ++ () const
        {
            MoveFwd();
            return *this;
        }

        /// @copydetail MoveFwd()
        /// @note
        /// - Does not follow postfix definations, works same as prefix.
        /// - Calls MoveFwd()
        const ThisT& operator ++ (int) const
        {
            MoveFwd();
            return *this;
        }
    };

    /// Object to iterate over container elements.
    /// 
    /// @tparam ElementT Type of element IIterator iterates over.
    template <typename ElementT>
    interface IIterator:
        public virtual IConstIterator<ElementT>
    {
        /// Get reference to current element.
        /// 
        /// @throws OutOfBoundsException If IsEnd() == true.
        virtual ElementT& Value() = 0;

        /// Get reference to current element.
        ElementT& operator * ()
        {
            return Value();
        }

        /// Get pointer to current element.
        ElementT* operator -> ()
        {
            return &Value();
        }
    };
}