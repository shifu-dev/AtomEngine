#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Invokable/IInvokable.hpp"
#include "AtomEngine/Invokable/InvokableImpl.hpp"
#include "AtomEngine/Containers/IForwardIterator.hpp"

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
        using IConstForwardIteratorT = IConstForwardIterator<ElementT>;
        using ConstIterateActionT = IInvokable<void(const IConstForwardIteratorT&)>;

    public:
        virtual void Iterate(ConstIterateActionT& action) const = 0;
    };

    template <typename ElementT, typename ActionT>
    void ForEach(const IConstIterable<ElementT>& iterable, ActionT&& action)
    {
        using IConstForwardIteratorT = IConstForwardIterator<ElementT>;
        using IterableInvokableMakerT = TInvokableMaker<void(const IConstForwardIteratorT&)>;

        auto invokable = IterableInvokableMakerT::Make
        (
            [&action](const IConstForwardIteratorT& it)
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