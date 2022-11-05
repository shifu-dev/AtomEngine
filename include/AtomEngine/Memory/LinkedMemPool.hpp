#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Memory/MemPool.hpp"
#include "AtomEngine/Memory/GlobalAllocation.hpp"

namespace Atom
{
    class LinkedMemPool : public virtual MemPool
    {
    protected:
        struct Block
        {
            memptr mem = nullptr;   // ptr to memory
            sizet size = 0;         // size of this memory block
            bool isFree = true;     // is this memory available to use?
            bool isRoot = false;    // is this ptr used to manage memory block?

            Block ptr next = nullptr;
        };

        using blockptr = Block ptr;

    public:
        LinkedMemPool() noexcept;

    public:
        virtual memptr AllocateRaw(const sizet size, bool clear = true) override;
        virtual void DeallocateRaw(memptr src, const sizet size) override;

        virtual sizet Size() const noexcept final override;

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

        /// @brief adds memory to be managed by this memory pool
        /// @param mem ptr to memory, does not do anything if null
        /// @param isRoot is this memory ptr the root of memory block
        /// @param size size of memory block
        /// @return ptr to the block representing memory, null is memory not added
        virtual blockptr mAddMemory(memptr mem, const sizet size, bool isRoot = true);

        /// @brief removes memory from this memory pool
        /// @param mem ptr to memory, does not do anything if null
        /// @param size size of memory block to remove
        /// @param tillHit if true, remove till first hit (in use memory)
        /// @return size of memory block removed from the pool
        /// @note this does not deallocates the memory
        virtual sizet mTryRemoveMemory(memptr mem, const sizet size, const bool tillHit = true);

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

        /// @brief allocates or uses cache to create single block
        /// @return ptr to the block
        virtual blockptr mCreateBlock();

        /// @brief deallocates or caches blocks
        /// @param blocks ptr to blocks
        /// @param count count of blocks
        virtual void mDestroyBlock(blockptr block);

        /// @brief reserves count blocks used to manage memory
        /// @param count count of blocks to reserve
        virtual void mReserveBlocks(const sizet count);

        /// @brief reserves count blocks used to manage memory,
        /// does not checks already reserved count
        /// @param count count of blocks to reserve
        virtual void mReserveMoreBlocks(const sizet count);

        /// @brief allocates blocks used to manage memory
        /// @param count count of blocks to allocate
        /// @return ptr to array of blocks
        virtual blockptr mAllocateBlocks(const sizet count);

        /// @brief deallocates blocks used to manage memory
        /// @param blocks ptr to blocks
        /// @param count count of blocks
        virtual void mDeallocateBlock(blockptr block);

    protected:
        blockptr mRootBlock;            // root block of memory layout
        blockptr mEndBlock;             // end block of memory layout
        blockptr mFirstBlock;           // first block with available memory
        sizet mMemoryUsed;              // count of memory used in bytes
        sizet mMemoryTotal;             // total memory managed by this pool

        blockptr mFreeBlock;            // first free block (block allocation cache)
        sizet mReservedBlockCount;      // current count of reserved block allocations
        sizet mMaxReservedBlockCount;   // max count of block allocations to reserve
    };

    inline LinkedMemPool::LinkedMemPool() noexcept :
        mRootBlock(nullptr), mEndBlock(nullptr), mFirstBlock(nullptr), mMemoryUsed(0),
        mFreeBlock(nullptr), mReservedBlockCount(0), mMaxReservedBlockCount(-1) { }

