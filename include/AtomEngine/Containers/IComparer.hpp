#pragma once
#include "AtomEngine/Core.hpp"

namespace Atom
{
    template <typename Type>
    interface IComparer
    {
        virtual int Compare(const Type ref lhs, const Type ref rhs) const noexcept abstract;
    };

    template <typename Type>
    interface IEqualityComparer
    {
        virtual bool Compare(const Type ref lhs, const Type ref rhs) const noexcept abstract;
    };

    template <typename Type>
    struct DefaultEqualityComparer : public virtual IEqualityComparer<Type>
    {
        virtual bool Compare(const Type ref lhs, const Type ref rhs) const noexcept override
        {
            return lhs == rhs;
        }
    };
}