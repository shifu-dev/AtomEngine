#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Memory/FastLinkedMemPool.hpp"
#include "AtomEngine/Memory/DynamicLinkedMemPool.hpp"

namespace Atom
{
    template <sizet BlockStackSize>
    class FastDynamicLinkedMemPool : public FastLinkedMemPool<BlockStackSize>,
        public virtual DynamicLinkedMemPool {};
}