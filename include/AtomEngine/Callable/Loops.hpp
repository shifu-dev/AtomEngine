#pragma once
#include "AtomEngine/Callable/ICallable.hpp"

namespace Atom
{
    enum LoopCommands
    {
        BREAK_LOOP,
        CONTINUE_LOOP
    };

    template <typename... TArgs>
    using ILoopAction = ICallable<LoopCommands(TArgs...)>;
}