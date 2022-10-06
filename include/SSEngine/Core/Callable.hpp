#pragma once
#include "SSEngine/Core.hpp"

namespace SSEngine
{
    template <typename TFunc, typename TResult, typename... TArgs>
    class CallableFunctor;

    template <typename TResult, typename... TArgs> class Callable;
    template <typename TResult, typename... TArgs>
    class Callable <TResult(TArgs...)>
    {
    public:
        template <typename TFunc>
        static CallableFunctor<TFunc, TResult, TArgs...> Create(const TFunc lref func)
        {
            return CallableFunctor<TFunc, TResult, TArgs...>(func);
        }

    public:
        virtual TResult operator () (TArgs rref ... args) const abstract;
    };

    template <typename TFunc, typename TResult, typename... TArgs>
    class CallableFunctor : public Callable<TResult(TArgs...)>
    {
    public:
        CallableFunctor(const TFunc lref func) : func(func) { }

    public:
        virtual TResult operator () (TArgs rref ... args) const override
        {
            return func(forward<TArgs>(args)...);
        }

    public:
        const TFunc func;
    };
}