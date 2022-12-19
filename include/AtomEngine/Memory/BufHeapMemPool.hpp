#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Memory/HeapMemPool.hpp"

namespace Atom
{
    template<sizet StackSize, sizet BlockStackSize = 10>
    class BufHeapMemPool: public HeapMemPool<BlockStackSize>
    {
        using BaseT = HeapMemPool<BlockStackSize>;

    /// ----------------------------------------------------------------------------
    public:
        BufHeapMemPool() noexcept:
            BaseT(0)
        {
            _AddMemory(_stackMemory, StackSize);
        }

        BufHeapMemPool(sizet heapSize) noexcept:
            BaseT(0)
        {
            _AddMemory(_stackMemory, StackSize);
            _AddMemory(heapSize);
        }

    /// ----------------------------------------------------------------------------
    protected:
        using BaseT::_AddMemory;

    protected:
        byte _stackMemory[StackSize];
    };
}