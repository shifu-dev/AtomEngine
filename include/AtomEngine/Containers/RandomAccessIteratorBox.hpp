#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Memory/UniqueBox.hpp"
#include "AtomEngine/Containers/IRandomAccessIterator.hpp"

namespace Atom
{
    template <typename ElementT>
    using RandomAccessIteratorBox = TUniqueBox<IRandomAccessIterator<ElementT>, 40>;
}