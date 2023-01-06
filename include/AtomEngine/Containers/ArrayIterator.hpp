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
        using DiffT = long;

    public:
        ConstArrayIterator(NullT null) noexcept:
            ThisT(nullptr, 0) { }

        ConstArrayIterator(const ElementT* ptr, DiffT length) noexcept:
            _ptr(ptr), _minPtr(ptr), _maxPtr(_ptr + length) { }

    public:
        const ElementT& Value() const override final
        {
            ASSERT(IsEnd() == false, "ArrayIterator has reached its end, cannot access value.");

            return *_ptr;
        }

        void MoveFwdBy(sizet steps) const override final
        {
            ASSERT(_ptr < _maxPtr, "ArrayIterator has reached its end, cannot move forward.");

            _ptr += steps;
        }

        void MoveBwdBy(sizet steps) const override final
        {
            ASSERT(_ptr > _minPtr, "ArrayIterator has reached its end, cannot move backward.");

            _ptr -= steps;
        }

        bool IsEnd() const noexcept override final
        {
            return _ptr < _minPtr || _ptr > _maxPtr;
        }

    protected:
        const ElementT mutable* _ptr;
        const ElementT* _minPtr;
        const ElementT* _maxPtr;
    };

    /// Iterator for array.
    /// 
    /// @tparam ElementT Type of element iterator iterates over.
    template <typename ElementT>
    class ArrayIterator: public ConstArrayIterator<ElementT>,
        public virtual IRandomAccessIterator<ElementT>
    {
        using ThisT = ArrayIterator<ElementT>;
        using BaseT = ConstArrayIterator<ElementT>;

    public:
        ArrayIterator(NullT null) noexcept:
            ThisT(nullptr, 0) { }

        ArrayIterator(ElementT* ptr, DiffT length) noexcept:
            BaseT(ptr, length) { }

    public:
        using BaseT::IsEnd;
    
        ElementT& Value() override final
        {
            ASSERT(IsEnd() == false, "ArrayIterator has reached its end, cannot access value.");

            return *CCAST(ElementT*, _ptr);
        }

    protected:
        using BaseT::_ptr;
    };
}