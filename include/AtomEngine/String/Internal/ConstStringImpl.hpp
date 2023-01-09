#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/ForLoopIterator.hpp"
#include "AtomEngine/Containers/Internal/ConstArrayImpl.hpp"
#include "AtomEngine/String/IConstString.hpp"

namespace Atom::Internal
{
    /// Basic IConstString implementation.
    /// @tparam CharT Type of character this string stores.
    template <typename CharT>
    class TConstStringImpl: public virtual ConstArrayImpl<CharT>,
        public virtual IConstString<CharT>
    {
        using ThisT = TConstStringImpl<CharT>;
        using BaseT = ConstArrayImpl<CharT>;
        using IConstStringT = IConstString<CharT>;
        using IConstIteratorT = IConstIterator<CharT>;
        using IConstBidirectionalIteratorT = IConstBidirectionalIterator<CharT>;

    public:
        using typename IConstStringT::CompareOptions;
        using typename IConstStringT::CompareResult;
        using typename IConstStringT::SearchOptions;
        using typename IConstStringT::SimpleCompareOptions;

    /// ----------------------------------------------------------------------------
    /// Compare
    protected:
        virtual CompareResult _CompareImpl(const CharT ch, SizeT chCount, CompareOptions options) const noexcept override final
        {
            _AssertIndexIsInBounds(options.index);

            options.range = min(options.range, _count - (options.index + 1));
            options.range = min(options.range, chCount);
            if (options.range == 0) return { 0, 0 };

            for (SizeT i = options.index; i < options.index + options.range; i++)
            {
                if (options.comparer.Compare(_array[options.index], ch) == false)
                    return { i - options.index, options.range };
            }

            return { options.range, options.range };
        }

        virtual CompareResult _CompareImpl(const IConstIteratorT& it, SizeT itLength, CompareOptions options) const noexcept override final
        {
            _AssertIndexIsInBounds(options.index);

            options.range = min(options.range, _count - options.index + 1);
            options.range = min(options.range, itLength);
            if (options.range == 0) return { 0, 0 };

            SizeT i = options.index;
            SizeT end = options.index + options.range;

            for (CharT ch : ITERATE(it))
            {
                if (i >= end) break;

                if (options.comparer.Compare(_array[i], ch) == false)
                {
                    return { i - options.index, options.range };
                }

                i++;
            }

            SizeT matchCount = i - options.index;
            return { matchCount, matchCount };
        }

    /// ----------------------------------------------------------------------------
    /// StartsWith
    protected:
        virtual bool _StartsWithImpl(const CharT ch, SizeT chCount, SimpleCompareOptions options) const noexcept override final
        {
            options.range = min(options.range, _count);

            if (chCount == 0) return false;
            if (chCount > options.range) return false;

            for (SizeT i = 0; i < chCount; i++)
            {
                if (options.comparer.Compare(_array[i], ch) == false)
                    return false;
            }

            return true;
        }

        /// If length of iterator is less than itLength, that is considered.
        virtual bool _StartsWithImpl(const IConstIteratorT& it, SizeT itLength, SimpleCompareOptions options) const noexcept override final
        {
            options.range = min(options.range, _count);

            if (itLength == 0) return false;
            if (options.range == 0) return false;

            SizeT i = 0;
            for (CharT ch : ITERATE(it))
            {
                if (i >= itLength) break;
                if (i >= options.range) return false;

                if (options.comparer.Compare(_array[i], ch) == false)
                {
                    return false;
                }

                i++;
            }

            return true;
        }

    /// ----------------------------------------------------------------------------
    /// EndsWith
    protected:
        virtual bool _EndsWithImpl(const CharT ch, SizeT chCount, SimpleCompareOptions options) const noexcept override final
        {
            options.range = min(options.range, _count);

            if (chCount == 0) return false;
            if (chCount > options.range) return false;

            for (SizeT i = options.range - chCount; i < options.range; i++)
            {
                if (options.comparer.Compare(_array[i], ch) == false)
                    return false;
            }

            return true;
        }

        virtual bool _EndsWithImpl(const IConstIteratorT& it, SizeT itLength, SimpleCompareOptions options) const noexcept override final
        {
            options.range = min(options.range, _count);

            if (itLength == NPOS)
            {
                itLength = 0;
                for (CharT ch : ITERATE(it))
                {
                    if (itLength > options.range) break;

                    itLength++;
                }

                it.Reset();
            }

            if (itLength == 0) return false;
            if (itLength > options.range) return false;

            SizeT i = options.range - itLength;
            for (CharT ch : ITERATE(it))
            {
                DEBUG_ASSERT(i >= options.range, "Iterator length (itLength) specified wrong.");

                if (options.comparer.Compare(_array[i], ch) == false)
                {
                    return false;
                }

                i++;
            }

            return true;
        }

        virtual bool _EndsWithImpl(const IConstBidirectionalIteratorT& it, SizeT itLength, SimpleCompareOptions options) const noexcept override final
        {
            options.range = min(options.range, _count);

            if (itLength == 0) return false;
            if (options.range == 0) return false;

            SizeT i = _count - 1;
            for (CharT ch : RITERATE(it))
            {
                SizeT steps = _count - 1 - i;
                if (steps >= itLength) break;
                if (steps >= options.range) return false;

                if (options.comparer.Compare(_array[i], ch) == false)
                {
                    return false;
                }

                i--;
            }

            return true;
        }

    /// ----------------------------------------------------------------------------
    /// FindFirst
    protected:
        virtual SizeT _FindFirstImpl(const CharT ch, SizeT chCount, SearchOptions options) const noexcept override final
        {
            if (_count == 0) return NPOS;
            options.offset = min(options.offset, _count - 1);
            options.range = min(options.range, _count - options.offset + 1);

            if (chCount > options.range) return NPOS;

            for (SizeT i = options.offset; i < options.offset + options.range - chCount; i++)
            {
                SizeT j = 0;
                for (; j < chCount; j++)
                {
                    if (options.comparer.Compare(_array[i + j], ch) == false)
                        break;
                }

                if (j == chCount) return i;
            }

            return NPOS;
        }

        virtual SizeT _FindFirstImpl(const IConstIteratorT& it, SizeT itLength, SearchOptions options) const noexcept override final
        {
            if (_count == 0) return NPOS;
            options.offset = min(options.offset, _count - 1);
            options.range = min(options.range, _count - options.offset + 1);

            SizeT itLengthFound = 0;
            SizeT endRange = options.offset + options.range;
            for (SizeT i = options.offset; i < endRange - itLengthFound; i++)
            {
                it.Reset();

                SizeT j = 0;
                bool matched = true;
                for (CharT ch : ITERATE(it))
                {
                    // we cannot move forward than itLength specified.
                    if (j == itLength) break;

                    // length of this iterator more than remaining range,
                    // thus we cannot contain query string in this.
                    if (i + j == endRange) return NPOS;

                    if (options.comparer.Compare(_array[i + j], ch) == false)
                    {
                        matched = false;
                        break;
                    }

                    j++;
                }

                if (matched) return i;
                if (itLengthFound < j) itLengthFound = j;
            }

            return NPOS;
        }

    /// ----------------------------------------------------------------------------
    /// FindLast
    protected:
        virtual SizeT _FindLastImpl(const CharT ch, SizeT chCount, SearchOptions options) const noexcept override final
        {
            if (_count == 0) return NPOS;
            options.offset = min(options.offset, _count - 1);
            options.range = min(options.range, _count - options.offset);
            chCount = min(chCount, options.range);

            SizeT index = NPOS;
            for (SizeT i = _count - options.offset - chCount; i >= 0; i--)
            {
                SizeT j = 0;
                for (; j < chCount; j++)
                {
                    if (options.comparer.Compare(_array[i + j], ch) == false)
                        break;
                }

                if (j == chCount) return i;
            }

            return index;
        }

        virtual SizeT _FindLastImpl(const IConstIteratorT& it, SizeT itLength, SearchOptions options) const noexcept override final
        {
            if (_count == 0) return NPOS;
            options.offset = min(options.offset, _count - 1);
            options.range = min(options.range, _count - options.offset + 1);

            SizeT endRange = options.offset + options.range;
            for (SizeT i = endRange; i > 0; i--)
            {
                SizeT range = endRange - i;
                SizeT j = 0;
                for (CharT ch : ITERATE(it))
                {
                    if (j == range) break;
                    if (j == itLength) break;

                    if (options.comparer.Compare(_array[i + j], ch) == false)
                        break;

                    j++;
                }

                if (j == range) return i;
            }

            return NPOS;
        }

    /// ----------------------------------------------------------------------------
    /// FindFirstAny
    protected:
        virtual SizeT _FindFirstAnyImpl(const CharT ch, SearchOptions options) const noexcept override final
        {
            if (_count == 0) return NPOS;
            options.offset = min(options.offset, _count - 1);
            options.range = min(options.range, _count - options.offset);

            for (SizeT i = options.offset; i < options.offset + options.range; i++)
            {
                if (options.comparer.Compare(_array[i], ch))
                    return i;
            }

            return NPOS;
        }

        virtual SizeT _FindFirstAnyImpl(const IConstIteratorT& it, SizeT itLength, SearchOptions options) const noexcept override final
        {
            if (_count == 0) return NPOS;
            options.offset = min(options.offset, _count - 1);
            options.range = min(options.range, _count - options.offset);

            for (SizeT i = options.offset; i < options.offset + options.range; i++)
            {
                for (CharT ch : ITERATE(it))
                {
                    if (options.comparer.Compare(_array[i], ch))
                        return i;
                }
            }

            return NPOS;
        }

    /// ----------------------------------------------------------------------------
    /// FindFirstNotAny
    protected:
        virtual SizeT _FindFirstNotAnyImpl(const CharT ch, SearchOptions options) const noexcept override final
        {
            if (_count == 0) return NPOS;
            options.offset = min(options.offset, _count - 1);
            options.range = min(options.range, _count - options.offset);

            for (SizeT i = options.offset; i < options.offset + options.range; i++)
            {
                if (options.comparer.Compare(_array[i], ch) == false)
                    return i;
            }

            return NPOS;
        }

        virtual SizeT _FindFirstNotAnyImpl(const IConstIteratorT& it, SizeT itLength, SearchOptions options) const noexcept override final
        {
            if (_count == 0) return NPOS;
            options.offset = min(options.offset, _count - 1);
            options.range = min(options.range, _count - options.offset);

            for (SizeT i = options.offset; i < options.offset + options.range; i++)
            {
                for (CharT ch : ITERATE(it))
                {
                    if (options.comparer.Compare(_array[i], ch))
                        return i;
                }
            }

            return NPOS;
        }

    /// ----------------------------------------------------------------------------
    /// FindLastAny
    protected:
        virtual SizeT _FindLastAnyImpl(const CharT ch, SearchOptions options) const noexcept override final
        {
            if (_count == 0) return NPOS;
            options.offset = min(options.offset, _count - 1);
            options.range = min(options.range, _count - options.offset);

            for (SizeT i = _count - options.offset; i > _count - options.offset - options.range; i--)
            {
                if (options.comparer.Compare(_array[i], ch))
                    return i;
            }

            return NPOS;
        }

        virtual SizeT _FindLastAnyImpl(const IConstIteratorT& it, SizeT itLength, SearchOptions options) const noexcept override final
        {
            if (_count == 0) return NPOS;
            options.offset = min(options.offset, _count - 1);
            options.range = min(options.range, _count - options.offset);

            for (SizeT i = _count - options.offset; i > _count - options.offset - options.range; i--)
            {
                for (CharT ch : ITERATE(it))
                {
                    if (options.comparer.Compare(_array[i], ch))
                        return i;
                }
            }

            return NPOS;
        }

    /// ----------------------------------------------------------------------------
    /// FindLastNotAny
    protected:
        virtual SizeT _FindLastNotAnyImpl(const CharT ch, SearchOptions options) const noexcept override final
        {
            if (_count == 0) return NPOS;
            options.offset = min(options.offset, _count - 1);
            options.range = min(options.range, _count - options.offset);

            for (SizeT i = _count - options.offset; i > _count - options.offset - options.range; i--)
            {
                if (options.comparer.Compare(_array[i], ch) == false)
                    return i;
            }

            return NPOS;
        }

        virtual SizeT _FindLastNotAnyImpl(const IConstIteratorT& it, SizeT itLength, SearchOptions options) const noexcept override final
        {
            if (_count == 0) return NPOS;
            options.offset = min(options.offset, _count - 1);
            options.range = min(options.range, _count - options.offset);

            for (SizeT i = _count - options.offset; i > _count - options.offset - options.range; i--)
            {
                for (CharT ch : ITERATE(it))
                {
                    if (options.comparer.Compare(_array[i], ch) == false)
                        return i;
                }
            }

            return NPOS;
        }

    protected:
        using BaseT::_AssertIndexIsInBounds;

    protected:
        using BaseT::_array;
        using BaseT::_count;
    };
}