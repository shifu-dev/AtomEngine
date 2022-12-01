#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Memory/IMemPool.hpp"
#include "AtomEngine/Memory/GlobalAllocation.hpp"

namespace Atom
{
    /// LinkedMemPool defines the base logic to implement a IMemPool using LinkedData structure.
    ///
    /// @note 
    /// - This type is not supposed to be used as an interface to recieve objects,
    ///   as this just defines the base functionality for code reusage, instead use IMemPool.
    ///
    /// @todo
    /// - Redesign LinkedMemPool to use object memory(memory used by user during allocation) to
    ///   allocate Block objects.
    class LinkedMemPool : public virtual IMemPool
    {
        /// Used to manage memory blocks
        mprotected struct Block
        {
            /// ----------------------------------------------------------------------------
            /// Ptr to memory block.
            memptr mem = nullptr;

            /// ----------------------------------------------------------------------------
            /// Size of this memory block.
            sizet size = 0;

            /// ----------------------------------------------------------------------------
            /// Is this memory available to use?
            bool isFree = true;

            /// ----------------------------------------------------------------------------
            /// Is this ptr the root of memory block?
            /// It is used to manage the memory block.
            bool isRoot = false;

            /// ----------------------------------------------------------------------------
            /// Ptr to next Block object, to create linked data structure.
            Block ptr next = nullptr;
        };

        /// ----------------------------------------------------------------------------
        /// Type alias to promote code readibility.
        mprotected using blockptr = Block ptr;

        /// ----------------------------------------------------------------------------
        /// Default Constructor
        mpublic LinkedMemPool() noexcept;

        mpublic virtual sizet Size() const noexcept override;

        /// ----------------------------------------------------------------------------
        /// Count of memory units currently in use(allocated) from the pool.
        mpublic virtual sizet UsedCount() const noexcept;

        /// ----------------------------------------------------------------------------
        /// Count of memory units available for use(unallocated) in the pool.
        mpublic virtual sizet FreeCount() const noexcept;

        /// ----------------------------------------------------------------------------
        /// Checks if a memory block of size \p{size} is available for allocation.
        /// 
        /// @param[in] size Size of memory block to check for, if \p{size} is 0 returns @false.
        /// @return @true if memory block exists, @false otherwise.
        mpublic virtual bool HasBlockFor(const sizet size) const noexcept;

        /// ----------------------------------------------------------------------------
        /// Checks if a memory block of size \p{sizeof(TType) * count} is available.
        /// 
        /// @tparam TType Type of object to check memory block for.
        /// \n \p{TType} is only used to find the size of Type.
        /// \n If \p{TType} is @void, considers its size 1.
        ///
        /// @param[in] count Count of objects to check memory block for,
        /// if \p{sizeof(TType) * count} is 0 returns @false.
        /// 
        /// @return @true if memory block exists, @false otherwise.
        /// 
        /// @note
        /// - Calls \p{HasBlockFor(sizeof(TType) * count)}.
        /// - Looks for a single contiguous memory block.
        mpublic template <typename TType>
            bool HasBlockFor(const sizet count) const noexcept;

        mpublic virtual memptr AllocateRaw(const sizet size, bool clear = true) override final;

        mpublic virtual memptr ReallocateRaw(memptr mem, const sizet size, bool clear = true, bool clearAll = false) override final;

        mpublic virtual void DeallocateRaw(memptr mem, const sizet size) override final;

        /// ----------------------------------------------------------------------------
        /// Adds memory block to the pool.
        /// 
        /// @param[in] mem Ptr to the memory block to add, if @null does nothing.
        /// @param[in] size Size of the memory block to add, if 0 does nothing.
        /// @param[in] isRoot Is this memory address the root of memory block.
        /// \n If @true, adds a flag for the memory address, used during deallocation of memory block.
        ///
        /// @return Block object representing added memory block, @null if memory block not added.
        mprotected virtual blockptr mAddMemory(const memptr mem, const sizet size, const bool isRoot = true);

        /// ----------------------------------------------------------------------------
        /// Tries to remove memory block from this pool, fails if memory block is being used.
        /// 
        /// @param[in] mem Ptr to memory block, if @null does nothing.
        /// @param[in] size Size of memory block to remove, if 0 does nothing.
        /// @param[in] tillHit If @true, remove till first hit (in use memory).
        /// @return Size of memory block removed from the pool.
        /// 
        /// @note
        /// - This does not deallocates the memory block, only removes it from the pool,
        ///   so the memory block is no longer managed by this pool.
        mprotected virtual sizet mTryRemoveMemory(const memptr mem, const sizet size, const bool tillHit = true);

        /// ----------------------------------------------------------------------------
        /// Finds the first Block object representing free memory block of size \p{size}.
        /// 
        /// @param[in] size Size of memory block to search Block object for,
        ///     if \p{size} is 0 does nothing.
        /// @return Block object representing memory block, @null if not found.
        mprotected virtual blockptr mFindBlock(const sizet size) const noexcept;

        /// ----------------------------------------------------------------------------
        /// Finds Block object which represents memory block \p{mem}.
        /// 
        /// @param[in] mem Memory block to search Block object for, if @null does nothing.
        /// @return Block object representing memory block, @null if not found.
        mprotected virtual blockptr mFindBlockFor(const memptr mem) const noexcept;

