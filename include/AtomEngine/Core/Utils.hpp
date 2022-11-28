#include "AtomEngine/Core/LanguageFeatures.hpp"

////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////
/// UTILS

namespace Atom
{
    template <typename TType>
    const TType ref max(const TType ref left, const TType ref right)
    {
        return left >= right ? left : right;
    }

    template <typename TType>
    constexpr TType rref forward(typename std::remove_reference<TType>::type ref arg) noexcept
    {
        return SCAST(TType rref, arg);
    }

    template <class TType>
    [[nodiscard]] constexpr std::remove_reference_t<TType> rref move(TType rref args) noexcept
    {
        // forward args as movable
        return SCAST(std::remove_reference_t<TType> rref, args);
    }

    template <typename TType>
    void swap(TType ref lhs, TType ref rhs) noexcept
    {
        TType ref tmp = lhs;
        lhs = rhs;
        rhs = tmp;
    }
}