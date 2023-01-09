#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Memory/UniqueBox.hpp"
#include "AtomEngine/Containers/IBidirectionalIterator.hpp"

namespace Atom
{
    template <typename ElementT>
    using BidirectionalIteratorBox = TUniqueBox<IBidirectionalIterator<ElementT>, 40>;
}