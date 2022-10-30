#pragma once
#include "SSEngine/Core.hpp"
#include "SSEngine/Containers/Iterator.hpp"
#include <stdexcept>

namespace SSEngine
{
    template <typename TElement>
    class Array;

    /// @brief iterator for stack array
    /// @tparam TElement type of element stack array holds
    template <typename TElement>
    class ArrayIterator : public virtual RandomAccessIterator<TElement>
    {
        using ThisT = ArrayIterator<TElement>;
        using ContainerDefinationT = ContainerDefination<TElement>;
        using ElementT = typename ContainerDefinationT::ElementT;
        using SizeT = typename ContainerDefinationT::SizeT;
        using IteratorT = typename ContainerDefinationT::IteratorT;

    public:
        using SizeType = SizeT;
        using ElementType = ElementT;

    public:
        ArrayIterator(TElement ptr elementPtr)
            : _ptr(elementPtr) { }

        ArrayIterator(const ThisT lref other) = default;
        ArrayIterator(ThisT rref other) = default;

        ThisT lref operator = (const ThisT lref other) = default;
        ThisT lref operator = (ThisT rref other) = default;

        virtual TElement lref Value() noexcept override
        {
            return ptr _ptr;
        }

        virtual const TElement lref Value() const noexcept override
        {
            return ptr _ptr;
        }

        virtual void MoveFwdBy(const SizeT steps) const noexcept override
        {
            _ptr = _ptr + steps;
        }

        virtual void MoveBwdBy(const SizeT steps) const noexcept override
        {
            _ptr = _ptr - steps;
        }

        virtual int Compare(const IteratorT lref rhs) const noexcept override
        {
            const ThisT ptr rhsPtr = dcast<const ThisT ptr>(lref rhs);
            if (rhsPtr isnot null)
            {
                return Compare(ptr rhsPtr);
            }

            return -1;
        }

        virtual int Compare(const ThisT lref rhs) const noexcept
        {
            return _ptr - rhs._ptr;
        }

    protected:
        mutable ElementType ptr _ptr;
    };
}