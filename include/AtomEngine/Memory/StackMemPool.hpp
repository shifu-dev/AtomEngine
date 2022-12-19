#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Memory/FastLinkedMemPool.hpp"

namespace Atom
{
    template<sizet StackSize, sizet TBlockStackSize = (StackSize / 2)>
    class StackMemPool: public virtual FastLinkedMemPool<TBlockStackSize>
    {
        using BaseT = FastLinkedMemPool<TBlockStackSize>;

    public:
        StackMemPool() noexcept
        {
            _AddMemory(_stackMemory, StackSize);
        }

    protected:
        using BaseT::_AddMemory;

    protected:
        byte _stackMemory[StackSize];
    };
}