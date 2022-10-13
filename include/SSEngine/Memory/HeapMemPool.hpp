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
        sizet mSize;
    };

    HeapMemPool::HeapMemPool(const sizet size) noexcept
    {
        void ptr heapMem = malloc(size);

        mFirstBlock = mAllocateBlocks(1);
        mFirstBlock->mem = heapMem;
        mFirstBlock->size = size;
        mFirstBlock->isFree = true;
        mFirstBlock->next = nullptr;

        mFreeBlock = mFirstBlock;
    }

    sizet HeapMemPool::Size() const noexcept
    {
        return mSize;
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