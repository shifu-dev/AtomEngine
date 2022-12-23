#include "AtomEngine/Memory.hpp"

namespace Atom
{
    class GlobalRootMemPool: public HeapMemPool<>
    {
        using BaseT = HeapMemPool<>;

    /// ----------------------------------------------------------------------------
    public:
        GlobalRootMemPool(sizet size):
            BaseT(size) { }

    /// ----------------------------------------------------------------------------
    protected:
        memptr _AllocateMemory(sizet size) final
        {
            // default implementation uses global mem pool
            return SCAST(memptr, malloc(size));
        }

        void _DeallocateMemory(memptr mem, sizet size) final
        {
            // default implementation uses global mem pool
            free(mem);
        }
    };

    ATOM_API DefaultAllocator DefaultAllocatorInstance = DefaultAllocator();
    ATOM_API IAllocator* globalAllocator = new GlobalRootMemPool(0);
}