#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/IRandomAccessIterator.hpp"

namespace Atom
{
    /// Iterator for array.
    /// 
    /// @tparam ElementT Type of element iterator iterates over.
    template <typename ElementT>
    class TConstArrayIterator:
        public virtual IConstRandomAccessIterator<ElementT>
    {
        using ThisT = TConstArrayIterator<ElementT>;

    public:
        TConstArrayIterator(NullT null) noexcept:
            ThisT(nullptr, 0) { }

        TConstArrayIterator(const ElementT* arr, SizeT length, SizeT offset = 0) noexcept:
            _arrBegin(arr + offset), _arr(_arrBegin),
            _arrMin(arr), _arrMax(arr + length)
        {
            if (_arrBegin > _arrMax + 1)
            {
                _arrBegin = _arrMax + 1;
                _arr = _arrBegin;
            }
        }

        TConstArrayIterator(const ElementT* begin, const ElementT* end, SizeT offset = 0) noexcept:
            ThisT(begin < end ? begin : end, abs(end - begin), offset) { }

    public:
        const ElementT& Value() const override final
        {
            ASSERT(IsEnd() == false, "Iterator has reached its end, cannot access value.");

            return *_arr;
        }

        virtual void Reset() const noexcept override final
        {
            _arr = _arrBegin;
        }

        bool IsEnd() const noexcept override final
        {
            return _arr <= _arrMin && _arr >= _arrMax;
        }

        void MoveFwdBy(SizeT steps) const override final
        {
            ASSERT(_arr <= _arrMax, "Iterator has reached its end, cannot move forward.");

            steps = min<SizeT>(steps, (_arrMax + 1) - _arr);
            _arr += steps;
        }

        void MoveBwdBy(SizeT steps) const override final
        {
            ASSERT(_arr >= _arrMin, "Iterator has reached its end, cannot move backward.");

            steps = min<SizeT>(steps, _arr - (_arrMin - 1));
            _arr -= steps;
        }

    protected:
        const ElementT mutable* _arr;
        const ElementT* _arrMin;
        const ElementT* _arrMax;
        const ElementT* _arrBegin;
    };

    /// Iterator for array.
    /// 
    /// @tparam ElementT Type of element iterator iterates over.
    template <typename ElementT>
    class TArrayIterator: public TConstArrayIterator<ElementT>,
        public virtual IRandomAccessIterator<ElementT>
    {
        using ThisT = TArrayIterator<ElementT>;
        using BaseT = TConstArrayIterator<ElementT>;

    public:
        TArrayIterator(NullT null) noexcept:
            BaseT(null) { }

        TArrayIterator(ElementT* arr, SizeT length, SizeT offset = 0) noexcept:
            BaseT(arr, length, offset) { }

        TArrayIterator(ElementT* begin, ElementT* end, SizeT offset = 0) noexcept:
            BaseT(begin, end, offset) { }

    public:
        using BaseT::IsEnd;

        ElementT& Value() override final
        {
            ASSERT(IsEnd() == false, "Iterator has reached its end, cannot access value.");

            return *CCAST(ElementT*, _arr);
        }

    protected:
        using BaseT::_arr;
    };
}