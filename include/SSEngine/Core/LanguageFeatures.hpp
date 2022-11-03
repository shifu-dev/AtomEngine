#pragma once
#include "SSEngine/Core/Core.hpp"

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

#define and &&
#define or ||

#define noexceptif(cond) noexcept(noexcept(cond))

#define typeof(T) typeid(T)
#define nameof(T) typeid(T).name()

#define scast static_cast
#define dcast dynamic_cast
#define rcast reinteperet_cast

#define sassert static_assert