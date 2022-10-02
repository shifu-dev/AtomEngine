#pragma once
#include "SSEngine/Core.hpp"

namespace SSEngine
{
    template <typename Type>
    struct Comparer
    {
        virtual int Compare(const Type lref lhs, const Type lref rhs) const noexcept abstract;
    };

    template <typename Type>
    struct EqualityComparer
    {
        virtual bool Compare(const Type lref lhs, const Type lref rhs) const noexcept abstract;
    };
}