#pragma once
#include "SSEngine/Core.hpp"
#include "SSEngine/Memory/LinkedMemPool.hpp"
#include "SSEngine/Memory/GlobalAllocation.hpp"

namespace SSEngine
{
    template<sizet TBlockStackSize = 10>
    class HeapMemPool : public virtual FastDynamicLinkedMemPool<TBlockStackSize>
    {
    protected:
        using BaseT = FastDynamicLinkedMemPool<TBlockStackSize>;
        using BaseT::mAddMemory;

    public:
        HeapMemPool(const sizet size) noexcept
        {
            mAddMemory(size);
        }

        virtual memptr mAllocateMemory(const sizet size) override
        {
            return alloc(size);
        }

        virtual void mDeallocateMemory(memptr mem, const sizet size) override
        {
            return dealloc(mem, size);
        }
    };
}