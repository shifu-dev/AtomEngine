#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/IConstIterable.hpp"

namespace Atom
{
    /// Base type implementing iterable functionality.
    /// 
    /// Types extending from this class will be able to be used in range based for loops.
    /// 
    /// @tparam ElementT Type of element this iterable iterates on.
    template <typename ElementT>
    interface IIterable:
        public virtual IConstIterable<ElementT>
    {
        using IConstIterableT = IConstIterable<ElementT>;
        using IForwardIteratorT = IForwardIterator<ElementT>;
        using IterateActionT = IInvokable<void(IForwardIteratorT&)>;

        using IConstIterableT::Iterate;

    public:
        virtual void Iterate(IterateActionT& action) = 0;
    };

    template <typename ElementT, typename ActionT>
    void ForEach(IIterable<ElementT>& iterable, ActionT&& action)
    {
        using IForwardIteratorT = IForwardIterator<ElementT>;
        using IterableInvokableMakerT = TInvokableMaker<void(IForwardIteratorT&)>;

        auto invokable = IterableInvokableMakerT::Make
        (
            [&action](IForwardIteratorT& it)
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