#pragma once
#include "SSEngine/Core.hpp"
#include "SSEngine/Core/Callable.hpp"
#include "SSEngine/Memory.hpp"
#include "SSEngine/Collections/IteratorPointer.hpp"

namespace SSEngine
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
        using ContatinerDefinationT = ContainerDefination<TElement>;
        using SizeT = typename ContatinerDefinationT::SizeT;
        using ElementT = typename ContatinerDefinationT::ElementT;
        using ForwardIteratorPointerT = typename ContatinerDefinationT::ForwardIteratorPointerT;

    public:
        using SizeType = SizeT;
        using ElementType = ElementT;

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

    /// @brief Iterable helper class
    /// @tparam TIterator 
    template <typename TIterator>
    class IteratorIterable : public virtual Iterable<typename TIterator::ElementType>
    {
        using TElement = typename TIterator::ElementType;
        using ContatinerDefinationT = ContainerDefination<TElement>;
        using ForwardIteratorT = typename ContatinerDefinationT::ForwardIteratorT;
        using ForwardIteratorPointerT = typename ContatinerDefinationT::ForwardIteratorPointerT;
        using IteratorType = TIterator;

    public:
        virtual IteratorType Begin() noexcept abstract;
        virtual const IteratorType Begin() const noexcept abstract;

        virtual IteratorType End() noexcept abstract;
        virtual const IteratorType End() const noexcept abstract;

        IteratorType begin() noexcept { return Begin(); }
        const IteratorType begin() const noexcept { return Begin(); }

        IteratorType end() noexcept { return End(); }
        const IteratorType end() const noexcept { return End(); }

    protected:
        virtual const ForwardIteratorPointerT Iterable_begin() const noexcept override
        {
            return ForwardIteratorPointerT(Begin());
        }

        virtual ForwardIteratorPointerT Iterable_begin() noexcept override
        {
            return ForwardIteratorPointerT(Begin());
        }

        virtual const ForwardIteratorPointerT Iterable_end() const noexcept override
        {
            return ForwardIteratorPointerT(End());
        }

        virtual ForwardIteratorPointerT Iterable_end() noexcept override
        {
            return ForwardIteratorPointerT(End());
        }
    };
}

template <typename TElement>
using SSIterable = SSEngine::Iterable<TElement>;