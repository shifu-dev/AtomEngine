#include <type_traits>
#include "SSEngine/Core/LanguageFeatures.hpp"

////////////////////////////////////////////////////////
// BASE TYPES

namespace SSEngine
{
    using uchar = unsigned char;
    using sint = short int;
    using lint = long int;
    using llong = long long;
    using uint = unsigned int;
    using usint = unsigned short int;
    using ulint = unsigned long int;
    using sizet = size_t;
}

namespace SSEngine
{
    enum class byte : uchar { };

    template <typename TInt, std::enable_if_t<std::is_integral_v<TInt>, int> = 0>
    [[nodiscard]] constexpr byte operator << (const byte value, const TInt shift) noexcept
    {
        // every scast is intentional
        return scast<byte>(scast<uchar>(
            scast<uint>(value) << shift));
    }

    template <typename TInt, std::enable_if_t<std::is_integral_v<TInt>, int> = 0>
    [[nodiscard]] constexpr byte operator >> (const byte value, const TInt shift) noexcept
    {
        // every scast is intentional
        return scast<byte>(scast<uchar>(
            scast<uint>(value) >> shift));
    }

    [[nodiscard]]
    constexpr byte operator | (const byte left, const byte right) noexcept
    {
        // every scast is intentional
        return scast<byte>(scast<uchar>(
            scast<uint>(left) | scast<uint>(right)));
    }

    [[nodiscard]]
    constexpr byte operator & (const byte left, const byte right) noexcept
    {
        // every scast is intentional
        return scast<byte>(scast<uchar>(
            scast<uint>(left) & scast<uint>(right)));
    }

    [[nodiscard]]
    constexpr byte operator ^ (const byte left, const byte right) noexcept
    {
        // every scast is intentional
        return scast<byte>(scast<uchar>(
            scast<uint>(left) ^ scast<uint>(right)));
    }

    [[nodiscard]]
    constexpr byte operator ~ (const byte value) noexcept
    {
        // every scast is intentional
        return scast<byte>(scast<uchar>(
            ~scast<uint>(value)));
    }

    template <typename TInt, std::enable_if_t<std::is_integral_v<TInt>, int> = 0>
    constexpr byte lref operator <<= (byte lref value, const TInt shift) noexcept
    {
        return value = value << shift;
    }

    template <typename TInt, std::enable_if_t<std::is_integral_v<TInt>, int> = 0>
    constexpr byte lref operator >>= (byte lref value, const TInt shift) noexcept
    {
        return value = value >> shift;
    }

    constexpr byte lref operator |= (byte lref left, const byte right) noexcept
    {
        return left = left | right;
    }

    constexpr byte lref operator &= (byte lref left, const byte right) noexcept
    {
        return left = left & right;
    }

    constexpr byte lref operator ^= (byte lref left, const byte right) noexcept
    {
        return left = left ^ right;
    }

    template <typename TInt, std::enable_if_t<std::is_integral_v<TInt>, int> = 0>
    [[nodiscard]] constexpr TInt toInt(const byte value) noexcept
    {
        return scast<TInt>(value);
    }

    // CPP17 introduces std::byte
#ifdef SS_ENGINE_CPP17

    constexpr operator std::byte(const byte value) noexcept
    {
        return scast<std::byte>(value);
    }

    constexpr operator byte(const std::byte value) noexcept
    {
        return scast<byte>(value);
    }

#endif

}

////////////////////////////////////////////////////////
/// UTILS

namespace SSEngine
{
    template <typename TType>
    const TType lref max(const TType lref left, const TType lref right)
    {
        return left >= right ? left : right;
    }

    template <typename TType>
    constexpr TType rref forward(typename std::remove_reference<TType>::type lref arg) noexcept
    {
        return scast<TType rref>(arg);
    }

    template <typename TType>
    auto move(TType value) noexcept
    {
        return std::move(value);
    }

    template <typename TType>
    void swap(TType lref lhs, TType lref rhs) noexcept
    {
        TType lref tmp = lhs;
        lhs = rhs;
        rhs = tmp;
    }
}