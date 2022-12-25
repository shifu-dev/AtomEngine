#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Memory/IAllocator.hpp"
#include "AtomEngine/Memory/GlobalAllocation.hpp"

namespace Atom
{
    class LegacyAllocator:
        public virtual IAllocator
    {
    public:
        memptr AllocateRaw(sizet count, bool clear = true) override final
        {
            count = max<sizet>(0, count);
            memptr dest = nullptr;

            if (count > 0)
            {
                dest = alloc(count);

                if (dest != nullptr)
                {
                    if (clear)
                    {
                        memset(dest, 0, count);
                    }
                }
            }

            return dest;
        }

        void DeallocateRaw(memptr mem, sizet count) override final
        {
            if (mem != nullptr)
            {
                dealloc(mem, count);
            }
        }
    };
}