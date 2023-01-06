#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Invokable/IInvokable.hpp"
#include "AtomEngine/Invokable/InvokableImpl.hpp"
#include "AtomEngine/Containers/IIterator.hpp"

namespace Atom
{
    enum LoopCommand
    {
        CONTINUE_LOOP,
        BREAK_LOOP
    };

    template <typename ElementT>
    interface IConstIterable
    {
        using IConstIteratorT = IConstIterator<ElementT>;
        using ConstIterateActionT = IInvokable<void(const IConstIteratorT&)>;

    public:
        virtual void Iterate(ConstIterateActionT& action) const = 0;
    };

    template <typename ElementT, typename ActionT>
    void ForEach(const IConstIterable<ElementT>& iterable, ActionT&& action)
    {
        using IConstIteratorT = IConstIterator<ElementT>;
        using IterableInvokableMakerT = TInvokableMaker<void(const IConstIteratorT&)>;

        auto invokable = IterableInvokableMakerT::Make
        (
            [&action](const IConstIteratorT& it)
            {
                while (it.IsEnd() != false)
                {
                    LoopCommand cmd = action(it.Value());
                    if (cmd == BREAK_LOOP) break;

                    it.MoveFwd();
                }
            }
        );

        iterable.Iterate(invokable);
    }
}