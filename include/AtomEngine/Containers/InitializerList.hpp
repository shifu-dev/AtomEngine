#pragma once
#include <initializer_list>
#include "AtomEngine/Core.hpp"

namespace Atom
{
    template <typename ElementT>
    using InitializerList = std::initializer_list<ElementT>;
}