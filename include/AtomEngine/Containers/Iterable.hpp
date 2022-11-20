#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Callable/Callable.hpp"
#include "AtomEngine/Memory.hpp"
#include "AtomEngine/Containers/BoxedForwardIterator.hpp"

namespace Atom
{
    /// @brief base abstract class to implement basic iterable functionality
    /// just by implementing from this class, 
    /// extended class will be able to be used in range based for loop
    /// and funtions expecting an iterable type
    ///
    /// @tparam TElement type of value hold by this iterable
    template <typename TElement>
    class Iterable
    {
        using ElementT = TElement;
        using BoxedForwardIteratorT = BoxedForwardIterator<ElementT>;

        mpublic template <typename TFunctor>
            void ForEachT(const TFunctor ref functor) const
        {
            ForEach(Callable<void(const ElementT ref)>::Create(functor));
        }

        mpublic template <typename TFunctor>
            void ForEachT(const TFunctor ref functor)
        {
            ForEach(Callable<void(ElementT ref)>::Create(functor));
        }

        mpublic virtual void ForEach(const Callable<void(const ElementT ref)> ref callback) const abstract;
        mpublic virtual void ForEach(const Callable<void(ElementT ref)> ref callback) abstract;

        mpublic BoxedForwardIteratorT Begin() noexcept
        {
            return Iterable_begin();
        }

        mpublic const BoxedForwardIteratorT Begin() const noexcept
        {
            return Iterable_begin();
        }

        mpublic BoxedForwardIteratorT End() noexcept
        {
            return Iterable_end();
        }

        mpublic const BoxedForwardIteratorT End() const noexcept
        {
            return Iterable_end();
        }

        mpublic BoxedForwardIteratorT begin() noexcept
        {
            return Iterable_begin();
        }

        mpublic const BoxedForwardIteratorT begin() const noexcept
        {
            return Iterable_begin();
        }

        mpublic BoxedForwardIteratorT end() noexcept
        {
            return Iterable_end();
        }

        mpublic const BoxedForwardIteratorT end() const noexcept
        {
            return Iterable_end();
        }

        mprotected virtual BoxedForwardIteratorT Iterable_begin() noexcept abstract;
        mprotected virtual BoxedForwardIteratorT Iterable_end() noexcept abstract;

        mprotected virtual const BoxedForwardIteratorT Iterable_begin() const noexcept abstract;
        mprotected virtual const BoxedForwardIteratorT Iterable_end() const noexcept abstract;
    };
}