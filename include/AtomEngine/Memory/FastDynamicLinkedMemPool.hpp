#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Memory/FastLinkedMemPool.hpp"
#include "AtomEngine/Memory/DynamicLinkedMemPool.hpp"

namespace Atom
{
    template <sizet TBlockStackSize>
    class FastDynamicLinkedMemPool :
        public virtual FastLinkedMemPool<TBlockStackSize>,
        public virtual DynamicLinkedMemPool {};
}