#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Memory/UniqueBox.hpp"
#include "AtomEngine/Containers/IForwardIterator.hpp"

namespace Atom
{
    template <typename ElementT>
    using ConstForwardIteratorBox = TUniqueBox<IConstForwardIterator<ElementT>, 40>;

    template <typename ElementT>
    using ForwardIteratorBox = TUniqueBox<IForwardIterator<ElementT>, 40>;
}