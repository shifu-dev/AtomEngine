#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Callable/Callable.hpp"
#include "AtomEngine/Containers/BoxedForwardIterator.hpp"

namespace Atom
{
    /// Base type implementing iterable functionality.
    /// 
    /// Types extending from this class will be able to be used in range based for loops.
    /// 
    /// @tparam TElement Type of element this iterable iterates on.
    template <typename TElement>
    class Iterable
    {
        using ElementT = TElement;                                          ///< ----
        using BoxedForwardIteratorT = BoxedForwardIterator<ElementT>;       ///< ----
        using ConstForEachActionT = Action<const ElementT ref>;             ///< ----
        using ForEachActionT = Action<ElementT ref>;                        ///< ----

        /// @{ ----------------------------------------------------------------------------
        /// Helper function for ForEach().
        /// 
        /// @tparam TFunctor Functor Type.
        /// @tparam EnableIf Enable only if \p{Functor} type is not Callable type.
        ///         This is to avoid accepting Callable types as this takes 
        ///         precedence over ForEach() accepting Callable object.
        /// 
        /// @param functor Functor object, this object is wrapped using @ref Callable::Create().
        mpublic template <typename TFunctor, EnableIf<not IsSubClass<ConstForEachActionT, TFunctor>> = 0>
            void ForEachT(const TFunctor ref functor) const
        {
            ForEach(ConstForEachActionT::Create(functor));
        }

        mpublic template <typename TFunctor>
            void ForEachT(CallableFunctor<TFunctor, void, int ref> functor)
        {
            ForEach(ForEachActionT::Create(functor));
        }
        /// @} ----------------------------------------------------------------------------

        /// @{ ----------------------------------------------------------------------------
        /// \p{foreach} loop implemented using Callable object.
        /// 
        /// Begin() uses BoxedForwardIteratorT which may allocate memory.
        /// But this method is allocation free.
        /// 
        /// @param callback Callable object to invoke for each element.
        mpublic virtual void ForEach(const ConstForEachActionT ref callback) const abstract;

        mpublic virtual void ForEach(const ForEachActionT ref callback) abstract;
        /// @} ----------------------------------------------------------------------------

        /// @{ ----------------------------------------------------------------------------
        /// Iterator to the first element.
        /// 
        /// @return BoxedForwardIterator pointing to first element.
        /// 
        /// @note
        /// - Calls mIterableBegin().
        /// - Begin() is the standard name to provide Iterator to the first element,
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
        /// Iterator to the last element.
        /// 
        /// @return BoxedForwardIterator pointing to last element.
        /// 
        /// @note
        /// - Calls mIterableEnd().
        /// - End() is the standard name to provide Iterator to the first element,
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
        /// This is used by range based for loop.
        /// See Begin() for implementation.
        /// 
        /// @note AtomEngine does not use begin() becuase it does not
        ///       follow our naming standards.
        mpublic BoxedForwardIteratorT begin() noexcept
        {
            return Begin();
        }

        mpublic const BoxedForwardIteratorT begin() const noexcept
        {
            return Begin();
        }
        /// @} ----------------------------------------------------------------------------

        /// @{ ----------------------------------------------------------------------------
        /// This is used by range based for loop.
        /// See End() for implementation.
        /// 
        /// @note AtomEngine does not use end() becuase it does not
        ///       follow our naming standards.
        mpublic BoxedForwardIteratorT end() noexcept
        {
            return End();
        }

        mpublic const BoxedForwardIteratorT end() const noexcept
        {
            return End();
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
}