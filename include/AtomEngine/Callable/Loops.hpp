#pragma once
#include "AtomEngine/Callable/ICallable.hpp"

namespace Atom
{
    enum LoopCommands
    {
        BREAK_LOOP,
        CONTINUE_LOOP
    };

    template <typename... ArgsT>
    using ILoopAction = ICallable<LoopCommands(ArgsT...)>;
}