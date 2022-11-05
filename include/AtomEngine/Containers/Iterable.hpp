#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Callable/Callable.hpp"
#include "AtomEngine/Memory.hpp"
#include "AtomEngine/Containers/IteratorPointer.hpp"

namespace Atom
{
    template <typename TElement>
    class ContainerDefination;

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
        using ForwardIteratorPointerT = ForwardIteratorPointer<ElementT>;

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

        mpublic ForwardIteratorPointerT Begin() noexcept
        {
            return Iterable_begin();
        }

        mpublic const ForwardIteratorPointerT Begin() const noexcept
        {
            return Iterable_begin();
        }

        mpublic ForwardIteratorPointerT End() noexcept
        {
            return Iterable_end();
        }

        mpublic const ForwardIteratorPointerT End() const noexcept
        {
            return Iterable_end();
        }

        mpublic ForwardIteratorPointerT begin() noexcept
        {
            return Iterable_begin();
        }

        mpublic const ForwardIteratorPointerT begin() const noexcept
        {
            return Iterable_begin();
        }

        mpublic ForwardIteratorPointerT end() noexcept
        {
            return Iterable_end();
        }

        mpublic const ForwardIteratorPointerT end() const noexcept
        {
            return Iterable_end();
        }

        mprotected virtual ForwardIteratorPointerT Iterable_begin() noexcept abstract;
        mprotected virtual ForwardIteratorPointerT Iterable_end() noexcept abstract;

        mprotected virtual const ForwardIteratorPointerT Iterable_begin() const noexcept abstract;
        mprotected virtual const ForwardIteratorPointerT Iterable_end() const noexcept abstract;
    };
}