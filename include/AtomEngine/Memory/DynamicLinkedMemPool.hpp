#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Memory/LinkedMemPool.hpp"

namespace Atom
{
    class DynamicLinkedMemPool :
        public virtual LinkedMemPool,
        public virtual DynamicMemPool
    {
        mpublic virtual void Shrink() override;
        mpublic virtual void Reserve(const sizet size) override;
        mpublic virtual void ReserveMore(const sizet size) override;

        mprotected virtual memptr mAllocateMemory(const sizet count) abstract;
        mprotected virtual void mDeallocateMemory(memptr mem, const sizet count) abstract;

        /// @brief calls mAllocateMemory, and passes it to mAddMemory(mem, size, isRoot);
        mprotected blockptr mAddMemory(const sizet size, bool isRoot = true);
    };

    inline void DynamicLinkedMemPool::Shrink()
    {
        // TODO: implement
    }

    inline void DynamicLinkedMemPool::Reserve(const sizet size)
    {
        const sizet freeCount = FreeCount();
        if (size > freeCount)
        {
            ReserveMore(size - freeCount);
        }
    }

    inline void DynamicLinkedMemPool::ReserveMore(const sizet size)
    {
        memptr mem = mAllocateMemory(size);
        if (mem is nullptr)
        {
            // todo: throw exception
            // out of memory

            return;
        }

        blockptr block = mCreateBlock();
        block->mem = mem;
        block->size = size;
        block->isFree = true;
        block->isRoot = true;
        block->next = nullptr;
    }

    inline DynamicLinkedMemPool::blockptr DynamicLinkedMemPool::mAddMemory(const sizet size, bool isRoot)
    {
        if (size is 0) return nullptr;

        memptr mem = mAllocateMemory(size);
        if (mem is nullptr)
        {
            return nullptr;
        }

        return LinkedMemPool::mAddMemory(mem, size, isRoot);
    }
}