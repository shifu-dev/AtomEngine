#pragma once
#include "AtomEngine/Core.hpp"

namespace Atom
{
    template <typename TFunctor, typename TResult, typename... TArgs>
    class CallableFunctor;

    template <typename TResult, typename... TArgs> class ICallable;
    template <typename TResult, typename... TArgs>
    class ICallable <TResult(TArgs...)>
    {
        using ThisT = ICallable<TResult(TArgs...)>;

        mpublic template <typename TFunctor>
            static CallableFunctor<TFunctor, TResult, TArgs...> Create(const TFunctor ref func)
        {
            return CallableFunctor<TFunctor, TResult, TArgs...>(func);
        }

        mpublic TResult operator () (TArgs rref ... args) const
        {
            return Invoke(forward<TArgs>(args)...);
        }

        mpublic virtual TResult Invoke(TArgs rref ... args) const abstract;
    };

    template <typename... TArgs>
    using IPredicate = ICallable<bool(TArgs...)>;

    template <typename... TArgs>
    using IAction = ICallable<void(TArgs...)>;

    template <typename TFunctor, typename TResult, typename... TArgs>
    class CallableFunctor : public ICallable<TResult(TArgs...)>
    {
        mpublic CallableFunctor(const TFunctor ref func) : func(func) { }

        mpublic virtual TResult Invoke(TArgs rref ... args) const override
        {
            return func(forward<TArgs>(args)...);
        }

        mpublic TFunctor func;
    };
}