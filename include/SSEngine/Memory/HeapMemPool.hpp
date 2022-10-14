#pragma once
#include "SSEngine/Core.hpp"
#include "SSEngine/Memory/LinkedMemPool.hpp"

namespace SSEngine
{
    template<sizet TBlockStackSize = 10>
    class HeapMemPool : public virtual FastDynamicLinkedMemPool<TBlockStackSize>
    {
        using BaseT = FastLinkedMemPool<TBlockStackSize>;
        using BaseT::mRootBlock;
        using BaseT::mFirstBlock;
        using BaseT::mCreateBlock;

    public:
        HeapMemPool(const sizet size) noexcept
        {
            mRootBlock = mCreateBlock();
            mRootBlock->mem = malloc(size);
            mRootBlock->size = size;
            mRootBlock->isFree = true;
            mRootBlock->isRoot = true;
            mRootBlock->next = nullptr;

            mFirstBlock = mFirstBlock;

            mMemorySize = size;
        }

        virtual sizet Size() const noexcept final override
        {
            return mMemorySize;
        }

        virtual memptr mAllocateMemory(const sizet size) override
        {
            return new byte[size];
        }

        virtual void mDeallocateMemory(memptr mem, const sizet size) override
        {
            delete[](byte ptr)mem;
        }

    protected:
        sizet mMemorySize;
    };
}