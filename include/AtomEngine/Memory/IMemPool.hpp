#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Memory/IAllocator.hpp"

namespace Atom
{
    /// ----------------------------------------------------------------------------
    /// IMemPool is the base interface to manage memory pool.
    interface IMemPool : public virtual IAllocator
    {
        /// ----------------------------------------------------------------------------
        /// Count of memory units managed by this pool.
        mpublic virtual sizet Size() const noexcept abstract;
    };
}