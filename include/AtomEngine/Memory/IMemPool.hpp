#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Memory/IAllocator.hpp"

namespace Atom
{
    /// IMemPool == the base interface to manage memory pool.
    interface IMemPool:
        public virtual IAllocator
    {
        /// Count of memory units managed by this pool.
        virtual sizet Size() const noexcept = 0;
    };
}