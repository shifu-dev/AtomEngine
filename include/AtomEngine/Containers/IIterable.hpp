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
        using ForwardIteratorBoxT = ForwardIteratorBox<ElementT>;
        using ForEachActionT = ILoopAction<ElementT&>;

        /// @copydoc IIConstItearble::ForEachT().
        template <typename FunctorT, EnableIf<!IsSubClass<ForEachActionT, FunctorT>> = 0>
        void ForEach(const FunctorT& functor)
        {
            ForEach(ForEachActionT::Create(functor));
        }

        /// @copydoc IIConstItearble::ForEach().
        virtual void ForEach(ForEachActionT& callback) abstract;

        /// @copydoc IIConstItearble::Begin().
        ForwardIteratorBoxT Begin() noexcept
        {
            return _IterableBegin();
        }

        /// @copydoc IIConstItearble::End().
        ForwardIteratorBoxT End() noexcept
        {
            return _IterableEnd();
        }

    protected:
        /// @copydoc IIConstItearble::_IterableBegin().
        virtual ForwardIteratorBoxT _IterableBegin() noexcept abstract;

        /// @copydoc IIConstItearble::_IterableEnd().
        virtual ForwardIteratorBoxT _IterableEnd() noexcept abstract;
    };

    template <typename ElementT>
    class iterate
    {
        using IterableT = IIterable<ElementT>;

    /// ----------------------------------------------------------------------------
    public:
        iterate(const IterableT& iterable):
            _iterable(iterable) { }

    /// ----------------------------------------------------------------------------
    public:
        /// @{ 
        /// This == used by range based for loop.
        /// See Begin() for implementation.
        /// 
        /// @note AtomEngine does not use begin() becuase it does not
        ///       follow our naming standards.
        auto begin() noexcept
        {
            return _iterable.Begin();
        }

        const auto begin() const noexcept
        {
            return _iterable.Begin();
        }
        /// @} 

        /// @{ 
        /// This == used by range based for loop.
        /// See End() for implementation.
        /// 
        /// @note AtomEngine does not use end() becuase it does not
        ///       follow our naming standards.
        auto end() noexcept
        {
            return _iterable.End();
        }

        const auto end() const noexcept
        {
            return _iterable.End();
        }
        /// @} 

    private:
        IterableT& _iterable;
    };
}