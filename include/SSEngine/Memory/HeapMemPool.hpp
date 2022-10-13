#pragma once
#include "SSEngine/Core.hpp"
#include "SSEngine/Memory/LinkedMemPool.hpp"

namespace SSEngine
{
    class HeapMemPool : public virtual DynamicLinkedMemPool
    {
    public:
        HeapMemPool(const sizet size) noexcept;

        virtual sizet Size() const noexcept final override;

        virtual memptr mAllocateMemory(const sizet size) override;
        virtual void mDeallocateMemory(memptr mem, const sizet size) override;

    protected:
        sizet mMemorySize;
    };

    HeapMemPool::HeapMemPool(const sizet size) noexcept
    {
        mReserveMoreBlocks(size);

        mRootBlock = mCreateBlock();
        mRootBlock->mem = malloc(size);
        mRootBlock->size = size;
        mRootBlock->isFree = true;
        mRootBlock->next = nullptr;

        mFirstBlock = mFirstBlock;

        mMemorySize = size;
    }

    sizet HeapMemPool::Size() const noexcept
    {
        return mMemorySize;
    }

    memptr HeapMemPool::mAllocateMemory(const sizet size)
    {
        return new byte[size];
    }

    void HeapMemPool::mDeallocateMemory(memptr mem, const sizet size)
    {
        delete[](byte ptr)mem;
    }
}