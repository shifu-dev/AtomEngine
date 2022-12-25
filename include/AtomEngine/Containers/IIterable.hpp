#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/IConstIterable.hpp"

namespace Atom
{
    /// Base type implementing iterable functionality.
    /// 
    /// Types extending from this class will be able to be used in range based for loops.
    /// 
    /// @tparam ElementT Type of element this iterable iterates on.
    template <typename ElementT>
    interface IIterable:
        public virtual IConstIterable<ElementT>
    {
        using IConstIterableT = IConstIterable<ElementT>;
        using ForwardIteratorBoxT = ForwardIteratorBox<ElementT>;

        using IConstIterableT::Begin;

        /// @copydoc IIConstItearble::Begin().
        ForwardIteratorBoxT Begin() noexcept
        {
            return _IterableBegin();
        }

        using IConstIterableT::End;

        /// @copydoc IIConstItearble::End().
        ForwardIteratorBoxT End() noexcept
        {
            return _IterableEnd();
        }

    protected:
        /// @copydoc IIConstItearble::_IterableBegin().
        virtual ForwardIteratorBoxT _IterableBegin() noexcept = 0;

        /// @copydoc IIConstItearble::_IterableEnd().
        virtual ForwardIteratorBoxT _IterableEnd() noexcept = 0;
    };
}