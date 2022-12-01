#pragma once
#include "AtomEngine/Core.hpp"

namespace Atom
{
    /// Type used to represent unit memory block.
    /// 
    /// This type is gaurenteed to be compaitible with arithmetic operations (unlikes void).
    /// AtomEngine uses this type instead of typeless void.
    ///
    /// A single memt object is reffered as single memory unit.
    using memt = byte;

    /// Type representing ptr to unit memory block.
    /// 
    /// Recommended to use this instead of 'memt ptr' or 'memt*' for code readiblity.
    ///
    /// memptr is used to refer to a memory block.
    using memptr = memt ptr;

    /// Function to copy memory from one place to another.
    /// 
    /// @param dest Ptr to the destination to copy.
    /// @param src Ptr to the source to copy.
    /// @param size Count of memory units to copy.
    inline void memcpy(memptr dest, memptr src, const sizet size) noexcept
    {
        std::memcpy(dest, src, size);
    }

    /// Writes \p{value} at specified memory.
    /// 
    /// @param dest Ptr to the memory.
    /// @param value Value to write at memory.
    /// @param count Count of memory units to write.
    inline void memset(memptr dest, const int value, const sizet count) noexcept
    {
        std::memset(dest, value, count);
    }
}