#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Memory/UniqueBox.hpp"
#include "AtomEngine/Containers/IIterator.hpp"

namespace Atom
{
    template <typename ElementT>
    using IteratorBox = TUniqueBox<IIterator<ElementT>, 40>;
}