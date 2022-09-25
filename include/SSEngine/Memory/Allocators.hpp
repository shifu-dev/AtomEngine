#pragma once
#include "SSEngine/Core.hpp"

namespace SSEngine
{
    /// @brief base allocator type to allocate memory,
    /// allocates on heap using new() and delete()
    struct Allocator
    {
    public:

        /// @brief allocates memory to specified type
        /// @tparam T type for which to allocate memory
        /// @param dest pointer to allocated memory space
        /// @param amount count of memory blocks to allocate for type T
        /// @return count of memory blocks allocated for type T
        ///
        /// @note if amount == 0, does not allocates memory.
        /// @note @param dest is equal to nullptr, in case of no memory allocation
        /// @note total memory allocated in bytes is equal to sizeof(T) * amount
        template <typename T>
        umax Allocate(T ptr ref dest, in umax amount = 1) noexcept;

        /// @brief allocates memory in bytes
        /// @param dest pointer to allocated memory space
        /// @param amount count in bytes to allocate memory
        /// @param clear if true, writes memory with zeros
        /// @return count in bytes of allocated memory
        virtual umax AllocateRaw(void ptr ref dest, in umax amount, bool clear = true) noexcept;

        /// @brief dellocates allocated memory
        /// @param src pointer to the memory space to dellocate
        /// @param amount amount of memory
        /// @return count of dellocated memory in bytes
        virtual umax Deallocate(in void ptr src, in umax amount) noexcept;
    };

    template <typename T>
    umax Allocator::Allocate(T ptr ref dest, in umax amount) noexcept
    {
        void ptr rawptr = dest;
        if (umax mem = AllocateRaw(rawptr, amount * sizeof(T)) > 0)
        {
            dest = (T ptr) rawptr;
            return mem / sizeof(T);
        }

        return 0;
    }

    // explicit specialization for void type,
    // to avoid sizeof() operator on void type
    template <>
    umax Allocator::Allocate<void>(void ptr ref dest, in umax amount) noexcept
    {
        return AllocateRaw(dest, amount);
    }

    umax Allocator::AllocateRaw(void ptr ref dest, in umax amount, bool clear) noexcept
    {
        if (isnotnull(dest) or amount > 0)
        {
            if (clear)
            {
                dest = new byte[amount]{ (byte)0 };
            }
            else
            {
                dest = new byte[amount]();
            }

            return amount;
        }

        dest = nullptr;
        return 0;
    }

    umax Allocator::Deallocate(in void ptr src, in umax amount) noexcept
    {
        if (isnotnull(src))
        {
            delete[](byte ptr) src;
            return amount;
        }

        return 0;
    }
}