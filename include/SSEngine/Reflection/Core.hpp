#pragma once
#include <type_traits>
#include "SSEngine/Core.hpp"

namespace SSEngine
{
    template <typename TBase, typename TDerived>
    inline constexpr bool IsSubClass = std::is_convertible_v<TDerived ptr, TBase ptr>;

    template <typename TBase, typename TDerived>
    constexpr void StaticAssertSubClass()
    {
        // sassert(IsSubClass<TBase, TDerived>, nameof(TDerived) + " is not a subclass of " + nameof(TBase));
        sassert(IsSubClass<TBase, TDerived>, "Inappropriate SubClass");
    }

    template <bool Enable>
    using EnableIf = std::enable_if_t<Enable>;
}