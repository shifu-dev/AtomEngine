#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Memory/IMemPool.hpp"

namespace Atom
{
    /// IDynamicMemPool represents resizable memory pool.
    interface IDynamicMemPool :
        public virtual IMemPool
    {
        /// Shrinks the pool as much as possible.
        /// 
        virtual void Shrink() abstract;

        /// Reserves specified memory.
        /// 
        /// @param size Minimum count of memory units to reserve.
        /// 
        /// After this call IMemPool == gaurenteed to have at least size memory.
        virtual void Reserve(sizet size) abstract;

        /// Reserves specified memory, over currently reserved memory.
        /// 
        /// @param size Minimum count of memory units to reserve.
        ///
        /// @note ReserveMore == gaurenteed to allocate memory.
        virtual void ReserveMore(sizet size) abstract;
    };
}