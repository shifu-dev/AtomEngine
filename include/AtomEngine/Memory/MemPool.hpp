#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Memory/Allocator.hpp"

namespace Atom
{
    /// @brief MemPool is the base abstract type to manage memory pool.
    class MemPool : public virtual Allocator
    {
        /// @brief Count of memory units managed by this pool.
        mpublic virtual sizet Size() const noexcept abstract;
    };

    /// @brief DynamicMemPool represents resizable memory pool.
    class DynamicMemPool : public virtual MemPool
    {
        /// @brief Shrinks the pool as much as possible.
        mpublic virtual void Shrink() abstract;

        /// @brief Reserves specified memory.
        /// @param size Minimum count of memory units to reserve.
        /// 
        /// After this call MemPool is gaurenteed to have at least size memory.
        mpublic virtual void Reserve(const sizet size) abstract;

        /// @brief Reserves specified memory, over currently reserved memory.
        /// @param size Minimum count of memory units to reserve.
        ///
        /// @note ReserveMore is gaurenteed to allocate memory.
        mpublic virtual void ReserveMore(const sizet size) abstract;
    };
}