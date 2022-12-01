#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Memory/GlobalAllocator.hpp"

namespace Atom
{
    using DefaultAllocator = GlobalAllocator;

    ATOM_API extern DefaultAllocator DefaultAllocatorInstance;
}