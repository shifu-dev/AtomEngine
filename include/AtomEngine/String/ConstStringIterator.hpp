#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/IRandomAccessIterator.hpp"

namespace Atom
{
    template <typename CharT>
    class TConstStringIterator:
        public virtual IConstRandomAccessIterator<CharT>
    {
        using IConstIteratorT = IConstIterator<CharT>;

    public:
        TConstStringIterator(const CharT* ptr)
            : _ptr(ptr) { }

    public:
        const CharT& Value() const noexcept final
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

        int Compare(const IConstIteratorT& rhs) const noexcept final
        {
            if (*_ptr == rhs.Value())
                return 0;

            return -1;
        }

    protected:
        const CharT mutable* _ptr;
    };
}