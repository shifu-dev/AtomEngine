#pragma once
#include <initializer_list>
#include "AtomEngine/Core.hpp"

namespace Atom
{
    template <typename TElement>
    using InitializerList = std::initializer_list<TElement>;
}