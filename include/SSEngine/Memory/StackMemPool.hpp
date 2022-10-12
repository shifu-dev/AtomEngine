#pragma once
#include "SSEngine/Core.hpp"
#include "SSEngine/Memory/LinkedMemPool.hpp"

namespace SSEngine
{
    template<sizet TSize>
    class StackMemPool : public LinkedMemPool
    {
        using LinkedMemPool::mFirstBlock;
        using LinkedMemPool::mFreeBlock;

    public:
        static constexpr sizet SIZE = TSize;

    public:
        StackMemPool() noexcept
        {
            mFirstBlock = mAllocateBlocks(1);
            mFirstBlock->mem = mMemory;
            mFirstBlock->size = SIZE;
            mFirstBlock->isFree = true;
            mFirstBlock->next = nullptr;

            mFreeBlock = mFirstBlock;
        }

        virtual sizet Size() const noexcept override
        {
            return SIZE;
        }

    protected:
        byte mMemory[Size];
    };
}