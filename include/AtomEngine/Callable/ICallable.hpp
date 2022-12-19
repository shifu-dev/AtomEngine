#pragma once
#include "AtomEngine/Core.hpp"

namespace Atom
{
    template <typename FunctorT, typename ResultT, typename... ArgsT>
    class CallableFunctor;

    template <typename ResultT, typename... ArgsT> class ICallable;
    template <typename ResultT, typename... ArgsT>
    class ICallable <ResultT(ArgsT...)>
    {
    /// ----------------------------------------------------------------------------
    public:
        template <typename FunctorT>
        static CallableFunctor<FunctorT, ResultT, ArgsT...> Create(const FunctorT& func)
        {
            return CallableFunctor<FunctorT, ResultT, ArgsT...>(func);
        }

    /// ----------------------------------------------------------------------------
    public:
        ResultT operator () (ArgsT && ... args) const
        {
            return Invoke(forward<ArgsT>(args)...);
        }

        virtual ResultT Invoke(ArgsT && ... args) const abstract;
    };

    template <typename... ArgsT>
    using IPredicate = ICallable<bool(ArgsT...)>;

    template <typename... ArgsT>
    using IAction = ICallable<void(ArgsT...)>;

    template <typename FunctorT, typename ResultT, typename... ArgsT>
    class CallableFunctor: public ICallable<ResultT(ArgsT...)>
    {
    /// ----------------------------------------------------------------------------
    public:
        CallableFunctor(const FunctorT& func): func(func) { }

        ResultT Invoke(ArgsT && ... args) const final
        {
            return func(forward<ArgsT>(args)...);
        }

    /// ----------------------------------------------------------------------------
    public:
        FunctorT func;
    };
}