#pragma once
#include "AtomEngine/Memory/IAllocator.hpp"

namespace Atom
{
    ATOM_API extern IAllocator* globalAllocator;

    inline memptr alloc(sizet size)
    {
        return globalAllocator->AllocateRaw(size);
    }

    inline void dealloc(const memptr mem, sizet size)
    {
        globalAllocator->Deallocate(mem, size);
    }

    template <typename T, typename... ArgsT>
    inline T* create(ArgsT... args)
    {
        return globalAllocator->Construct<T>(forward<ArgsT>(args)...);
    }

    template <typename T, typename... ArgsT>
    inline T* createArr(sizet count, ArgsT... args)
    {
        return globalAllocator->ConstructMultiple<T>(count, forward<ArgsT>(args)...);
    }

    template <typename T>
    inline void destroy(T* obj)
    {
        globalAllocator->Destruct<T>(obj);
    }

    template <typename T>
    inline void destroyArr(sizet count, T* obj)
    {
        globalAllocator->Destruct<T>(obj, count);
    }
}