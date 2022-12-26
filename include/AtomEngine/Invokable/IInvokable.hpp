#pragma once
#include "AtomEngine/Core.hpp"

namespace Atom
{
    template <typename ResultT, typename... ArgsT> interface IInvokable;
    template <typename ResultT, typename... ArgsT>
    interface IInvokable <ResultT(ArgsT...)>
    {
    public:
        ResultT operator () (ArgsT&&... args)
        {
            return Invoke(forward<ArgsT>(args)...);
        }

        virtual ResultT Invoke(ArgsT&&... args) = 0;
    };

    template <typename... ArgsT>
    using IPredicate = IInvokable<bool(ArgsT...)>;

    template <typename... ArgsT>
    using IAction = IInvokable<void(ArgsT...)>;
}