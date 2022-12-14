#pragma once
#include "AtomEngine/Core.hpp"

namespace Atom
{
    template <typename T>
    interface IComparer
    {
        virtual int Compare(const T& lhs, const T& rhs) const noexcept = 0;
    };

    template <typename T>
    interface IEqualityComparer
    {
        virtual bool Compare(const T& lhs, const T& rhs) const noexcept = 0;
    };

    template <typename T>
    struct DefaultEqualityComparer: public virtual IEqualityComparer<T>
    {
        bool Compare(const T& lhs, const T& rhs) const noexcept override final
        {
            return lhs == rhs;
        }
    };
}