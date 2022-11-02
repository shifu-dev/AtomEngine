#pragma once
#include "SSEngine/Memory/Allocator.hpp"

namespace SSEngine
{
    SS_ENGINE_API extern Allocator ptr globalAllocator;

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
        return globalAllocator->Construct<TType>(forward<TArgs>(args)...);
    }

    template <typename TType, typename... TArgs>
    inline TType ptr createArr(const sizet count, TArgs... args)
    {
        return globalAllocator->ConstructMultiple<TType>(count, forward<TArgs>(args)...);
    }

    template <typename TType>
    inline void destroy(TType ptr obj)
    {
        globalAllocator->Destruct<TType>(obj);
    }

    template <typename TType>
    inline void destroyArr(const sizet count, TType ptr obj)
    {
        globalAllocator->Destruct<TType>(obj, count);
    }
}