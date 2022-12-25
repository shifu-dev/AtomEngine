#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Memory/LinkedMemPool.hpp"

namespace Atom
{
    template <sizet BlockStackSize>
    class FastLinkedMemPool: public virtual LinkedMemPool
    {
        using BaseT = LinkedMemPool;

    /// ----------------------------------------------------------------------------
    public:
        FastLinkedMemPool() noexcept
        {
            _maxReservedBlockCount = BlockStackSize;
            _ReserveMoreBlocks(BlockStackSize);
        }

    /// ----------------------------------------------------------------------------
    protected:
        blockptr _AllocateBlocks(sizet count) override final
        {
            if (_stackResFreeBlock != NPOS)
            {
                blockptr block = &_stackResBlocks[_stackResFreeBlock];

                // find next free block before hand
                _stackResBlocksUsage[_stackResFreeBlock] = true;
                _stackResFreeBlock = NPOS;
                for (sizet i = _stackResFreeBlock; i < BlockStackSize; i++)
                {
                    if (_stackResBlocksUsage[_stackResFreeBlock] != true)
                    {
                        _stackResFreeBlock = i;
                        break;
                    }
                }

                return block;
            }

            return BaseT::_AllocateBlocks(count);
        }

        void _DeallocateBlock(blockptr block) override final
        {
            if (block > _stackResBlocks and block < _stackResBlocks + BlockStackSize)
            {
                sizet index = block - _stackResBlocks;
                _stackResBlocksUsage[index] = false;

                if (_stackResFreeBlock > index)
                {
                    _stackResFreeBlock = index;
                }

                return;
            }

            return BaseT::_DeallocateBlock(block);
        }

    protected:
        Block _stackResBlocks[BlockStackSize];
        bool _stackResBlocksUsage[BlockStackSize];
        sizet _stackResFreeBlock = 0;
    };
}