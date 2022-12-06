#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Memory/LinkedMemPool.hpp"

namespace Atom
{
    constexpr sizet nsize = -1;

    template <sizet TBlockStackSize>
    class FastLinkedMemPool : public virtual LinkedMemPool
    {
        using BaseT = LinkedMemPool;
        static constexpr sizet BLOCK_STACK_COUNT = TBlockStackSize;

        mpublic FastLinkedMemPool() noexcept
        {
            mMaxReservedBlockCount = BLOCK_STACK_COUNT;
            mReserveMoreBlocks(BLOCK_STACK_COUNT);
        }

        mpublic virtual blockptr mAllocateBlocks(const sizet count) final
        {
            if (mStackReservedFreeBlock isnot nsize)
            {
                blockptr block = ref mStackReservedBlocks[mStackReservedFreeBlock];

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

        mpublic virtual void mDeallocateBlock(blockptr block) final
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

        mprotected Block mStackReservedBlocks[BLOCK_STACK_COUNT];
        mprotected bool mStackReservedBlocksUsage[BLOCK_STACK_COUNT];
        mprotected sizet mStackReservedFreeBlock = 0;
    };
}