#pragma once
#include "AtomEngine/Core/Core.hpp"

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

#define scast static_cast
#define dcast dynamic_cast
#define rcast reinterpret_cast

#define sassert static_assert
#define sthrow(msg) sassert(false, msg)