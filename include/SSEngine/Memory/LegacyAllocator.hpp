#pragma once
#include "SSEngine/Core.hpp"
#include "SSEngine/Memory/Allocators.hpp"
#include "SSEngine/Memory/GlobalAllocation.hpp"

namespace SSEngine
{
    struct LegacyAllocator : public Allocator
    {
        virtual memptr AllocateRaw(const sizet count, bool clear = true) override;
        virtual void DeallocateRaw(memptr src, const sizet count) override;
    };

    inline memptr LegacyAllocator::AllocateRaw(sizet count, bool clear)
    {
        count = max<sizet>(0, count);
        memptr dest = null;

        if (count > 0)
        {
            dest = alloc(count);

            if (dest isnot null)
            {
                if (clear)
                {
                    memset(dest, 0, count);
                }
            }
        }

        return dest;
    }

    inline void LegacyAllocator::DeallocateRaw(memptr src, const sizet count)
    {
        if (isnotnull(src))
        {
            dealloc(src, count);
        }
    }
}