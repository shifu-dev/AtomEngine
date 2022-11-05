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

    public:

        template <typename TFunctor>
        void ForEachT(const TFunctor lref functor) const
        {
            ForEach(Callable<void(const ElementT lref)>::Create(functor));
        }

        template <typename TFunctor>
        void ForEachT(const TFunctor lref functor)
        {
            ForEach(Callable<void(ElementT lref)>::Create(functor));
        }

        virtual void ForEach(const Callable<void(const ElementT lref)> lref callback) const abstract;
        virtual void ForEach(const Callable<void(ElementT lref)> lref callback) abstract;

        ForwardIteratorPointerT Begin() noexcept
        {
            return Iterable_begin();
        }

        const ForwardIteratorPointerT Begin() const noexcept
        {
            return Iterable_begin();
        }

        ForwardIteratorPointerT End() noexcept
        {
            return Iterable_end();
        }

        const ForwardIteratorPointerT End() const noexcept
        {
            return Iterable_end();
        }

        ForwardIteratorPointerT begin() noexcept
        {
            return Iterable_begin();
        }

        const ForwardIteratorPointerT begin() const noexcept
        {
            return Iterable_begin();
        }

        ForwardIteratorPointerT end() noexcept
        {
            return Iterable_end();
        }

        const ForwardIteratorPointerT end() const noexcept
        {
            return Iterable_end();
        }

    protected:
        virtual ForwardIteratorPointerT Iterable_begin() noexcept abstract;
        virtual ForwardIteratorPointerT Iterable_end() noexcept abstract;

        virtual const ForwardIteratorPointerT Iterable_begin() const noexcept abstract;
        virtual const ForwardIteratorPointerT Iterable_end() const noexcept abstract;
    };
}