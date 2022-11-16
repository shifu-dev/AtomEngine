// NOTE: This file supposed to be included byte AtomEngine/Core/Utils.hpp

namespace Atom
{
    namespace
    {
        template <typename TType>
        using EnableIfIntegral = std::enable_if_t<std::is_integral_v<TType>, int>;
    }

    struct byte
    {
        mprivate uchar value;

        ////////////////////////////////////////////////////////////////////////////////

        mpublic constexpr byte() noexcept : value(0) { }

        mpublic constexpr byte(const byte ref other) noexcept : byte()
        {
            value = other.value;
        }

        mpublic constexpr byte ref operator = (const byte ref other) noexcept
        {
            value = other.value;
            return ptr this;
        }

        mpublic template <typename TInt, EnableIfIntegral<TInt> = 0>
            constexpr byte(const TInt num) noexcept : value(0)
        {
            value = scast<uchar>(num);
        }

        mpublic template <typename TInt, EnableIfIntegral<TInt> = 0>
            constexpr operator TInt() const noexcept
        {
            return scast<TInt>(value);
        }

        ////////////////////////////////////////////////////////////////////////////////
        //// Arithmetic Operations

        template <typename TInt, EnableIfIntegral<TInt> = 0>
        [[nodiscard]] constexpr byte operator << (const TInt shift) const noexcept
        {
            return byte(scast<uint>(value) << shift);
        }

        template <typename TInt, EnableIfIntegral<TInt> = 0>
        [[nodiscard]] constexpr byte operator >> (const TInt shift) const noexcept
        {
            return byte(scast<uint>(value) >> shift);
        }

        [[nodiscard]]
        constexpr byte operator | (const byte right) const noexcept
        {
            return byte(scast<uint>(value) | scast<uint>(right.value));
        }

        [[nodiscard]]
        constexpr byte operator & (const byte right) const noexcept
        {
            return byte(scast<uint>(value) & scast<uint>(right.value));
        }

        [[nodiscard]]
        constexpr byte operator ^ (const byte right) const noexcept
        {
            return byte(scast<uint>(value) ^ scast<uint>(right.value));
        }

        [[nodiscard]]
        constexpr byte operator ~ () const noexcept
        {
            return byte(~scast<uint>(value));
        }

        template <typename TInt, EnableIfIntegral<TInt> = 0>
        constexpr byte ref operator <<= (const TInt shift) noexcept
        {
            return ptr this = ptr this << shift;
        }

        template <typename TInt, EnableIfIntegral<TInt> = 0>
        constexpr byte ref operator >>= (const TInt shift) noexcept
        {
            return ptr this = ptr this >> shift;
        }

        constexpr byte ref operator |= (const byte right) noexcept
        {
            return ptr this = ptr this | right;
        }

        constexpr byte ref operator &= (const byte right) noexcept
        {
            return ptr this = ptr this & right;
        }

        constexpr byte ref operator ^= (const byte right) noexcept
        {
            return ptr this = ptr this ^ right;
        }
    };
}