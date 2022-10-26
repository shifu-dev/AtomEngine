#pragma once
#include <cstddef>
#include <memory>
#include <iostream>
#include <cstring>
#pragma warning(disable: 4250)
// #include <bits/c++config.h>

#define SS_NAME SoulSphere
#define SS_ENGINE_NAME SoulSphereEngine
#define SS_ENGINE_SHORT_NAME SSEngine
#define SS_CREATE_NAME_ALIAS(type) using SS ##type

// ****************************************************
// * type aliases for ease of use

using uchar = unsigned char;
using ushort = unsigned short int;
using ulong = unsigned long int;
using uint = unsigned int;
using uchar = unsigned char;
using sizet = size_t;

using byte = std::byte;
// enum class byte : uchar {};

using memptr = void*;

// ****************************************************
// * macros (keywords) to improve code readibility

#define nullt std::nullptr_t
#define null nullptr

#define iseq ==
#define isnot !=
#define isnull(ptr) (ptr iseq nullptr)
#define isnotnull(ptr) (isnull(ptr) iseq false)

#define ptr *
#define lref &
#define rref &&
#define dtor ~
#define abstract = 0

#define noexcept noexcept
#define noexceptif(cond) noexcept(noexcept(cond))

#define typeof(T) typeid(T)
#define nameof(T) typeid(T).name()

// ****************************************************
// * arguments forwarding and moving

namespace SSEngine
{
    template<typename Type>
    constexpr Type rref forward(typename std::remove_reference<Type>::type lref arg) noexcept
    {
        return static_cast<Type rref>(arg);
    }

    template <typename T>
    auto move(T value) noexcept
    {
        return std::move(value);
    }

    inline void memcpy(void ptr dest, void ptr src, const sizet size) noexcept
    {
        std::memcpy(dest, src, size);
    }

    inline void memset(void ptr dest, const int value, const sizet count) noexcept
    {
        std::memset(dest, value, count);
    }
}