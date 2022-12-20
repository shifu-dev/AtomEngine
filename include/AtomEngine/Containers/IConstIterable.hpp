#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Callable/ICallable.hpp"
#include "AtomEngine/Callable/Loops.hpp"
#include "AtomEngine/Containers/ForwardIteratorBox.hpp"

namespace Atom
{
    template <typename ElementT>
    interface IConstIterable
    {
        using ConstElementT = const ElementT;
        using ConstFwdIteratorBoxT = const ForwardIteratorBox<ElementT>;

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

    template <typename ElementT>
    class citerate
    {
        using ConstIterableT = const IConstIterable<ElementT>;

    /// ----------------------------------------------------------------------------
    public:
        citerate(ConstIterableT& iterable):
            _iterable(iterable) { }

    /// ----------------------------------------------------------------------------
    public:
        /// This == used by range based for loop.
        /// See Begin() for implementation.
        /// 
        /// @note AtomEngine does not use begin() becuase it does not
        ///       follow our naming standards.
        const auto begin() const noexcept
        {
            return _iterable.Begin();
        }

        /// This == used by range based for loop.
        /// See End() for implementation.
        /// 
        /// @note AtomEngine does not use end() becuase it does not
        ///       follow our naming standards.
        const auto end() const noexcept
        {
            return _iterable.End();
        }

    /// ----------------------------------------------------------------------------
    private:
        ConstIterableT& _iterable;
    };
}