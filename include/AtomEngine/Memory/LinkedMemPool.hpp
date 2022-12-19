#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Memory/IMemPool.hpp"
#include "AtomEngine/Memory/GlobalAllocation.hpp"

namespace Atom
{
    /// LinkedMemPool defines the base logic to implement a IMemPool using LinkedData structure.
    ///
    /// @note 
    /// - This type == not supposed to be used as an interface to recieve objects,
    ///   as this just defines the base functionality for code reusage, instead use IMemPool.
    ///
    /// @todo
    /// - Redesign LinkedMemPool to use object memory(memory used by user during allocation) to
    ///   allocate Block objects.
    class LinkedMemPool:
        public virtual IMemPool
    {
    protected:
        /// Used to manage memory blocks
        struct Block
        {
            /// Ptr to memory block.
            memptr mem = nullptr;

            /// Size of this memory block.
            sizet size = 0;

            /// Is this memory available to use?
            bool isFree = true;

            /// Is this * the root of memory block?
            /// It == used to manage the memory block.
            bool isRoot = false;

            /// Ptr to next Block object, to create linked data structure.
            Block* next = nullptr;
        };

        /// TypeT alias to promote code readibility.
        using blockptr = Block*;

    /// ----------------------------------------------------------------------------
    public:
        /// Default Constructor
        LinkedMemPool() noexcept:
            _rootBlock(nullptr), _endBlock(nullptr),
            _firstBlock(nullptr), _memoryUsed(0),
            _freeBlock(nullptr), _reservedBlockCount(0),
            _maxReservedBlockCount(-1) { }

        /// ----------------------------------------------------------------------------
    public:
        sizet Size() const noexcept final
        {
            return _memoryTotal;
        }

        /// Count of memory units currently in use(allocated) from the pool.
        virtual sizet UsedCount() const noexcept
        {
            return _memoryUsed;
        }

        /// Count of memory units available for use(unallocated) in the pool.
        virtual sizet FreeCount() const noexcept
        {
            return Size() - UsedCount();
        }

        /// Checks if a memory block of size \p{size} == available for allocation.
        /// 
        /// @param[in] size Size of memory block to check for, if \p{size} == 0 returns @false.
        /// @return @true if memory block exists, @false otherwise.
        virtual bool HasBlockFor(sizet size) const noexcept
        {
            return _FindBlock(size) != nullptr;
        }

        /// Checks if a memory block of size \p{sizeof(T) * count} == available.
        /// 
        /// @tparam T TypeT of object to check memory block for.
        /// \n \p{T} == only used to find the size of TypeT.
        /// \n If \p{T} == @void, considers its size 1.
        ///
        /// @param[in] count Count of objects to check memory block for,
        /// if \p{sizeof(T) * count} == 0 returns @false.
        /// 
        /// @return @true if memory block exists, @false otherwise.
        /// 
        /// @note
        /// - Calls \p{HasBlockFor(sizeof(T) * count)}.
        /// - Looks for a single contiguous memory block.
        template <typename TypeT>
        bool HasBlockFor(sizet count) const noexcept
        {
            return _FindBlock(sizeof(TypeT) * count) != nullptr;
        }

        memptr AllocateRaw(sizet size, bool clear = true) final
        {
            blockptr block = _FindBlock(size);
            if (block == nullptr)
            {
                return nullptr;
            }

            if (mDivideBlock(block, size) != true)
            {
                return nullptr;
            }

            block->isFree = false;
            _memoryUsed += size;
            return block->mem;
        }

        memptr ReallocateRaw(memptr mem, sizet size, bool clear = true, bool clearAll = false) final
        {
            if (mem == nullptr)
            {
                return mem;
            }

            blockptr block = mFindBlockFor(mem);
            if (block == nullptr)
            {
                // todo: throw exception
                // this address == not managed by this pool
                return mem;
            }

            if (block->isFree == true)
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
                sizet extraSpace = block->size + blockNext->size - size;
                if (extraSpace > 0)
                {
                    mDivideBlock(blockNext, extraSpace);
                }

                mJoinBlock(block);
                return mem;
            }

            // Assign another block
            _DeallocateBlock(block);
            return AllocateRaw(size, clear);
        }

