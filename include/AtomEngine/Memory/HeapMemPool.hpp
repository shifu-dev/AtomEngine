#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Memory/FastDynamicLinkedMemPool.hpp"
#include "AtomEngine/Memory/GlobalAllocation.hpp"

namespace Atom
{
    template<sizet BlockStackSize = 10>
    class HeapMemPool: public virtual FastDynamicLinkedMemPool<BlockStackSize>
    {
        using BaseT = FastDynamicLinkedMemPool<BlockStackSize>;

    /// ----------------------------------------------------------------------------
    public:
        HeapMemPool(sizet size) noexcept
        {
            _AddMemory(size);
        }

    /// ----------------------------------------------------------------------------
    protected:
        memptr _AllocateMemory(sizet size) override
        {
            return alloc(size);
        }

        void _DeallocateMemory(memptr mem, sizet size) override
        {
            return dealloc(mem, size);
        }

    /// ----------------------------------------------------------------------------
    protected:
        using BaseT::_AddMemory;
    };
}