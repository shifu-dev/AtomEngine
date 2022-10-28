#pragma once
#include "SSEngine/Core.hpp"

namespace SSEngine
{
    template <typename TFunctor, typename TResult, typename... TArgs>
    class CallableFunctor;

    template <typename TResult, typename... TArgs> class Callable;
    template <typename TResult, typename... TArgs>
    class Callable <TResult(TArgs...)>
    {
        using ThisT = Callable<TResult(TArgs...)>;

    public:
        template <typename TFunctor>
        static CallableFunctor<TFunctor, TResult, TArgs...> Create(const TFunctor lref func)
        {
            return CallableFunctor<TFunctor, TResult, TArgs...>(func);
        }

    public:
        TResult operator () (TArgs rref ... args) const
        {
            return Invoke(forward<TArgs>(args)...);
        }

        virtual TResult Invoke(TArgs rref ... args) const abstract;
    };

    template <typename... TArgs>
    using Predicate = Callable<bool(TArgs...)>;

    template <typename... TArgs>
    using Action = Callable<void(TArgs...)>;

    template <typename TFunctor, typename TResult, typename... TArgs>
    class CallableFunctor : public Callable<TResult(TArgs...)>
    {
    public:
        CallableFunctor(const TFunctor lref func) : func(func) { }

    public:
        virtual TResult Invoke(TArgs rref ... args) const override
        {
            return func(forward<TArgs>(args)...);
        }

    public:
        const TFunctor func;
    };
}