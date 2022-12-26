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
        using ForwardIteratorBoxT = ForwardIteratorBox<ElementT>;
        using LoopActionT = ILoopAction<ElementT&>;

        using IConstIterableT::ForEach;

    public:
        virtual void ForEach(LoopActionT& action) = 0;
    };

    template <typename ElementT, typename ActionT>
    void ForEach(IIterable<ElementT>& iterable, ActionT&& action)
    {
        using InvokableMakerT = TInvokableMaker<LoopCommand(ElementT&)>;

        auto invokable = InvokableMakerT::Make(forward<ActionT>(action));
        iterable.ForEach(invokable);
    }
}