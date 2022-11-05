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

    public:
        static constexpr sizet SIZE = TSize;

    public:
        StackMemPool() noexcept
        {
            mAddMemory(mStackMemory, SIZE);
        }

    protected:
        byte mStackMemory[SIZE];
    };
}