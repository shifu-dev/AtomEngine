#pragma once
#include "SSEngine/Core.hpp"
#include "SSEngine/Memory/FastLinkedMemPool.hpp"

namespace SSEngine
{
    template<sizet TSize, sizet TBlockStackSize = (TSize / 2)>
    class StackMemPool : public virtual FastLinkedMemPool<TBlockStackSize>
    {
        using BaseT = FastLinkedMemPool<TBlockStackSize>;
        using BaseT::mRootBlock;
        using BaseT::mFirstBlock;
        using BaseT::mCreateBlock;

    public:
        static constexpr sizet SIZE = TSize;

    public:
        StackMemPool() noexcept
        {
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

    protected:
        byte mMemory[SIZE];
    };
}