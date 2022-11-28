#include "AtomEngine/Memory.hpp"

namespace Atom
{
    class GlobalRootMemPool : public HeapMemPool<>
    {
        using BaseT = HeapMemPool<>;

        mpublic GlobalRootMemPool(const sizet size) : BaseT(size) { }

        mpublic virtual memptr mAllocateMemory(const sizet size) override
        {
            // default implementation uses global mem pool
            return SCAST(memptr, malloc(size));
        }

        mpublic virtual void mDeallocateMemory(memptr mem, const sizet size) override
        {
            // default implementation uses global mem pool
            free(mem);
        }
    };

    ATOM_API Allocator ptr globalAllocator = new GlobalRootMemPool(0);
}