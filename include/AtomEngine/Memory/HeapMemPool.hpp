#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Memory/LinkedMemPool.hpp"
#include "AtomEngine/Memory/GlobalAllocation.hpp"

namespace Atom
{
    template<sizet TBlockStackSize = 10>
    class HeapMemPool : public virtual FastDynamicLinkedMemPool<TBlockStackSize>
    {
        mprotected using BaseT = FastDynamicLinkedMemPool<TBlockStackSize>;
        mprotected using BaseT::mAddMemory;

        mpublic HeapMemPool(const sizet size) noexcept
        {
            mAddMemory(size);
        }

        mpublic virtual memptr mAllocateMemory(const sizet size) override
        {
            return alloc(size);
        }

        mpublic virtual void mDeallocateMemory(memptr mem, const sizet size) override
        {
            return dealloc(mem, size);
        }
    };
}