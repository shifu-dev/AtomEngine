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
    using SizeT = size_t;
    constexpr sizet NPOS = -1;
}

#include "Byte.hpp"

/// ----------------------------------------------------------------------------
/// UTILS

namespace Atom
{
    template <typename T>
    using RemoveReferenceT = std::remove_reference_t<T>;

    template <typename T>
    constexpr const T& min(const T& left, const T& right)
    {
        return left <= right ? left : right;
    }

    template <typename T>
    constexpr const T& max(const T& left, const T& right)
    {
        return left >= right ? left : right;
    }

    template <typename T>
    constexpr T&& forward(RemoveReferenceT<T>& arg) noexcept
    {
        return SCAST(T&&, arg);
    }

    template <class T>
    constexpr RemoveReferenceT<T>&& move(T&& args) noexcept
    {
        // forward args as movable
        return SCAST(RemoveReferenceT<T>&&, args);
    }

    template <typename T>
    void swap(T& lhs, T& rhs) noexcept
    {
        T& tmp = lhs;
        lhs = rhs;
        rhs = tmp;
    }
}

/// @todo implement this
#define DEBUG_ASSERT(assertion, msg)