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

        virtual void Resize(const sizet size) override;

        virtual void Reserve(const sizet size) override;

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

    void HeapMemPool::Resize(const sizet size)
    {
        // todo implement this
    }

    void HeapMemPool::Reserve(const sizet size)
    {
        const sizet freeCount = FreeCount();
        if (freeCount < size)
        {
            Resize(Size() - freeCount + size);
        }
    }
}