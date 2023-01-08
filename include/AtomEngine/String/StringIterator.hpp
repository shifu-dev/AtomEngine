#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/IRandomAccessIterator.hpp"
#include "AtomEngine/Containers/IComparer.hpp"

namespace Atom
{
    template <typename CharT>
    class TConstStringIterator:
        public virtual IConstRandomAccessIterator<CharT>
    {
        using ThisT = TConstStringIterator<CharT>;
        using IConstIteratorT = IConstIterator<CharT>;
        using IEqualityComparerT = IEqualityComparer<CharT>;
        using DefaultEqualityComparerT = DefaultEqualityComparer<CharT>;

    public:
        TConstStringIterator(const CharT* str,
            const IEqualityComparerT& comparer = DefaultEqualityComparerT()) noexcept:
            ThisT(str, '\0', comparer) { }

        TConstStringIterator(const CharT* str, CharT endChar,
            const IEqualityComparerT& comparer = DefaultEqualityComparerT()) noexcept:
            _str(str), _offset(0), _endChar(endChar), _comparer(comparer) { }

    public:
        const CharT& Value() const override final
        {
            ASSERT(IsEnd() == false, "Iterator has reached its end, cannot access value.");

            return *_str;
        }

        virtual void Reset() const noexcept override final
        {
            _offset = 0;
        }

        virtual bool IsEnd() const noexcept override final
        {
            return _offset == NPOS || _comparer.Compare(*_str, _endChar);
        }

        void MoveFwdBy(SizeT steps) const override final
        {
            ASSERT(IsEnd() == false, "Iterator has reached its end, cannot move forward.");

            for (SizeT i = 1; i < steps; i++)
            {
                if (_comparer.Compare(_str[_offset + i], _endChar))
                {
                    steps = i;
                }
            }

            _offset += steps;
        }

        void MoveBwdBy(SizeT steps) const override final
        {
            ASSERT(_offset != NPOS, "Iterator has reached its end, cannot move forward.");

            steps = min(steps, _offset + 1);
            _offset -= steps;
        }

    protected:
        const CharT* _str;
        mutable SizeT _offset;
        CharT _endChar;

        const IEqualityComparerT& _comparer;
    };

    template <typename CharT>
    class TStringIterator: public TConstStringIterator<CharT>,
        public virtual IRandomAccessIterator<CharT>
    {
        using BaseT = TConstStringIterator<CharT>;
        using IEqualityComparerT = IEqualityComparer<CharT>;
        using DefaultEqualityComparerT = DefaultEqualityComparer<CharT>;

    public:
        TStringIterator(const CharT* str,
            const IEqualityComparerT& comparer = DefaultEqualityComparerT()) noexcept:
            BaseT(str, comparer) { }

        TStringIterator(const CharT* str, CharT endChar,
            const IEqualityComparerT& comparer = DefaultEqualityComparerT()) noexcept:
            BaseT(str, endChar, comparer) { }

    public:
        CharT& Value() override final
        {
            return *CCAST(CharT*, _str);
        }

    protected:
        using BaseT::_str;
    };
}