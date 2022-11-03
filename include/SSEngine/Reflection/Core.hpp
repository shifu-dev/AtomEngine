#pragma once
#include <type_traits>
#include "SSEngine/Core.hpp"

namespace SSEngine
{
    template <typename TBase, typename TDerived>
    inline constexpr bool IsSubClass = std::is_convertible_v<TBase ptr, TDerived ptr>;
}