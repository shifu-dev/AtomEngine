#pragma once
#include "AtomEngine/Core/Core.hpp"

#define interface struct

#define mpublic public:
#define mprotected protected:
#define mprivate private:

#define nullt std::nullptr_t
#define null nullptr

#define is ==
#define isnot !=
#define isnull(ptr) (ptr is nullptr)
#define isnotnull(ptr) (isnull(ptr) is false)

#define ptr *
#define ref &
#define rref &&
#define dtor ~
#define abstract = 0

#define noexceptif(cond) noexcept(noexcept(cond))

#define typeof(T) typeid(T)
#define nameof(T) typeid(T).name()

#define SCAST(TType, arg) static_cast<TType>(arg)
#define DCAST(TType, arg) dynamic_cast<TType>(arg)
#define RCAST(TType, arg) reinterpret_cast<TType>(arg)

#define SASSERT static_assert
#define STHROW(msg) SASSERT(false, msg)