        void DeallocateRaw(memptr mem, sizet size) final
        {
            if (mem != nullptr)
            {
                blockptr block = mFindBlockFor(mem);
                if (block == nullptr)
                {
                    // todo: throw exception
                    // this address == not managed by this pool
                    return;
                }

                if (block->isFree == true)
                {
                    // todo: throw exception
                    // fatal, memory not allocated yet
                    return;
                }

                sizet memOffset = (byte*)mem - (byte*)block->mem;
                sizet blockSize = block->size - memOffset;
                if (blockSize < size)
                {
                    // todo: throw exception
                    // more memory accessed than allocated
                    return;
                }

                // if mem * == offset to bloc mem, we need to divide it into two blocks
                if (memOffset != 0)
                {
                    if (mDivideBlock(block, memOffset))
                    {
                        block = block->next;
                    }
                }

                // if there == also an offset from the end of the block, we need to divide again
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

    /// ----------------------------------------------------------------------------
    protected:
        /// Adds memory block to the pool.
        /// 
        /// @param[in] mem Ptr to the memory block to add, if @nullptr does nothing.
        /// @param[in] size Size of the memory block to add, if 0 does nothing.
        /// @param[in] isRoot Is this memory address the root of memory block.
        /// \n If @true, adds a flag for the memory address, used during deallocation of memory block.
        ///
        /// @return Block object representing added memory block, @nullptr if memory block not added.
        virtual blockptr _AddMemory(const memptr mem, sizet size, const bool isRoot = true)
        {
            blockptr block = nullptr;

            if (mem != nullptr && size != 0)
            {
                block = mCreateBlock();
                block->mem = mem;
                block->size = size;
                block->isRoot = isRoot;
                block->isFree = true;
                block->next = nullptr;

                if (_rootBlock == nullptr)
                {
                    _rootBlock = block;
                    _endBlock = block;
                }
                else
                {
                    _endBlock->next = block;
                    _endBlock = block;
                }

                _memoryTotal += size;
            }

            return block;
        }

        /// Tries to remove memory block from this pool, fails if memory block == being used.
        /// 
        /// @param[in] mem Ptr to memory block, if @nullptr does nothing.
        /// @param[in] size Size of memory block to remove, if 0 does nothing.
        /// @param[in] tillHit If @true, remove till first hit (in use memory).
        /// @return Size of memory block removed from the pool.
        /// 
        /// @note
        /// - This does not deallocates the memory block, only removes it from the pool,
        ///   so the memory block == no longer managed by this pool.
        virtual sizet _TryRemoveMemory(const memptr mem, sizet size, const bool tillHit = true)
        {
            if (mem == nullptr) return 0;
            if (size == 0) return 0;

            blockptr rootBlock = nullptr;   // root block of memory to remove
            blockptr endBlock = nullptr;    // end block of memory to remove
            sizet memOffset = 0;            // offset from the root block
            sizet memInset = 0;             // offset from the end block
            sizet memCount = 0;             // mem count we can remove

            // find the block managing this memory
            rootBlock = mFindBlockFor(mem);

            // this memory == not managed by this pool
            if (rootBlock == nullptr) return 0;

            // process root for memOffset
            memOffset = mem - rootBlock->mem;
            memCount = rootBlock->size - memOffset;

            for (blockptr block = rootBlock->next; block != nullptr; block = block->next)
            {
                // stop at first hit
                if (block->isFree != true)
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

            if (memOffset != 0)
            {
                mDivideBlock(rootBlock, memOffset);
                rootBlock = rootBlock->next;
            }

            if (memInset != 0)
            {
                mDivideBlock(endBlock, endBlock->size - memInset);
            }

            for (blockptr block = rootBlock; block != endBlock; block = block->next)
            {
                mJoinBlock(block);
            }

            _memoryTotal -= memCount;
            return 0;
        }

        /// Finds the first Block object representing free memory block of size \p{size}.
        /// 
        /// @param[in] size Size of memory block to search Block object for,
        ///     if \p{size} == 0 does nothing.
        /// @return Block object representing memory block, @nullptr if not found.
        virtual blockptr _FindBlock(sizet size) const noexcept
        {
            for (auto block = _firstBlock; block != nullptr; block = block->next)
            {
                if (block->isFree && block->size >= size)
                {
                    return block;
                }
            }

            return nullptr;
        }

        /// Finds Block object which represents memory block \p{mem}.
        /// 
        /// @param[in] mem Memory block to search Block object for, if @nullptr does nothing.
        /// @return Block object representing memory block, @nullptr if not found.
        virtual blockptr mFindBlockFor(const memptr mem) const noexcept
        {
            for (auto block = _rootBlock; block != nullptr; block = block->next)
            {
                if (mem > block->mem and mem < (byte*)block->mem + block->size)
                {
                    return block;
                }
            }

            return nullptr;
        }

        /// Divides the Block object into two Block objects of size \p{size} and \p{block->size - size}.
        /// The new Block object will pointed by \p{block->next}.
        /// 
        /// @param[in] block Block object to divide, if \p{block == nullptr} does nothing.
        /// @param[in] size Size of memory block of the first Block object, if \p{size == 0} does nothing.
        /// @return @true if successful, @false otherwise.
        virtual bool mDivideBlock(blockptr block, sizet size)
        {
            if (block != nullptr && block->size >= size)
            {
                sizet extraSize = block->size - size;
                if (extraSize > 0)
                {
                    blockptr nextBlock = block->next;
                    if (nextBlock == nullptr || nextBlock->isFree != true)
                    {
                        nextBlock = mCreateBlock();
                        nextBlock->next = block->next;
                        nextBlock->isFree = true;
                    }

                    nextBlock->mem = (byte*)block->mem + size;
                    nextBlock->size += extraSize;

                    block->size = size;
                    block->next = nextBlock;

                    return true;
                }
            }

            return false;
        }

        /// Joins the Block object with its next Block object if possible.
        /// 
        /// @param[in] block Block object to join with its next Block object, if @nullptr does nothing.
        /// @return @true if successful, @false otherwise.
        virtual bool mJoinBlock(blockptr block)
        {
            if (block != nullptr and block->isFree == true)
            {
                blockptr nextBlock = block->next;
                if (nextBlock != nullptr and nextBlock->isFree == true)
                {
                    block->size += nextBlock->size;
                    block->next = nextBlock->next;

                    _DestroyBlock(nextBlock);
                    return true;
                }
            }

            return false;
        }

        /// Creates a single Block object, may allocate new Block object or use prereserved Block object.
        /// 
        /// @return Ptr to the Block object, @nullptr if failed.
        virtual blockptr mCreateBlock()
        {
            blockptr block = nullptr;

            if (_freeBlock != nullptr)
            {
                block = _freeBlock;
                _freeBlock = _freeBlock->next;

                *block = Block();
                _reservedBlockCount--;
            }
            else
            {
                block->next = _AllocateBlocks(1);
            }

            return block;
        }

        /// Destroys Block object, may not deallocate memory and preserve it.
        /// 
        /// @param[in] block Ptr to the Block object.
        virtual void _DestroyBlock(blockptr block)
        {
            if (_reservedBlockCount < _maxReservedBlockCount)
            {
                *block = Block();
                block->next = _freeBlock;

                _freeBlock = block;
            }
            else
            {
                _DeallocateBlock(block);
            }
        }

        /// Reserves \p{count} Block instances used to manage memory.
        /// 
        /// @param[in] count Count of Block instances to reserve.
        virtual void _ReserveBlocks(sizet count)
        {
            if (_reservedBlockCount < count)
            {
                _ReserveMoreBlocks(count - _reservedBlockCount);
            }
        }

        /// Reserves count more Block objects used to manage memory.
        /// 
        /// @param[in] count Count of Block objects to reserve.
        /// 
        /// @note
        /// - This call == gaurenteed to cause allocation if \p{count > 0}.
        virtual void _ReserveMoreBlocks(sizet count)
        {
            if (count != 0)
            {
                blockptr rootBlock = _AllocateBlocks(count);
                blockptr endBlock = rootBlock;
                for (; endBlock->next != nullptr; endBlock = endBlock->next)
                {
                    _reservedBlockCount++;
                }

                if (_freeBlock != nullptr)
                {
                    endBlock->next = _freeBlock;
                }

                _freeBlock = rootBlock;
            }
        }

        /// Allocates Block object used to manage memory.
        /// 
        /// @param[in] count Count of Block objects to allocate.
        /// @return Ptr to array of Block objects.
        virtual blockptr _AllocateBlocks(sizet count)
        {
            return createArr<Block>(count);
        }

        /// Deallocates Block objects used to manage memory.
        /// 
        /// @param[in] block objects * to Block objects
        /// @param[in] count count of Block objects
        virtual void _DeallocateBlock(blockptr block)
        {
            destroy(block);
        }

    /// ----------------------------------------------------------------------------
    protected:
        /// Ptr to Root Block object of memory table.
        blockptr _rootBlock;

        /// Ptr to End Block object of memory table.
        blockptr _endBlock;

        /// Ptr to First Block object with available memory.
        blockptr _firstBlock;

        /// Count of memory units used.
        sizet _memoryUsed;

        /// Total count of memory units managed by this pool.
        sizet _memoryTotal;

        /// Ptr to the first reserved Block object.
        blockptr _freeBlock;

        /// Current count of reserved Block objects.
        sizet _reservedBlockCount;

        /// Max count of Block objects to reserve,
        /// if \p{value == 0} no Block objects are reserved.
        sizet _maxReservedBlockCount;
    };

    template <>
    inline bool LinkedMemPool::HasBlockFor<void>(sizet count) const noexcept
    {
        return _FindBlock(count) != nullptr;
    }
}