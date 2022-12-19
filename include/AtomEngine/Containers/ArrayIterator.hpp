#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/IRandomAccessIterator.hpp"

namespace Atom
{
    /// Iterator for array.
    /// 
    /// @tparam ElementT Type of element iterator iterates over.
    template <typename ElementT>
    interface ArrayIterator: public virtual IRandomAccessIterator<ElementT>
    {
        using ThisT = ArrayIterator<ElementT>;
        using ConstElementT = const ElementT;
        using IteratorT = IIterator<ElementT>;

    public:
        ArrayIterator(ElementT* ptr)
            : _ptr(ptr) { }

        ArrayIterator(const ThisT& other) = default;
        ArrayIterator(ThisT&& other) = default;

        ThisT& operator = (const ThisT& other) = default;
        ThisT& operator = (ThisT&& other) = default;

        ~ArrayIterator() = default;

    public:
        ElementT& Value() noexcept final
        {
            return *_ptr;
        }

        ConstElementT& Value() const noexcept final
        {
            return *_ptr;
        }

        void MoveFwdBy(sizet steps) const noexcept final
        {
            _ptr += steps;
        }

        void MoveBwdBy(sizet steps) const noexcept final
        {
            _ptr -= steps;
        }

        int Compare(const IteratorT& rhs) const noexcept final
        {
            const ThisT* rhsPtr = DCAST(const ThisT*, &rhs);
            if (rhsPtr != nullptr)
            {
                return Compare(*rhsPtr);
            }

            return -1;
        }

        int Compare(const ThisT& rhs) const noexcept
        {
            return SCAST(int, _ptr - rhs._ptr);
        }

    protected:
        mutable ElementT* _ptr;
    };
}