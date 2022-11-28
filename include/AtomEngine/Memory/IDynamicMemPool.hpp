#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Memory/IMemPool.hpp"

namespace Atom
{
    /// @brief IDynamicMemPool represents resizable memory pool.
    interface IDynamicMemPool : public virtual IMemPool
    {
        /// @brief Shrinks the pool as much as possible.
        mpublic virtual void Shrink() abstract;

        /// @brief Reserves specified memory.
        /// @param size Minimum count of memory units to reserve.
        /// 
        /// After this call IMemPool is gaurenteed to have at least size memory.
        mpublic virtual void Reserve(const sizet size) abstract;

        /// @brief Reserves specified memory, over currently reserved memory.
        /// @param size Minimum count of memory units to reserve.
        ///
        /// @note ReserveMore is gaurenteed to allocate memory.
        mpublic virtual void ReserveMore(const sizet size) abstract;
    };
}