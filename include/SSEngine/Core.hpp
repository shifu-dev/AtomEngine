#pragma once
#include <stddef.h>
#include <bits/c++config.h>

using uchar = unsigned char;
using ushort = unsigned short int;
using ulong = unsigned long int;
using uint = unsigned int;
using uchar = unsigned char;
using umax = size_t;
enum byte : char {};
enum ubyte : unsigned char {};

// ****************************************************
// macros (keywords) to improve code readibility

#define nullt std::nullptr_t
#define null nullptr;

#define is ==
#define isnot !=
#define isnull(ptr) (ptr is nullptr)
#define isnotnull(ptr) (isnull(ptr) is false)

#define var auto
#define ptr *
#define in const
#define ref &
#define out(type) outarg<type>

// #define noexcept noexcept
#define noexceptif(cond) noexcept(noexcept(cond))

template <typename T>
struct outarg
{
public:
    using type = T;

public:
    outarg() = delete;
    outarg(T ref value) : value(value) {}

    template <typename TParam>
    void operator=(TParam arg)
    {
        value = arg;
    }

    operator T ref() const noexcept
    {
        return value;
    }

    T ref operator -> ()
    {
        return value;
    }

public:
    T ref value;
};