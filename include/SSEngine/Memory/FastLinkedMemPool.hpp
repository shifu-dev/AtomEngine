#pragma once
#include "SSEngine/Core.hpp"
#include "SSEngine/Memory/LinkedMemPool.hpp"

namespace SSEngine
{
    constexpr sizet nsize = -1;

    template <sizet TBlockStackSize>
    class FastLinkedMemPool : public virtual LinkedMemPool
    {
        using BaseT = LinkedMemPool;
        static constexpr sizet BLOCK_STACK_COUNT = TBlockStackSize;

    public:
        FastLinkedMemPool() noexcept
        {
            mMaxReservedBlockCount = BLOCK_STACK_COUNT;
            mReserveMoreBlocks(BLOCK_STACK_COUNT);
        }

        virtual blockptr mAllocateBlocks(const sizet count) final override
        {
            if (mStackReservedFreeBlock isnot nsize)
            {
                blockptr block = lref mStackReservedBlocks[mStackReservedFreeBlock];

                // find next free block before hand
                mStackReservedBlocksUsage[mStackReservedFreeBlock] = true;
                mStackReservedFreeBlock = nsize;
                for (sizet i = mStackReservedFreeBlock; i < BLOCK_STACK_COUNT; i++)
                {
                    if (mStackReservedBlocksUsage[mStackReservedFreeBlock] isnot true)
                    {
                        mStackReservedFreeBlock = i;
                        break;
                    }
                }

                return block;
            }

            return BaseT::mAllocateBlocks(count);
        }

        virtual void mDeallocateBlock(blockptr block) final override
        {
            if (block > mStackReservedBlocks and block < mStackReservedBlocks + BLOCK_STACK_COUNT)
            {
                const sizet index = block - mStackReservedBlocks;
                mStackReservedBlocksUsage[index] = false;

                if (mStackReservedFreeBlock > index)
                {
                    mStackReservedFreeBlock = index;
                }

                return;
            }

            return BaseT::mDeallocateBlock(block);
        }

    protected:
        Block mStackReservedBlocks[BLOCK_STACK_COUNT];
        bool mStackReservedBlocksUsage[BLOCK_STACK_COUNT];
        sizet mStackReservedFreeBlock = 0;
    };

    template <sizet TBlockStackSize>
    class FastDynamicLinkedMemPool :
        public virtual FastLinkedMemPool<TBlockStackSize>,
        public virtual DynamicLinkedMemPool {};
}