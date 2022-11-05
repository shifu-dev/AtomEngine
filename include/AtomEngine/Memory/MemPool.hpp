#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Memory/Allocator.hpp"

namespace Atom
{
    class MemPool : public virtual Allocator
    {
    public:

        /// @return total memory managed in bytes 
        virtual sizet Size() const noexcept abstract;
    };

    class DynamicMemPool : public virtual MemPool
    {
    public:

        /// @brief shrinks the pool as much as possible
        virtual void Shrink() abstract;

        /// @brief reserves specified memory
        virtual void Reserve(const sizet size) abstract;

        /// @brief reserves specified memory, over currently reserved memory
        /// does not checks for currently reserved memory
        virtual void ReserveMore(const sizet size) abstract;
    };
}