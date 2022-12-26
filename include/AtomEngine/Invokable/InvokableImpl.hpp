#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Invokable/IInvokable.hpp"

namespace Atom
{
    template <typename FunctorT, typename ResultT, typename... ArgsT> class InvokableImpl;
    template <typename FunctorT, typename ResultT, typename... ArgsT>
    class InvokableImpl <ResultT(ArgsT...), FunctorT>:
        public virtual IInvokable<ResultT(ArgsT...)>
    {
    public:
        InvokableImpl(const FunctorT& func):
            func(func) { }

    /// ----------------------------------------------------------------------------
    /// IInvokable
    public:
        ResultT Invoke(ArgsT&&... args) override final
        {
            return func(forward<ArgsT>(args)...);
        }

    /// ----------------------------------------------------------------------------
    public:
        FunctorT func;
    };

    template <typename ResultT, typename... ArgsT> class TInvokableMaker;
    template <typename ResultT, typename... ArgsT>
    class TInvokableMaker <ResultT(ArgsT...)>
    {
        template <typename FunctorT>
        using TInvokableImplType = InvokableImpl<ResultT(ArgsT...), FunctorT>;

    private:
        TInvokableMaker() noexcept = default;

    public:
        template <typename FunctorT>
        static TInvokableImplType<FunctorT> Make(FunctorT&& functor) noexcept
        {
            return TInvokableImplType<FunctorT>(forward<FunctorT>(functor));
        }
    };
}