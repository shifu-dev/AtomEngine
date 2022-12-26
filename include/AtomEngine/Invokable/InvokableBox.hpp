#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Memory/UniqueBox.hpp"
#include "AtomEngine/Invokable/IInvokable.hpp"

namespace Atom
{
    template <typename ResultT, typename... ArgsT> class InvokableBox;
    template <typename ResultT, typename... ArgsT>
    class InvokableBox<ResultT(ArgsT...)>: public TUniqueBox<IInvokable<ResultT(ArgsT...)>, 50>
    {
        using ThisT = InvokableBox<ResultT(ArgsT...)>;
        using BaseT = TUniqueBox<IInvokable<ResultT(ArgsT...)>, 50>;
        using InvokableT = IInvokable<ResultT(ArgsT...)>;

    /// ----------------------------------------------------------------------------
    public:
        InvokableBox() = default;

        InvokableBox(const ThisT& other) = default;
        InvokableBox(ThisT&& other) = default;

        ThisT& operator = (const ThisT& other) = default;
        ThisT& operator = (ThisT&& other) = default;

        ~InvokableBox() = default;

        template <typename InvokableImplT, EnableIf<!IsSubClass<ThisT, InvokableImplT>> = 0>
        InvokableBox(const InvokableImplT& callable):
            BaseT(callable)
        {
            StaticAssertSubClass<InvokableT, InvokableImplT>();
        }

        template <typename InvokableImplT, EnableIf<!IsSubClass<ThisT, InvokableImplT>> = 0>
        InvokableBox(InvokableImplT&& callable):
            BaseT(move(callable))
        {
            StaticAssertSubClass<InvokableT, InvokableImplT>();
        }

        template <typename InvokableImplT, EnableIf<!IsSubClass<ThisT, InvokableImplT>> = 0>
        ThisT& operator = (const InvokableImplT& callable)
        {
            StaticAssertSubClass<InvokableT, InvokableImplT>();
            BaseT::operator = (callable);

            return *this;
        }

        template <typename InvokableImplT, EnableIf<!IsSubClass<ThisT, InvokableImplT>> = 0>
        ThisT& operator = (InvokableImplT&& callable)
        {
            StaticAssertSubClass<InvokableT, InvokableImplT>();
            BaseT::operator = (move(callable));

            return *this;
        }
    };
}