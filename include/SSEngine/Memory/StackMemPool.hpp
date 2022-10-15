#pragma once
#include "SSEngine/Core.hpp"
#include "SSEngine/Memory/FastLinkedMemPool.hpp"

namespace SSEngine
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