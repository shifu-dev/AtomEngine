#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Memory/FastLinkedMemPool.hpp"

namespace Atom
{
    template<sizet TSize, sizet TBlockStackSize = (TSize / 2)>
    class StackMemPool : public virtual FastLinkedMemPool<TBlockStackSize>
    {
        using BaseT = FastLinkedMemPool<TBlockStackSize>;
        using BaseT::mAddMemory;

        mpublic static constexpr sizet SIZE = TSize;

        mpublic StackMemPool() noexcept
        {
            mAddMemory(mStackMemory, SIZE);
        }

        mprotected byte mStackMemory[SIZE];
    };
}