    inline memptr LinkedMemPool::AllocateRaw(const sizet size, bool clear)
    {
        blockptr block = mFindBlock(size);
        if (block is nullptr)
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
            if (block is nullptr)
            {
                // todo: throw exception
                // this address is not managed by this pool
                return;
            }

            if (block->isFree is true)
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

    inline sizet LinkedMemPool::Size() const noexcept
    {
        return mMemoryTotal;
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

    inline LinkedMemPool::blockptr LinkedMemPool::mAddMemory(memptr mem, const sizet size, bool isRoot)
    {
        blockptr block = nullptr;

        if (mem isnot nullptr && size isnot 0)
        {
            block = mCreateBlock();
            block->mem = mem;
            block->size = size;
            block->isRoot = isRoot;
            block->isFree = true;
            block->next = nullptr;

            if (mRootBlock is nullptr)
            {
                mRootBlock = block;
                mEndBlock = block;
            }
            else
            {
                mEndBlock->next = block;
                mEndBlock = block;
            }

            mMemoryTotal += size;
        }

        return block;
    }

    inline sizet LinkedMemPool::mTryRemoveMemory(memptr mem, const sizet size, const bool tillHit)
    {
        if (mem is nullptr) return 0;
        if (size is 0) return 0;

        blockptr rootBlock = nullptr;   // root block of memory to remove
        blockptr endBlock = nullptr;    // end block of memory to remove
        sizet memOffset = 0;            // offset from the root block
        sizet memInset = 0;             // offset from the end block
        sizet memCount = 0;             // mem count we can remove

        // find the block managing this memory
        rootBlock = mFindBlockFor(mem);

        // this memory is not managed by this pool
        if (rootBlock is nullptr) return 0;

        // process root for memOffset
        memOffset = (byte ptr)mem - (byte ptr)rootBlock->mem;
        memCount = rootBlock->size - memOffset;

        for (blockptr block = rootBlock->next; block isnot nullptr; block = block->next)
        {
            // stop at first hit
            if (block->isFree isnot true)
            {
                if (tillHit) break;

                return 0;
            }

            memCount += block->size;

            if (memCount >= size)
            {
                endBlock = block;
                break;
            }
        }

        memInset = memCount - size;

        // start removing blocks now

        if (memOffset isnot 0)
        {
            mDivideBlock(rootBlock, memOffset);
            rootBlock = rootBlock->next;
        }

        if (memInset isnot 0)
        {
            mDivideBlock(endBlock, endBlock->size - memInset);
        }

        for (blockptr block = rootBlock; block isnot endBlock; block = block->next)
        {
            mJoinBlock(block);
        }

        mMemoryTotal -= memCount;
        return 0;
    }

    inline LinkedMemPool::blockptr LinkedMemPool::mFindBlock(const sizet size) const noexcept
    {
        for (auto block = mFirstBlock; block isnot nullptr; block = block->next)
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
        for (auto block = mRootBlock; block isnot nullptr; block = block->next)
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
                if (nextBlock is nullptr || nextBlock->isFree isnot true)
                {
                    nextBlock = mCreateBlock();
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
        if (block isnot nullptr and block->isFree is true)
        {
            blockptr nextBlock = block->next;
            if (nextBlock isnot nullptr and nextBlock->isFree is true)
            {
                block->size += nextBlock->size;
                block->next = nextBlock->next;

                mDestroyBlock(nextBlock);
                return true;
            }
        }

        return false;
    }

    inline LinkedMemPool::blockptr LinkedMemPool::mCreateBlock()
    {
        blockptr block = nullptr;

        if (mFreeBlock isnot nullptr)
        {
            block = mFreeBlock;
            mFreeBlock = mFreeBlock->next;

            ptr block = Block();
            mReservedBlockCount--;
        }
        else
        {
            block->next = mAllocateBlocks(1);
        }

        return block;
    }

    inline void LinkedMemPool::mDestroyBlock(blockptr block)
    {
        if (mReservedBlockCount < mMaxReservedBlockCount)
        {
            ptr block = Block();
            block->next = mFreeBlock;

            mFreeBlock = block;
        }
        else
        {
            mDeallocateBlock(block);
        }
    }

    inline void LinkedMemPool::mReserveBlocks(const sizet count)
    {
        if (mReservedBlockCount < count)
        {
            mReserveMoreBlocks(count - mReservedBlockCount);
        }
    }

    inline void LinkedMemPool::mReserveMoreBlocks(const sizet count)
    {
        if (count isnot 0)
        {
            blockptr rootBlock = mAllocateBlocks(count);
            blockptr endBlock = rootBlock;
            for (; endBlock->next isnot nullptr; endBlock = endBlock->next)
            {
                mReservedBlockCount++;
            }

            if (mFreeBlock isnot nullptr)
            {
                endBlock->next = mFreeBlock;
            }

            mFreeBlock = rootBlock;
        }
    }

    inline LinkedMemPool::blockptr LinkedMemPool::mAllocateBlocks(const sizet count)
    {
        return createArr<Block>(count);
    }

    inline void LinkedMemPool::mDeallocateBlock(blockptr block)
    {
        destroy(block);
    }

    class DynamicLinkedMemPool :
        public virtual LinkedMemPool,
        public virtual DynamicMemPool
    {
    public:
        virtual void Shrink() override;
        virtual void Reserve(const sizet size) override;
        virtual void ReserveMore(const sizet size) override;

    protected:
        virtual memptr mAllocateMemory(const sizet count) abstract;
        virtual void mDeallocateMemory(memptr mem, const sizet count) abstract;

        /// @brief calls mAllocateMemory, and passes it to mAddMemory(mem, size, isRoot);
        blockptr mAddMemory(const sizet size, bool isRoot = true);
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