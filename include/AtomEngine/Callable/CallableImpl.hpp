#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Callable/ICallable.hpp"

namespace Atom
{
    template <typename FunctorT, typename ResultT, typename... ArgsT> class CallableImpl;
    template <typename FunctorT, typename ResultT, typename... ArgsT>
    class CallableImpl <ResultT(ArgsT...), FunctorT>:
        public virtual ICallable<ResultT(ArgsT...)>
    {
    public:
        CallableImpl(const FunctorT& func):
            func(func) { }

    /// ----------------------------------------------------------------------------
    /// ICallable
    public:
        ResultT Invoke(ArgsT&&... args) override final
        {
            return func(forward<ArgsT>(args)...);
        }

    /// ----------------------------------------------------------------------------
    public:
        FunctorT func;
    };

    template <typename ResultT, typename... ArgsT> class TCallableMaker;
    template <typename ResultT, typename... ArgsT>
    class TCallableMaker <ResultT(ArgsT...)>
    {
        template <typename FunctorT>
        using TCallableImplType = CallableImpl<ResultT(ArgsT...), FunctorT>;

    private:
        TCallableMaker() noexcept = default;

    public:
        template <typename FunctorT>
        static TCallableImplType<FunctorT> Make(FunctorT&& functor) noexcept
        {
            return TCallableImplType<FunctorT>(forward<FunctorT>(functor));
        }
    };
}