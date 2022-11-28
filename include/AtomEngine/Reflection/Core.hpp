#pragma once
#include "AtomEngine/Core.hpp"

namespace Atom
{
    template <typename TBase, typename TDerived>
    inline constexpr bool IsSubClass =
    std::is_convertible_v
    <
        std::remove_const_t<
        std::remove_volatile_t<
        std::remove_reference_t<TDerived>>> ptr,

        std::remove_const_t<
        std::remove_volatile_t<
        std::remove_reference_t<TBase>>> ptr
    >;

    template <typename TBase, typename TDerived>
    constexpr void StaticAssertSubClass()
    {
        SASSERT(IsSubClass<TBase, TDerived>, "Inappropriate SubClass");
    }

    template <bool Enable, typename TType = bool>
    using EnableIf = std::enable_if_t<Enable, TType>;
}