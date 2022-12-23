#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Memory/UniqueBox.hpp"
#include "AtomEngine/Callable/ICallable.hpp"

namespace Atom
{
    template <typename ResultT, typename... ArgsT> class CallableBox;
    template <typename ResultT, typename... ArgsT>
    class CallableBox<ResultT(ArgsT...)>: public TUniqueBox<ICallable<ResultT(ArgsT...)>, 50>
    {
        using ThisT = CallableBox<ResultT(ArgsT...)>;
        using BaseT = TUniqueBox<ICallable<ResultT(ArgsT...)>, 50>;
        using CallableT = ICallable<ResultT(ArgsT...)>;

    /// ----------------------------------------------------------------------------
    public:
        CallableBox() = default;

        CallableBox(const ThisT& other) = default;
        CallableBox(ThisT&& other) = default;

        ThisT& operator = (const ThisT& other) = default;
        ThisT& operator = (ThisT&& other) = default;

        ~CallableBox() = default;

        template <typename CallableImplT, EnableIf<!IsSubClass<ThisT, CallableImplT>> = 0>
        CallableBox(const CallableImplT& callable):
            BaseT(callable)
        {
            StaticAssertSubClass<CallableT, CallableImplT>();
        }

        template <typename CallableImplT, EnableIf<!IsSubClass<ThisT, CallableImplT>> = 0>
        CallableBox(CallableImplT&& callable):
            BaseT(move(callable))
        {
            StaticAssertSubClass<CallableT, CallableImplT>();
        }

        template <typename CallableImplT, EnableIf<!IsSubClass<ThisT, CallableImplT>> = 0>
        ThisT& operator = (const CallableImplT& callable)
        {
            StaticAssertSubClass<CallableT, CallableImplT>();
            BaseT::operator = (callable);

            return *this;
        }

        template <typename CallableImplT, EnableIf<!IsSubClass<ThisT, CallableImplT>> = 0>
        ThisT& operator = (CallableImplT&& callable)
        {
            StaticAssertSubClass<CallableT, CallableImplT>();
            BaseT::operator = (move(callable));

            return *this;
        }
    };
}