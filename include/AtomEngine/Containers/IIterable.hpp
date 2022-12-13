#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/IConstIterable.hpp"

namespace Atom
{
    /// Base type implementing iterable functionality.
    /// 
    /// Types extending from this class will be able to be used in range based for loops.
    /// 
    /// @tparam TElement Type of element this iterable iterates on.
    template <typename TElement>
    interface IIterable : public virtual IConstIterable<TElement>
    {
        using ElementT = TElement;
        using BoxedForwardIteratorT = BoxedForwardIterator<ElementT>;
        using ForEachActionT = ILoopAction<ElementT ref>;

        /// ----------------------------------------------------------------------------
        /// @copydoc IIConstItearble::ForEachT().
        mpublic template <typename TFunctor,
            EnableIf<!IsSubClass<ForEachActionT, TFunctor>> = 0>
            void ForEach(const TFunctor ref functor)
        {
            ForEach(ForEachActionT::Create(functor));
        }

        /// ----------------------------------------------------------------------------
        /// @copydoc IIConstItearble::ForEach().
        mpublic virtual void ForEach(const ForEachActionT ref callback) abstract;

        /// ----------------------------------------------------------------------------
        /// @copydoc IIConstItearble::Begin().
        mpublic BoxedForwardIteratorT Begin() noexcept
        {
            return mIterableBegin();
        }

        /// ----------------------------------------------------------------------------
        /// @copydoc IIConstItearble::End().
        mpublic BoxedForwardIteratorT End() noexcept
        {
            return mIterableEnd();
        }

        /// ----------------------------------------------------------------------------
        /// @copydoc IIConstItearble::mIterableBegin().
        mprotected virtual BoxedForwardIteratorT mIterableBegin() noexcept abstract;

        /// ----------------------------------------------------------------------------
        /// @copydoc IIConstItearble::mIterableEnd().
        mprotected virtual BoxedForwardIteratorT mIterableEnd() noexcept abstract;
    };

    template <typename TIterable>
    class iterate
    {
        mpublic iterate(TIterable ref iterable) :
            mIterable(iterable) { }

        /// @{ ----------------------------------------------------------------------------
        /// This is used by range based for loop.
        /// See Begin() for implementation.
        /// 
        /// @note AtomEngine does not use begin() becuase it does not
        ///       follow our naming standards.
        mpublic auto begin() noexcept
        {
            return mIterable.Begin();
        }

        mpublic const auto begin() const noexcept
        {
            return mIterable.Begin();
        }
        /// @} ----------------------------------------------------------------------------

        /// @{ ----------------------------------------------------------------------------
        /// This is used by range based for loop.
        /// See End() for implementation.
        /// 
        /// @note AtomEngine does not use end() becuase it does not
        ///       follow our naming standards.
        mpublic auto end() noexcept
        {
            return mIterable.End();
        }

        mpublic const auto end() const noexcept
        {
            return mIterable.End();
        }
        /// @} ----------------------------------------------------------------------------

        mprivate TIterable ref mIterable;
    };
}