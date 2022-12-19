// NOTE: This file supposed to be included byte AtomEngine/Core/Utils.hpp

namespace Atom
{
    namespace
    {
        template <typename T>
        using EnableIfIntegral = std::enable_if_t<std::is_integral_v<T>, int>;
    }

    struct byte
    {
    /// ----------------------------------------------------------------------------
    public:
        constexpr byte() noexcept:
            value(0) { }

        constexpr byte(const byte& other) noexcept:
            byte()
        {
            value = other.value;
        }

        constexpr byte& operator = (const byte& other) noexcept
        {
            value = other.value;
            return *this;
        }

        template <typename IntT, EnableIfIntegral<IntT> = 0>
        constexpr byte(const IntT num) noexcept: value(0)
        {
            value = SCAST(uchar, num);
        }

        template <typename IntT, EnableIfIntegral<IntT> = 0>
        constexpr operator IntT() const noexcept
        {
            return SCAST(IntT, value);
        }

    /// ----------------------------------------------------------------------------
    /// Arithmetic Operations
    public:

        template <typename IntT, EnableIfIntegral<IntT> = 0>
        [[nodiscard]] constexpr byte operator << (const IntT shift) const noexcept
        {
            return byte(SCAST(uint, value) << shift);
        }

        template <typename IntT, EnableIfIntegral<IntT> = 0>
        [[nodiscard]] constexpr byte operator >> (const IntT shift) const noexcept
        {
            return byte(SCAST(uint, value) >> shift);
        }

        [[nodiscard]]
        constexpr byte operator | (const byte right) const noexcept
        {
            return byte(SCAST(uint, value) | SCAST(uint, right.value));
        }

        [[nodiscard]]
        constexpr byte operator & (const byte right) const noexcept
        {
            return byte(SCAST(uint, value) & SCAST(uint, right.value));
        }

        [[nodiscard]]
        constexpr byte operator ^ (const byte right) const noexcept
        {
            return byte(SCAST(uint, value) ^ SCAST(uint, right.value));
        }

        [[nodiscard]]
        constexpr byte operator ~ () const noexcept
        {
            return byte(~SCAST(uint, value));
        }

        template <typename IntT, EnableIfIntegral<IntT> = 0>
        constexpr byte& operator <<= (const IntT shift) noexcept
        {
            return *this = *this << shift;
        }

        template <typename IntT, EnableIfIntegral<IntT> = 0>
        constexpr byte& operator >>= (const IntT shift) noexcept
        {
            return *this = *this >> shift;
        }

        constexpr byte& operator |= (const byte right) noexcept
        {
            return *this = *this | right;
        }

        constexpr byte& operator &= (const byte right) noexcept
        {
            return *this = *this & right;
        }

        constexpr byte& operator ^= (const byte right) noexcept
        {
            return *this = *this ^ right;
        }

    /// ----------------------------------------------------------------------------
    private:
        uchar value;
    };
}