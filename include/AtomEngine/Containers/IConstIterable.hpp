#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Invokable/IInvokable.hpp"
#include "AtomEngine/Invokable/InvokableImpl.hpp"
#include "AtomEngine/Containers/ForwardIteratorBox.hpp"

namespace Atom
{
    enum LoopCommand
    {
        CONTINUE_LOOP,
        BREAK_LOOP
    };

    template <typename... ArgsT>
    using ILoopAction = IInvokable<LoopCommand(ArgsT...)>;

    template <typename ElementT>
    interface IConstIterable
    {
        using ConstElementT = const ElementT;
        using ConstForwardIteratorBoxT = ConstForwardIteratorBox<ElementT>;
        using ConstLoopActionT = ILoopAction<const ElementT&>;

    public:
        virtual void ForEach(ConstLoopActionT& action) const = 0;
    };

    template <typename ElementT, typename ActionT>
    void ForEach(const IConstIterable<ElementT>& iterable, ActionT&& action)
    {
        using InvokableMakerT = TInvokableMaker<LoopCommand(const ElementT&)>;

        auto invokable = InvokableMakerT::Make(forward<ActionT>(action));
        iterable.ForEach(invokable);
    }
}