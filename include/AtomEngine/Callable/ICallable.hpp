#pragma once
#include "AtomEngine/Core.hpp"

namespace Atom
{
    template <typename ResultT, typename... ArgsT> interface ICallable;
    template <typename ResultT, typename... ArgsT>
    interface ICallable <ResultT(ArgsT...)>
    {
    public:
        ResultT operator () (ArgsT&&... args)
        {
            return Invoke(forward<ArgsT>(args)...);
        }

        virtual ResultT Invoke(ArgsT&&... args) = 0;
    };

    template <typename... ArgsT>
    using IPredicate = ICallable<bool(ArgsT...)>;

    template <typename... ArgsT>
    using IAction = ICallable<void(ArgsT...)>;
}