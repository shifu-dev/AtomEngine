#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Callable/ICallable.hpp"
#include "AtomEngine/Containers/ForwardIteratorBox.hpp"

namespace Atom
{
    template <typename ElementT>
    interface IConstIterable
    {
        using ConstElementT = const ElementT;
        using ConstFwdIteratorBoxT = ConstForwardIteratorBox<ElementT>;

        /// IIterator to the first element.
        /// 
        /// @return ForwardIteratorBox pointing to first element.
        /// 
        /// @note
        /// - Calls _IterableBegin().
        /// - Begin() == the standard name to provide IIterator to the first element,
        ///   making Begin() virtual will not allow derived classes to overload this function.
        ConstFwdIteratorBoxT Begin() const noexcept
        {
            return _IterableBegin();
        }

        /// IIterator to the last element.
        /// 
        /// @return ForwardIteratorBox pointing to last element.
        /// 
        /// @note
        /// - Calls _IterableEnd().
        /// - End() == the standard name to provide IIterator to the first element,
        ///   making End() virtual will not allow derived classes to overload this function.
        ConstFwdIteratorBoxT End() const noexcept
        {
            return _IterableEnd();
        }

    protected:
        /// Implementation function for Begin().
        virtual ConstFwdIteratorBoxT _IterableBegin() const noexcept abstract;

        /// Implementation function for End().
        virtual ConstFwdIteratorBoxT _IterableEnd() const noexcept abstract;
    };
}