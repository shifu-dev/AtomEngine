#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Memory/IAllocator.hpp"
#include "AtomEngine/Memory/GlobalAllocation.hpp"

namespace Atom
{
    class GlobalAllocator : IAllocator
    {
        mpublic memptr AllocateRaw(const sizet count, bool clear = true) override final
        {
            return globalAllocator->AllocateRaw(count, clear);
        }

        mpublic void DeallocateRaw(const memptr mem, const sizet count) override final
        {
            return globalAllocator->DeallocateRaw(mem, count);
        }
    };
}