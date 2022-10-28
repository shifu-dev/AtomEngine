#pragma once
#include <cstring>
#include "SSEngine/Core.hpp"

namespace SSEngine
{
    using memptr = void ptr;

    inline void memcpy(memptr dest, memptr src, const sizet size) noexcept
    {
        std::memcpy(dest, src, size);
    }

    inline void memset(memptr dest, const int value, const sizet count) noexcept
    {
        std::memset(dest, value, count);
    }
}