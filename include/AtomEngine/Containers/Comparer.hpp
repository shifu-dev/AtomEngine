#pragma once
#include "AtomEngine/Core.hpp"

namespace Atom
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

    template <typename Type>
    struct DefaultEqualityComparer : public EqualityComparer<Type>
    {
        virtual bool Compare(const Type lref lhs, const Type lref rhs) const noexcept override
        {
            return lhs == rhs;
        }
    };
}