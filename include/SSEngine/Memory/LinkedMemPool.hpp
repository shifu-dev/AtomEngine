#pragma once
#include "SSEngine/Core.hpp"
#include "SSEngine/Memory/MemPool.hpp"

namespace SSEngine
{
    class LinkedMemPool : public MemPool
    {
    protected:
        struct Block
        {
            memptr mem;
            sizet size;
            bool isFree = true;

            Block ptr next;
        };

        using blockptr = Block ptr;

    public:
        LinkedMemPool() noexcept;

    public:
        virtual memptr AllocateRaw(const sizet size, bool clear = true) override;
        virtual void DeallocateRaw(memptr src, const sizet size) override;

        /// @return amount of memory in use from the pool
        virtual sizet UsedCount() const noexcept;

        /// @return amount of free memory in the pool
        virtual sizet FreeCount() const noexcept;

        /// @brief checks if block of enough size is available for allocation
        /// @param size size of block the check for
        /// @return true if block exists, false otherwise
        virtual bool HasBlockFor(const sizet size) const noexcept;

        /// @brief checks if block of [sizeof(Type) * count] is available
        /// @note looks for contiguous block of memory
        /// @tparam Type type of object to check blocks for
        /// @param count count of objects
        /// @return true if block exists, false otherwise
        template <typename Type>
        bool HasBlockFor(const sizet count) const noexcept;

    protected:

        /// @brief finds the first block for the specified size
        /// @param size size to search block for
        /// @return ptr to block, null if not found
        virtual blockptr mFindBlock(const sizet size) const noexcept;

        /// @brief finds block which contains given memory address
        /// @param ptr memory address to search block for
        /// @return ptr to block, null if not found
        virtual blockptr mFindBlockFor(const memptr mem) const noexcept;

        /// @brief divides the block into two blocks of [size] and [block->size - size]
        /// @param block ptr to block to divide
        /// @param size size of the first block
        /// @return true if sucessfull, false otherwise
        virtual bool mDivideBlock(blockptr block, const sizet size);

        /// @brief joins the block with its next block if possible
        /// @param block block to join with its next block
        /// @return true if sucessfull, false otherwise
        virtual bool mJoinBlock(blockptr block);

        /// @brief allocates block used to manage memory
        /// @param count count of blocks to allocate
        /// @return ptr to array of blocks
        virtual blockptr mAllocateBlocks(const sizet count = 1);

        /// @brief deallocates blocks used to manage memory
        /// @param blocks ptr to blocks
        /// @param count count of blocks
        virtual void mDeallocateBlocks(blockptr blocks, const sizet count = 1);

    protected:
        blockptr mFirstBlock;
        blockptr mFreeBlock;
        sizet mMemoryUsed;
    };

    LinkedMemPool::LinkedMemPool() noexcept :
        mFirstBlock(nullptr),
        mFreeBlock(nullptr),
        mMemoryUsed(0) { }

    inline memptr LinkedMemPool::AllocateRaw(const sizet size, bool clear)
    {
        blockptr block = mFindBlock(size);
        if (block iseq nullptr)
        {
            return nullptr;
        }

        if (mDivideBlock(block, size) isnot true)
        {
            return nullptr;
        }

        block->isFree = false;
        mMemoryUsed += size;
        return block->mem;
    }

    inline void LinkedMemPool::DeallocateRaw(memptr src, const sizet size)
    {
        if (src isnot nullptr)
        {
            blockptr block = mFindBlockFor(src);
            if (block iseq nullptr)
            {
                // todo: throw exception
                // this address is not managed by this pool
                return;
            }

            if (block->isFree iseq true)
            {
                // todo: throw exception
                // fatal, memory not allocated yet
                return;
            }

            sizet memOffset = (byte ptr) src - (byte ptr) block->mem;
            sizet blockSize = block->size - memOffset;
            if (blockSize < size)
            {
                // todo: throw exception
                // more memory accessed than allocated
                return;
            }

            // if src ptr is offset to bloc mem, we need to divide it into two blocks
            if (memOffset isnot 0)
            {
                if (mDivideBlock(block, memOffset))
                {
                    block = block->next;
                }
            }

            // if there is also an offset from the end of the block, we need to divide again
            memOffset = block->size - size;
            if (memOffset > 0)
            {
                if (mDivideBlock(block, size))
                {
                    block->next->isFree = false;
                }
            }

            block->isFree = true;
        }
    }

    inline sizet LinkedMemPool::UsedCount() const noexcept
    {
        return mMemoryUsed;
    }

    inline sizet LinkedMemPool::FreeCount() const noexcept
    {
        return Size() - UsedCount();
    }

    inline bool LinkedMemPool::HasBlockFor(const sizet size) const noexcept
    {
        return mFindBlock(size) isnot nullptr;
    }

    template <typename Type>
    inline bool LinkedMemPool::HasBlockFor(const sizet count) const noexcept
    {
        return mFindBlock(sizeof(Type) * count) isnot nullptr;
    }

    template <>
    inline bool LinkedMemPool::HasBlockFor<void>(const sizet count) const noexcept
    {
        return mFindBlock(count) isnot nullptr;
    }

    inline LinkedMemPool::blockptr LinkedMemPool::mFindBlock(const sizet size) const noexcept
    {
        for (auto block = mFreeBlock; block isnot nullptr; block = block->next)
        {
            if (block->isFree && block->size >= size)
            {
                return block;
            }
        }

        return nullptr;
    }

    inline LinkedMemPool::blockptr LinkedMemPool::mFindBlockFor(memptr mem) const noexcept
    {
        for (auto block = mFirstBlock; block isnot nullptr; block = block->next)
        {
            if (mem > block->mem and mem < (byte ptr)block->mem + block->size)
            {
                return block;
            }
        }

        return nullptr;
    }

    inline bool LinkedMemPool::mDivideBlock(blockptr block, const sizet size)
    {
        if (block isnot nullptr && block->size >= size)
        {
            sizet extraSize = block->size - size;
            if (extraSize > 0)
            {
                blockptr nextBlock = block->next;
                if (nextBlock iseq nullptr || nextBlock->isFree isnot true)
                {
                    nextBlock = new Block();
                    nextBlock->next = block->next;
                    nextBlock->isFree = true;
                }

                nextBlock->mem = (byte ptr)block->mem + size;
                nextBlock->size += extraSize;

                block->size = size;
                block->next = nextBlock;

                return true;
            }
        }

        return false;
    }

    inline bool LinkedMemPool::mJoinBlock(blockptr block)
    {
        if (block isnot nullptr and block->isFree iseq false and
            block->next isnot nullptr and block->next->isFree iseq false)
        {
            block->size += block->next->size;
            block->next = block->next->next;

            return true;
        }

        return false;
    }

    inline LinkedMemPool::blockptr LinkedMemPool::mAllocateBlocks(const sizet count)
    {
        return new Block[count];
    }

    inline void LinkedMemPool::mDeallocateBlocks(blockptr blocks, const sizet count)
    {
        delete[] blocks;
    }

    class DynamicLinkedMemPool : public virtual LinkedMemPool, public virtual DynamicMemPool {};
}