#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Memory/HeapMemPool.hpp"

namespace Atom
{
    template<sizet TStackSize, sizet TBlockStackSize = 10>
    class BufHeapMemPool : public HeapMemPool<TBlockStackSize>
    {
        using BaseT = HeapMemPool<TBlockStackSize>;
        using LinkedMemPool::mAddMemory;
        using BaseT::mAddMemory;

        static constexpr sizet SIZE = TStackSize;

        mpublic BufHeapMemPool() noexcept : BaseT(0)
        {
            mAddMemory(mStackMemory, SIZE);
        }

        mpublic BufHeapMemPool(const sizet heapSize) noexcept : BaseT(0)
        {
            mAddMemory(mStackMemory, SIZE);
            mAddMemory(heapSize);
        }

        mprotected byte mStackMemory[SIZE];
    };
}