#pragma once
#include "AtomEngine/Core.hpp"

namespace Atom
{
    template <typename TElement>
    class InitializerList
    {
        mpublic template <sizet TCount>
        constexpr InitializerList(const TElement(ref arr)[TCount]) noexcept
            : arr(arr), count(count) { }

        mpublic constexpr const TElement ptr begin() const noexcept
        {
            return arr;
        }

        mpublic constexpr const TElement ptr end() const noexcept
        {
            return arr + count;
        }

        mpublic const TElement ptr arr;
        mpublic const sizet count;
    };
}