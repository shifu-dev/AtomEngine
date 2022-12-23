#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/String/ConstStringIterator.hpp"

namespace Atom
{
    template <typename CharT>
    class TStringIterator: public TConstStringIterator<CharT>,
        public virtual IRandomAccessIterator<CharT>
    {
        using BaseT = TConstStringIterator<CharT>;

    public:
        TStringIterator(CharT* ptr) noexcept:
            BaseT(ptr) { }

    public:
        CharT& Value() noexcept final
        {
            return *CCAST(CharT*, _ptr);
        }

    protected:
        using BaseT::_ptr;
    };
}