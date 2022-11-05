#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Memory/Allocator.hpp"

namespace Atom
{
    class MemPool : public virtual Allocator
    {
        /// @return total memory managed in bytes 
        mpublic virtual sizet Size() const noexcept abstract;
    };

    class DynamicMemPool : public virtual MemPool
    {
        /// @brief shrinks the pool as much as possible
        mpublic virtual void Shrink() abstract;

        /// @brief reserves specified memory
        mpublic virtual void Reserve(const sizet size) abstract;

        /// @brief reserves specified memory, over currently reserved memory
        /// does not checks for currently reserved memory
        mpublic virtual void ReserveMore(const sizet size) abstract;
    };
}