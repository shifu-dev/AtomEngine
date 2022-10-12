#pragma once
#include "SSEngine/Core.hpp"
#include "SSEngine/Memory/Allocators.hpp"

namespace SSEngine
{
    class MemPool : public Allocator
    {
        using memptr = void ptr;

    public:

        /// @return total memory managed in bytes 
        virtual sizet Size() const noexcept abstract;
    };

    class DynamicMemPool : public MemPool
    {
        using memptr = void ptr;

    public:

        /// @brief resizes pool to specified size
        virtual void Resize(const sizet size) abstract;

        /// @brief reserves specified memory
        virtual void Reserve(const sizet size) abstract;
    };
}