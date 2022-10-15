#pragma once
#include "SSEngine/Core.hpp"
#include "SSEngine/Memory/HeapMemPool.hpp"

namespace SSEngine
{
    template<sizet TStackSize, sizet TBlockStackSize = 10>
    class BufHeapMemPool : public HeapMemPool<TBlockStackSize>
    {
        using BaseT = HeapMemPool<TBlockStackSize>;
        using LinkedMemPool::mAddMemory;
        using BaseT::mAddMemory;

        static constexpr sizet SIZE = TStackSize;

    public:
        BufHeapMemPool() noexcept : BaseT(0)
        {
            mAddMemory(mStackMemory, SIZE);
        }

        BufHeapMemPool(const sizet heapSize) noexcept : BaseT(0)
        {
            mAddMemory(mStackMemory, SIZE);
            mAddMemory(heapSize);
        }

    protected:
        byte mStackMemory[SIZE];
    };
}