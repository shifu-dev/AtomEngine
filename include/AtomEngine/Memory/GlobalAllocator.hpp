#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Memory/IAllocator.hpp"
#include "AtomEngine/Memory/GlobalAllocation.hpp"

namespace Atom
{
    class GlobalAllocator:
        public virtual IAllocator
    {
    public:
        memptr AllocateRaw(sizet count, bool clear = true) final
        {
            return globalAllocator->AllocateRaw(count, clear);
        }

        memptr ReallocateRaw(const memptr mem, sizet count, bool clear = true, bool clearAll = false) final
        {
            return globalAllocator->ReallocateRaw(mem, count, clear, clearAll);
        }

        void DeallocateRaw(const memptr mem, sizet count) final
        {
            return globalAllocator->DeallocateRaw(mem, count);
        }
    };
}