#pragma once
#include "AtomEngine/Core.hpp"

namespace Atom
{
    template <typename BaseT, typename DerivedT>
    inline constexpr bool IsSubClass =
    std::is_convertible_v
    <
        std::remove_const_t<
        std::remove_volatile_t<
        std::remove_reference_t<DerivedT>>> *,

        std::remove_const_t<
        std::remove_volatile_t<
        std::remove_reference_t<BaseT>>> *
    >;

    template <typename BaseT, typename DerivedT>
    constexpr void StaticAssertSubClass()
    {
        SASSERT(IsSubClass<BaseT, DerivedT>, "Inappropriate SubClass");
    }

    template <bool Enable>
    using EnableIf = std::enable_if_t<Enable, int>;
}