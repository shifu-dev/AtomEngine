#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Memory/IDynamicMemPool.hpp"
#include "AtomEngine/Memory/LinkedMemPool.hpp"

namespace Atom
{
    /// @todo Fix LinkedMemPool virtual inheritance
    class DynamicLinkedMemPool: public virtual LinkedMemPool,
        public virtual IDynamicMemPool
    {
    /// ----------------------------------------------------------------------------
    public:
        void Shrink() final
        {
            // TODO: implement
        }

        void Reserve(sizet size) final
        {
            sizet freeCount = FreeCount();
            if (size > freeCount)
            {
                ReserveMore(size - freeCount);
            }
        }

        void ReserveMore(sizet size) final
        {
            memptr mem = _AllocateMemory(size);
            if (mem == nullptr)
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

    /// ----------------------------------------------------------------------------
    protected:
        /// @note Calls _AllocateMemory, and passes it to _AddMemory(mem, size, isRoot);
        blockptr _AddMemory(sizet size, bool isRoot = true)
        {
            if (size == 0) return nullptr;

            memptr mem = _AllocateMemory(size);
            if (mem == nullptr)
            {
                return nullptr;
            }

            return LinkedMemPool::_AddMemory(mem, size, isRoot);
        }

        virtual memptr _AllocateMemory(sizet count) abstract;
        virtual void _DeallocateMemory(memptr mem, sizet count) abstract;
    };
}