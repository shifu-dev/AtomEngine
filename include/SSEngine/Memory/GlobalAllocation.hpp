#pragma once
#include "SSEngine/Memory/Allocators.hpp"

namespace SSEngine
{
    extern Allocator ptr globalAllocator;

    inline memptr alloc(const sizet size)
    {
        return globalAllocator->AllocateRaw(size);
    }

    inline void dealloc(const memptr mem, const sizet size)
    {
        globalAllocator->Deallocate(mem, size);
    }

    template <typename TType, typename... TArgs>
    inline TType ptr create(TArgs... args)
    {
        globalAllocator->Construct(sizeof(TType));
    }

    template <typename TType>
    inline void destroy(TType ptr obj)
    {
        globalAllocator->Destruct(obj);
    }
}