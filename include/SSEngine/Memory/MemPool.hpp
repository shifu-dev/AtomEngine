#pragma once
#include "SSEngine/Core.hpp"
#include "SSEngine/Memory/Allocators.hpp"

namespace SSEngine
{
    class MemPool : public Allocator
    {
        using memptr = void ptr;

    public:
        virtual sizet Size() const noexcept;
    };
}