#pragma once
#include "AtomEngine/Core/Core.hpp"

#define interface struct

#define NullT std::nullptr_t

#define abstract = 0
#define noexceptif(cond) noexcept(noexcept(cond))

#define typeof(T) typeid(T)
#define nameof(T) typeid(T).name()

#define SCAST(T, arg) static_cast<T>(arg)
#define DCAST(T, arg) dynamic_cast<T>(arg)
#define RCAST(T, arg) reinterpret_cast<T>(arg)
#define CCAST(T, arg) const_cast<T>(arg)

#define SASSERT static_assert
#define STHROW(msg) SASSERT(false, msg)