#pragma once
#include "AtomEngine/Core.hpp"

namespace Atom
{
    template <typename TFunctor, typename TResult, typename... TArgs>
    class CallableFunctor;

    template <typename TResult, typename... TArgs> class Callable;
    template <typename TResult, typename... TArgs>
    class Callable <TResult(TArgs...)>
    {
        using ThisT = Callable<TResult(TArgs...)>;

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
    using Predicate = Callable<bool(TArgs...)>;

    template <typename... TArgs>
    using Action = Callable<void(TArgs...)>;

    template <typename TFunctor, typename TResult, typename... TArgs>
    class CallableFunctor : public Callable<TResult(TArgs...)>
    {
        mpublic CallableFunctor(const TFunctor ref func) : func(func) { }

        mpublic virtual TResult Invoke(TArgs rref ... args) const override
        {
            return func(forward<TArgs>(args)...);
        }

        mpublic TFunctor func;
    };
}