#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Memory/IAllocator.hpp"
#include "AtomEngine/Memory/GlobalAllocation.hpp"

namespace Atom
{
    class GlobalAllocator : public virtual IAllocator
    {
        mpublic memptr AllocateRaw(const sizet count, bool clear = true) final
        {
            return globalAllocator->AllocateRaw(count, clear);
        }

        mpublic memptr ReallocateRaw(const memptr mem, const sizet count, bool clear = true, bool clearAll = false) final
        {
            return globalAllocator->ReallocateRaw(mem, count, clear, clearAll);
        }

        mpublic void DeallocateRaw(const memptr mem, const sizet count) final
        {
            return globalAllocator->DeallocateRaw(mem, count);
        }
    };
}