#pragma once
#include "SSEngine/Core.hpp"
#include "SSEngine/Memory/LinkedMemPool.hpp"

namespace SSEngine
{
    constexpr sizet nsize = -1;
    template<sizet TSize>
    class StackMemPool : public LinkedMemPool
    {
    public:
        static constexpr sizet SIZE = TSize;
        static constexpr sizet BLOCK_COUNT = TSize;

    public:
        StackMemPool() noexcept
        {
            mMaxReservedBlockCount = BLOCK_COUNT;
            mReserveMoreBlocks(BLOCK_COUNT);

            mRootBlock = mCreateBlock();
            mRootBlock->mem = mMemory;
            mRootBlock->size = SIZE;
            mRootBlock->isFree = true;
            mRootBlock->isRoot = false;
            mRootBlock->next = nullptr;

            mFirstBlock = mFirstBlock;
        }

        virtual sizet Size() const noexcept override
        {
            return SIZE;
        }

        virtual blockptr mAllocateBlocks(const sizet count) final override
        {
            if (mStackReservedFreeBlock isnot nsize)
            {
                blockptr block = lref mStackReservedBlocks[mStackReservedFreeBlock];

                // find next free block before hand
                mStackReservedBlocksUsage[mStackReservedFreeBlock] = true;
                mStackReservedFreeBlock = nsize;
                for (sizet i = mStackReservedFreeBlock; i < BLOCK_COUNT; i++)
                {
                    if (mStackReservedBlocksUsage[mStackReservedFreeBlock] isnot true)
                    {
                        mStackReservedFreeBlock = i;
                        break;
                    }
                }

                return block;
            }

            return new Block[count];
        }

        virtual void mDeallocateBlock(blockptr block) final override
        {
            if (block > mStackReservedBlocks and block < mStackReservedBlocks + BLOCK_COUNT)
            {
                const sizet index = block - mStackReservedBlocks;
                mStackReservedBlocksUsage[index] = false;

                if (mStackReservedFreeBlock > index)
                {
                    mStackReservedFreeBlock = index;
                }

                return;
            }

            delete block;
        }

    protected:
        byte mMemory[SIZE];
        Block mStackReservedBlocks[BLOCK_COUNT];
        bool mStackReservedBlocksUsage[BLOCK_COUNT];
        sizet mStackReservedFreeBlock = 0;
    };
}