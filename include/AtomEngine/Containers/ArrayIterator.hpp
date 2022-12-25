#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/IRandomAccessIterator.hpp"

namespace Atom
{
    /// Iterator for array.
    /// 
    /// @tparam ElementT Type of element iterator iterates over.
    template <typename ElementT>
    class ConstArrayIterator:
        public virtual IConstRandomAccessIterator<ElementT>
    {
        using ThisT = ConstArrayIterator<ElementT>;
        using ConstIteratorT = IConstIterator<ElementT>;

    public:
        ConstArrayIterator(const ElementT* ptr)
            : _ptr(ptr) { }

    public:
        const ElementT& Value() const noexcept override final
        {
            return *_ptr;
        }

        void MoveFwdBy(sizet steps) const noexcept override final
        {
            _ptr += steps;
        }

        void MoveBwdBy(sizet steps) const noexcept override final
        {
            _ptr -= steps;
        }

        int Compare(const ConstIteratorT& rhs) const noexcept override final
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
        const ElementT mutable* _ptr;
    };

    /// Iterator for array.
    /// 
    /// @tparam ElementT Type of element iterator iterates over.
    template <typename ElementT>
    class ArrayIterator: public ConstArrayIterator<ElementT>,
        public virtual IRandomAccessIterator<ElementT>
    {
        using BaseT = ConstArrayIterator<ElementT>;

    public:
        ArrayIterator(ElementT* ptr) noexcept:
            BaseT(ptr) { }

    public:
        ElementT& Value() noexcept override final
        {
            return *CCAST(ElementT*, _ptr);
        }

    protected:
        using BaseT::_ptr;
    };
}