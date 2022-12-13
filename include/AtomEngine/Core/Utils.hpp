#include "AtomEngine/Core/LanguageFeatures.hpp"

/// ----------------------------------------------------------------------------
// BASE TYPES

namespace Atom
{
    using uchar = unsigned char;
    using sint = short int;
    using lint = long int;
    using llong = long long;
    using uint = unsigned int;
    using usint = unsigned short int;
    using ulint = unsigned long int;
    using sizet = size_t;
    constexpr sizet NPOS = -1;
}

#include "Byte.hpp"

/// ----------------------------------------------------------------------------
/// UTILS

namespace Atom
{
    template <typename TypeT>
    using RemoveReferenceT = std::remove_reference_t<TypeT>;

    template <typename TypeT>
    constexpr TypeT& min(TypeT& left, TypeT& right)
    {
        return left <= right ? left : right;
    }

    template <typename TypeT>
    constexpr const TypeT& max(const TypeT& left, const TypeT& right)
    {
        return left >= right ? left : right;
    }

    template <typename TypeT>
    constexpr TypeT&& forward(RemoveReferenceT<TypeT>& arg) noexcept
    {
        return SCAST(TypeT&&, arg);
    }

    template <class TypeT>
    constexpr RemoveReferenceT<TypeT>&& move(TypeT&& args) noexcept
    {
        // forward args as movable
        return SCAST(RemoveReferenceT<TypeT>&&, args);
    }

    template <typename TypeT>
    void swap(TypeT& lhs, TypeT& rhs) noexcept
    {
        TypeT& tmp = lhs;
        lhs = rhs;
        rhs = tmp;
    }
}