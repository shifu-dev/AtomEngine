#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Callable/ICallable.hpp"
#include "AtomEngine/Containers/BoxedForwardIterator.hpp"

namespace Atom
{
    /// Base type implementing iterable functionality.
    /// 
    /// Types extending from this class will be able to be used in range based for loops.
    /// 
    /// @tparam TElement Type of element this iterable iterates on.
    template <typename TElement>
    interface IIterable
    {
        using ElementT = TElement;                                          ///< ----
        using BoxedForwardIteratorT = BoxedForwardIterator<ElementT>;       ///< ----
        using ConstForEachActionT = IAction<const ElementT ref>;             ///< ----
        using ForEachActionT = IAction<ElementT ref>;                        ///< ----

        /// @{ ----------------------------------------------------------------------------
        /// Helper function for ForEach().
        /// 
        /// @tparam TFunctor Functor Type.
        /// @tparam EnableIf Enable only if \p{Functor} type is not ICallable type.
        ///         This is to avoid accepting ICallable types as this takes 
        ///         precedence over ForEach() accepting ICallable object.
        /// 
        /// @param functor Functor object, this object is wrapped using @ref ICallable::Create().
        mpublic template <typename TFunctor>
            void ForEachT(const TFunctor ref functor) const
        {
            ForEach(ConstForEachActionT::Create(functor));
        }

        mpublic template <typename TFunctor>
            void ForEachT(const TFunctor ref functor)
        {
            ForEach(ForEachActionT::Create(functor));
        }
        /// @} ----------------------------------------------------------------------------

        /// @{ ----------------------------------------------------------------------------
        /// \p{foreach} loop implemented using ICallable object.
        /// 
        /// Begin() uses BoxedForwardIteratorT which may allocate memory.
        /// But this method is allocation free.
        /// 
        /// @param callback ICallable object to invoke for each element.
        mpublic virtual void ForEach(const ConstForEachActionT ref callback) const abstract;

        mpublic virtual void ForEach(const ForEachActionT ref callback) abstract;
        /// @} ----------------------------------------------------------------------------

        /// @{ ----------------------------------------------------------------------------
        /// IIterator to the first element.
        /// 
        /// @return BoxedForwardIterator pointing to first element.
        /// 
        /// @note
        /// - Calls mIterableBegin().
        /// - Begin() is the standard name to provide IIterator to the first element,
        ///   making Begin() virtual will not allow derived classes to overload this function.
        mpublic BoxedForwardIteratorT Begin() noexcept
        {
            return mIterableBegin();
        }

        mpublic const BoxedForwardIteratorT Begin() const noexcept
        {
            return mIterableBegin();
        }
        /// @} ----------------------------------------------------------------------------

        /// @{ ----------------------------------------------------------------------------
        /// IIterator to the last element.
        /// 
        /// @return BoxedForwardIterator pointing to last element.
        /// 
        /// @note
        /// - Calls mIterableEnd().
        /// - End() is the standard name to provide IIterator to the first element,
        ///   making End() virtual will not allow derived classes to overload this function.
        mpublic BoxedForwardIteratorT End() noexcept
        {
            return mIterableEnd();
        }

        mpublic const BoxedForwardIteratorT End() const noexcept
        {
            return mIterableEnd();
        }
        /// @} ----------------------------------------------------------------------------

        /// @{ ----------------------------------------------------------------------------
        /// Implementation function for Begin().
        mprotected virtual BoxedForwardIteratorT mIterableBegin() noexcept abstract;

        mprotected virtual const BoxedForwardIteratorT mIterableBegin() const noexcept abstract;
        /// @} ----------------------------------------------------------------------------

        /// @{ ----------------------------------------------------------------------------
        /// Implementation function for End().
        mprotected virtual BoxedForwardIteratorT mIterableEnd() noexcept abstract;

        mprotected virtual const BoxedForwardIteratorT mIterableEnd() const noexcept abstract;
        /// @} ----------------------------------------------------------------------------
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