        /// ----------------------------------------------------------------------------
        /// Divides the Block object into two Block objects of size \p{size} and \p{block->size - size}.
        /// The new Block object will pointed by \p{block->next}.
        /// 
        /// @param[in] block Block object to divide, if \p{block is null} does nothing.
        /// @param[in] size Size of memory block of the first Block object, if \p{size is 0} does nothing.
        /// @return @true if successful, @false otherwise.
        mprotected virtual bool mDivideBlock(blockptr block, const sizet size);

        /// ----------------------------------------------------------------------------
        /// Joins the Block object with its next Block object if possible.
        /// 
        /// @param[in] block Block object to join with its next Block object, if @null does nothing.
        /// @return @true if successful, @false otherwise.
        mprotected virtual bool mJoinBlock(blockptr block);

        /// ----------------------------------------------------------------------------
        /// Creates a single Block object, may allocate new Block object or use prereserved Block object.
        /// 
        /// @return Ptr to the Block object, @null if failed.
        mprotected virtual blockptr mCreateBlock();

        /// ----------------------------------------------------------------------------
        /// Destroys Block object, may not deallocate memory and preserve it.
        /// 
        /// @param[in] block Ptr to the Block object.
        mprotected virtual void mDestroyBlock(blockptr block);

        /// ----------------------------------------------------------------------------
        /// Reserves \p{count} Block instances used to manage memory.
        /// 
        /// @param[in] count Count of Block instances to reserve.
        mprotected virtual void mReserveBlocks(const sizet count);

        /// ----------------------------------------------------------------------------
        /// Reserves count more Block objects used to manage memory.
        /// 
        /// @param[in] count Count of Block objects to reserve.
        /// 
        /// @note
        /// - This call is gaurenteed to cause allocation if \p{count > 0}.
        mprotected virtual void mReserveMoreBlocks(const sizet count);

        /// ----------------------------------------------------------------------------
        /// Allocates Block object used to manage memory.
        /// 
        /// @param[in] count Count of Block objects to allocate.
        /// @return Ptr to array of Block objects.
        mprotected virtual blockptr mAllocateBlocks(const sizet count);

        /// ----------------------------------------------------------------------------
        /// Deallocates Block objects used to manage memory.
        /// 
        /// @param[in] block objects ptr to Block objects
        /// @param[in] count count of Block objects
        mprotected virtual void mDeallocateBlock(blockptr block);

        /// ----------------------------------------------------------------------------
        /// Ptr to Root Block object of memory table.
        mprotected blockptr mRootBlock;

        /// ----------------------------------------------------------------------------
        /// Ptr to End Block object of memory table.
        mprotected blockptr mEndBlock;

        /// ----------------------------------------------------------------------------
        /// Ptr to First Block object with available memory.
        mprotected blockptr mFirstBlock;

        /// ----------------------------------------------------------------------------
        /// Count of memory units used.
        mprotected sizet mMemoryUsed;

        /// ----------------------------------------------------------------------------
        /// Total count of memory units managed by this pool.
        mprotected sizet mMemoryTotal;

        /// ----------------------------------------------------------------------------
        /// Ptr to the first reserved Block object.
        mprotected blockptr mFreeBlock;

        /// ----------------------------------------------------------------------------
        /// Current count of reserved Block objects.
        mprotected sizet mReservedBlockCount;

        /// ----------------------------------------------------------------------------
        /// Max count of Block objects to reserve,
        /// if \p{value is 0} no Block objects are reserved.
        mprotected sizet mMaxReservedBlockCount;
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

    inline memptr LinkedMemPool::ReallocateRaw(memptr mem, const sizet size, bool clear, bool clearAll)
    {
        if (mem == null)
        {
            return mem;
        }

        blockptr block = mFindBlockFor(mem);
        if (block is nullptr)
        {
            // todo: throw exception
            // this address is not managed by this pool
            return mem;
        }

        if (block->isFree is true)
        {
            // todo: throw exception
            // fatal, memory not allocated yet
            return mem;
        }

        // Requested to allocate memory of same size.
        if (block->size == size)
        {
            return mem;
        }

        // If we need to shrink memory, no need to assign another block
        if (block->size > size)
        {
            mDivideBlock(block, block->size - size);
            return mem;
        }

        // Check if we can extend already assigned memory.
        blockptr blockNext = block->next;
        if (blockNext->isFree and (block->size + blockNext->size >= size))
        {
            const sizet extraSpace = block->size + blockNext->size - size;
            if (extraSpace > 0)
            {
                mDivideBlock(blockNext, extraSpace);
            }

            mJoinBlock(block);
            return mem;
        }

        // Assign another block
        mDeallocateBlock(block);
        return AllocateRaw(size, clear);
    }

    inline void LinkedMemPool::DeallocateRaw(memptr mem, const sizet size)
    {
        if (mem isnot nullptr)
        {
            blockptr block = mFindBlockFor(mem);
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

            sizet memOffset = (byte ptr) mem - (byte ptr) block->mem;
            sizet blockSize = block->size - memOffset;
            if (blockSize < size)
            {
                // todo: throw exception
                // more memory accessed than allocated
                return;
            }

            // if mem ptr is offset to bloc mem, we need to divide it into two blocks
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

    inline LinkedMemPool::blockptr LinkedMemPool::mAddMemory(const memptr mem, const sizet size, const bool isRoot)
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

    inline sizet LinkedMemPool::mTryRemoveMemory(const memptr mem, const sizet size, const bool tillHit)
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
        memOffset = mem - rootBlock->mem;
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
}