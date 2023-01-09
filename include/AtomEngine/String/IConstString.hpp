#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/IConstArray.hpp"
#include "AtomEngine/Containers/IBidirectionalIterator.hpp"
#include "AtomEngine/Containers/IBidirectionalIterable.hpp"
#include "AtomEngine/String/StringIterator.hpp"

namespace Atom
{
    /// Interface for ReadOnly string.
    /// 
    /// @tparam CharT Type of character this string stores.
    template <typename CharT>
    interface IConstString:
        public virtual IConstArray<CharT>
    {
        using ThisT = IConstString<CharT>;

        using IConstIteratorT = IConstIterator<CharT>;
        using IConstBidirectionalIteratorT = IConstBidirectionalIterator<CharT>;
        using ConstArrayIteratorT = TConstArrayIterator<CharT>;
        using ConstStringIteratorT = TConstStringIterator<CharT>;

        using IConstIterableT = IConstIterable<CharT>;
        using IConstBidirectionalIterableT = IConstBidirectionalIterable<CharT>;
        using IConstCollectionT = IConstCollection<CharT>;

        using IEqualityComparerT = IEqualityComparer<CharT>;
        using DefaultEqualityComparerT = DefaultEqualityComparer<CharT>;

        using ConstIterableActionMakerT = TInvokableMaker<void(const IConstIteratorT&)>;

        static const CharT NullChar;

    public:
        struct CompareOptions
        {
            SizeT index;
            SizeT range = NPOS;
            const IEqualityComparerT& comparer = DefaultEqualityComparerT();
        };

        struct CompareResult
        {
            SizeT compared = 0;
            SizeT total = 0;

            constexpr operator bool() const noexcept
            {
                return total != 0 && compared == total;
            }
        };

        struct SimpleCompareOptions
        {
            SizeT range = NPOS;
            const IEqualityComparerT& comparer = DefaultEqualityComparerT();
        };

        struct SearchOptions
        {
            SizeT offset = 0;
            SizeT range = NPOS;
            const IEqualityComparerT& comparer = DefaultEqualityComparerT();
        };

    /// ----------------------------------------------------------------------------
    #pragma region Compare

    public:

        /// Compares string or character with this.
        /// 
        /// @param ch Character to compare.
        /// @param chCount Count of characters to compare.
        /// 
        /// @param str String to compare.
        /// @param strLength Length of string to compare.
        /// 
        /// @param begin Iterator to first character of string to compare.
        /// @param end Iterator to last character of string to compare.
        /// 
        /// @param it Iterator to first character of string to compare.
        /// @param itLength Length of the iterator to compare.
        /// 
        /// @param options.index Index of this string to compare.
        /// @param options.range Range from options.index of this string to compare.
        ///                      (default = NPOS).
        /// 
        /// @param options.comparer Comparer to compare two characters.
        ///                      (default = DefaultEqualityComparerT).
        /// 
        /// @throws OutOfBoundsException If options.index is out of bounds.
        /// 
        /// @exceptsafe Strong Exception Safety.
        /// 
        /// @{ ----------------------------------------------------------------------------

        CompareResult Compare(const CharT ch, CompareOptions options) const noexcept
        {
            return _CompareImpl(ch, 1, options);
        }

        CompareResult Compare(const CharT ch, SizeT chCount, CompareOptions options) const noexcept
        {
            return _CompareImpl(ch, chCount, options);
        }

        CompareResult Compare(const CharT* str, CompareOptions options) const noexcept
        {
            return _CompareImpl(ConstStringIteratorT(str), NPOS, options);
        }

        CompareResult Compare(const CharT* str, SizeT strLength, CompareOptions options) const noexcept
        {
            return _CompareImpl(ConstArrayIteratorT(str, strLength), strLength, options);
        }

        CompareResult Compare(const IConstIteratorT& it, CompareOptions options) const noexcept
        {
            return _CompareImpl(it, NPOS, options);
        }

        CompareResult Compare(const IConstIteratorT& it, SizeT itLength, CompareOptions options) const noexcept
        {
            return _CompareImpl(it, itLength, options);
        }

        CompareResult Compare(const IConstIterableT& str, CompareOptions options) const noexcept
        {
            CompareResult result;
            IterateT(str, [&](const IConstIteratorT& it)
                {
                    result = this->_CompareImpl(it, NPOS, options);
                });

            return result;
        }

        CompareResult Compare(const IConstIterableT& str, SizeT strLength, CompareOptions options) const noexcept
        {
            CompareResult result;
            IterateT(str, [&](const IConstIteratorT& it)
                {
                    result = this->_CompareImpl(it, strLength, options);
                });

            return result;
        }

        CompareResult Compare(const IConstCollectionT& str, CompareOptions options) const noexcept
        {
            CompareResult result;
            IterateT(str, [&](const IConstIteratorT& it)
                {
                    result = this->_CompareImpl(it, str.Count(), options);
                });

            return result;
        }

        CompareResult Compare(const IConstCollectionT& str, SizeT strLength, CompareOptions options) const noexcept
        {
            strLength = min(strLength, str.Count());

            CompareResult result;
            IterateT(str, [&](const IConstIteratorT& it)
                {
                    result = this->_CompareImpl(it, strLength, options);
                });

            return result;
        }

        /// @} ----------------------------------------------------------------------------

    protected:
        virtual CompareResult _CompareImpl(const CharT ch, SizeT chCount, CompareOptions options) const noexcept = 0;

        virtual CompareResult _CompareImpl(const IConstIteratorT& it, SizeT itLength, CompareOptions options) const noexcept = 0;

    #pragma endregion

    /// ----------------------------------------------------------------------------
    #pragma region StartsWith

    public:
        static const SimpleCompareOptions StartsWithDefaultOptions;

    public:
        bool StartsWith(const CharT ch, SimpleCompareOptions options = StartsWithDefaultOptions) const noexcept
        {
            return _StartsWithImpl(ch, 1, options);
        }

        bool StartsWith(const CharT ch, SizeT chCount, SimpleCompareOptions options = StartsWithDefaultOptions) const noexcept
        {
            return _StartsWithImpl(ch, chCount, options);
        }

        bool StartsWith(const CharT* str, SimpleCompareOptions options = StartsWithDefaultOptions) const noexcept
        {
            return _StartsWithImpl(ConstStringIteratorT(str), NPOS, options);
        }

        bool StartsWith(const CharT* str, SizeT strLength, SimpleCompareOptions options = StartsWithDefaultOptions) const noexcept
        {
            return _StartsWithImpl(ConstArrayIteratorT(str, strLength), strLength, options);
        }

        bool StartsWith(const IConstIteratorT& it, SimpleCompareOptions options = StartsWithDefaultOptions) const noexcept
        {
            return _StartsWithImpl(it, NPOS, options);
        }

        bool StartsWith(const IConstIteratorT& it, SizeT itLength, SimpleCompareOptions options = StartsWithDefaultOptions) const noexcept
        {
            return _StartsWithImpl(it, itLength, options);
        }

        bool StartsWith(const IConstIterableT& str, SimpleCompareOptions options = StartsWithDefaultOptions) const noexcept
        {
            bool result;
            IterateT(str, [&](const IConstIteratorT& it)
                {
                    result = this->_StartsWithImpl(it, NPOS, options);
                });

            return result;
        }

        bool StartsWith(const IConstIterableT& str, SizeT strLength, SimpleCompareOptions options = StartsWithDefaultOptions) const noexcept
        {
            bool result;
            IterateT(str, [&](const IConstIteratorT& it)
                {
                    result = this->_StartsWithImpl(it, strLength, options);
                });

            return result;
        }

        bool StartsWith(const IConstCollectionT& str, SimpleCompareOptions options = StartsWithDefaultOptions) const noexcept
        {
            bool result;
            IterateT(str, [&](const IConstIteratorT& it)
                {
                    result = this->_StartsWithImpl(it, str.Count(), options);
                });

            return result;
        }

        bool StartsWith(const IConstCollectionT& str, SizeT strLength, SimpleCompareOptions options = StartsWithDefaultOptions) const noexcept
        {
            strLength = min(strLength, str.Count());

            bool result;
            IterateT(str, [&](const IConstIteratorT& it)
                {
                    result = this->_StartsWithImpl(it, strLength, options);
                });

            return result;
        }

        /// @} ----------------------------------------------------------------------------

    protected:
        virtual bool _StartsWithImpl(const CharT ch, SizeT chCount, SimpleCompareOptions options) const noexcept = 0;

        virtual bool _StartsWithImpl(const IConstIteratorT& it, SizeT itLength, SimpleCompareOptions options) const noexcept = 0;

    #pragma endregion

    /// ----------------------------------------------------------------------------
    #pragma region EndsWith

    public:
        static const SimpleCompareOptions EndsWithDefaultOptions;

    public:
        bool EndsWith(const CharT ch, SimpleCompareOptions options = EndsWithDefaultOptions) const noexcept
        {
            return _EndsWithImpl(ch, 1, options);
        }

        bool EndsWith(const CharT ch, SizeT chCount, SimpleCompareOptions options = EndsWithDefaultOptions) const noexcept
        {
            return _EndsWithImpl(ch, chCount, options);
        }

        bool EndsWith(const CharT* str, SimpleCompareOptions options = EndsWithDefaultOptions) const noexcept
        {
            return _EndsWithImpl(ConstStringIteratorT(str), NPOS, options);
        }

        bool EndsWith(const CharT* str, SizeT strLength, SimpleCompareOptions options = EndsWithDefaultOptions) const noexcept
        {
            return _EndsWithImpl(ConstArrayIteratorT(str, strLength), strLength, options);
        }

        bool EndsWith(const IConstIteratorT& it, SimpleCompareOptions options = EndsWithDefaultOptions) const noexcept
        {
            return _EndsWithImpl(it, NPOS, options);
        }

        bool EndsWith(const IConstIteratorT& it, SizeT itLength, SimpleCompareOptions options = EndsWithDefaultOptions) const noexcept
        {
            return _EndsWithImpl(it, itLength, options);
        }

        bool EndsWith(const IConstIterableT& str, SimpleCompareOptions options = EndsWithDefaultOptions) const noexcept
        {
            bool result;
            IterateT(str, [&](const IConstIteratorT& it)
                {
                    result = this->_EndsWithImpl(it, NPOS, options);
                });

            return result;
        }

        bool EndsWith(const IConstIterableT& str, SizeT strLength, SimpleCompareOptions options = EndsWithDefaultOptions) const noexcept
        {
            bool result;
            IterateT(str, [&](const IConstIteratorT& it)
                {
                    result = this->_EndsWithImpl(it, strLength, options);
                });

            return result;
        }

        bool EndsWith(const IConstCollectionT& str, SimpleCompareOptions options = EndsWithDefaultOptions) const noexcept
        {
            bool result;
            IterateT(str, [&](const IConstIteratorT& it)
                {
                    result = this->_EndsWithImpl(it, str.Count(), options);
                });

            return result;
        }

        bool EndsWith(const IConstCollectionT& str, SizeT strLength, SimpleCompareOptions options = EndsWithDefaultOptions) const noexcept
        {
            strLength = min(strLength, str.Count());

            bool result;
            IterateT(str, [&](const IConstIteratorT& it)
                {
                    result = this->_EndsWithImpl(it, strLength, options);
                });

            return result;
        }

        bool EndsWith(const IConstBidirectionalIteratorT& it, SimpleCompareOptions options = EndsWithDefaultOptions) const noexcept
        {
            return _EndsWithImpl(it, NPOS, options);
        }

        bool EndsWith(const IConstBidirectionalIteratorT& it, SizeT itLength, SimpleCompareOptions options = EndsWithDefaultOptions) const noexcept
        {
            return _EndsWithImpl(it, itLength, options);
        }

        bool EndsWith(const IConstBidirectionalIterableT& str, SimpleCompareOptions options = EndsWithDefaultOptions) const noexcept
        {
            bool result;
            RevIterateT(str, [&](const IConstBidirectionalIteratorT& it)
                {
                    result = this->_EndsWithImpl(it, NPOS, options);
                });

            return result;
        }

        bool EndsWith(const IConstBidirectionalIterableT& str, SizeT strLength, SimpleCompareOptions options = EndsWithDefaultOptions) const noexcept
        {
            bool result;
            RevIterateT(str, [&](const IConstBidirectionalIteratorT& it)
                {
                    result = this->_EndsWithImpl(it, strLength, options);
                });

            return result;
        }

        /// @} ----------------------------------------------------------------------------

    protected:
        virtual bool _EndsWithImpl(const CharT ch, SizeT chCount, SimpleCompareOptions options) const noexcept = 0;

        virtual bool _EndsWithImpl(const IConstIteratorT& it, SizeT itLength, SimpleCompareOptions options) const noexcept = 0;

        virtual bool _EndsWithImpl(const IConstBidirectionalIteratorT& it, SizeT itLength, SimpleCompareOptions options) const noexcept = 0;

    #pragma endregion

    /// ----------------------------------------------------------------------------
    #pragma region FindFirst

    public:
        static const SearchOptions FindFirstDefaultSearchOptions;

    public:
        SizeT FindFirst(const CharT ch, SearchOptions options = FindFirstDefaultSearchOptions) const noexcept
        {
            return _FindFirstImpl(ch, 1, options);
        }

        SizeT FindFirst(const CharT ch, SizeT chCount, SearchOptions options = FindFirstDefaultSearchOptions) const noexcept
        {
            return _FindFirstImpl(ch, chCount, options);
        }

        SizeT FindFirst(const CharT* str, SearchOptions options = FindFirstDefaultSearchOptions) const noexcept
        {
            return _FindFirstImpl(ConstStringIteratorT(str), NPOS, options);
        }

        SizeT FindFirst(const CharT* str, SizeT strLength, SearchOptions options = FindFirstDefaultSearchOptions) const noexcept
        {
            return _FindFirstImpl(ConstArrayIteratorT(str, strLength), strLength, options);
        }

        SizeT FindFirst(const IConstIteratorT& it, SearchOptions options = FindFirstDefaultSearchOptions) const noexcept
        {
            return _FindFirstImpl(it, NPOS, options);
        }

        SizeT FindFirst(const IConstIteratorT& it, SizeT itLength, SearchOptions options = FindFirstDefaultSearchOptions) const noexcept
        {
            return _FindFirstImpl(it, itLength, options);
        }

        SizeT FindFirst(const IConstIterableT& str, SearchOptions options = FindFirstDefaultSearchOptions) const noexcept
        {
            SizeT result;
            IterateT(str, [&](const IConstIteratorT& it)
                {
                    result = this->_FindFirstImpl(it, NPOS, options);
                });

            return result;
        }

        SizeT FindFirst(const IConstIterableT& str, SizeT strLength, SearchOptions options = FindFirstDefaultSearchOptions) const noexcept
        {
            SizeT result;
            IterateT(str, [&](const IConstIteratorT& it)
                {
                    result = this->_FindFirstImpl(it, strLength, options);
                });

            return result;
        }

        SizeT FindFirst(const IConstCollectionT& str, SearchOptions options = FindFirstDefaultSearchOptions) const noexcept
        {
            SizeT result;
            IterateT(str, [&](const IConstIteratorT& it)
                {
                    result = this->_FindFirstImpl(it, str.Count(), options);
                });

            return result;
        }

        SizeT FindFirst(const IConstCollectionT& str, SizeT strLength, SearchOptions options = FindFirstDefaultSearchOptions) const noexcept
        {
            strLength = min(strLength, str.Count());

            SizeT result;
            IterateT(str, [&](const IConstIteratorT& it)
                {
                    result = this->_FindFirstImpl(it, strLength, options);
                });

            return result;
        }

    protected:
        virtual SizeT _FindFirstImpl(const CharT ch, SizeT chCount, SearchOptions options) const noexcept = 0;

        virtual SizeT _FindFirstImpl(const IConstIteratorT& it, SizeT itLength, SearchOptions options) const noexcept = 0;

    #pragma endregion

    /// ----------------------------------------------------------------------------
    #pragma region FindLast

    public:
        static const SearchOptions FindLastDefaultSearchOptions;

    public:
        SizeT FindLast(const CharT ch, SearchOptions options = FindLastDefaultSearchOptions) const noexcept
        {
            return _FindLastImpl(ch, 1, options);
        }

        SizeT FindLast(const CharT ch, SizeT chCount, SearchOptions options = FindLastDefaultSearchOptions) const noexcept
        {
            return _FindLastImpl(ch, chCount, options);
        }

        SizeT FindLast(const CharT* str, SearchOptions options = FindLastDefaultSearchOptions) const noexcept
        {
            return _FindLastImpl(ConstStringIteratorT(str), NPOS, options);
        }

        SizeT FindLast(const CharT* str, SizeT strLength, SearchOptions options = FindLastDefaultSearchOptions) const noexcept
        {
            return _FindLastImpl(ConstArrayIteratorT(str, strLength), strLength, options);
        }

        SizeT FindLast(const IConstIteratorT& it, SearchOptions options = FindLastDefaultSearchOptions) const noexcept
        {
            return _FindLastImpl(it, NPOS, options);
        }

        SizeT FindLast(const IConstIteratorT& it, SizeT itLength, SearchOptions options = FindLastDefaultSearchOptions) const noexcept
        {
            return _FindLastImpl(it, itLength, options);
        }

        SizeT FindLast(const IConstIterableT& str, SearchOptions options = FindLastDefaultSearchOptions) const noexcept
        {
            SizeT result;
            IterateT(str, [&](const IConstIteratorT& it)
                {
                    result = this->_FindLastImpl(it, NPOS, options);
                });

            return result;
        }

        SizeT FindLast(const IConstIterableT& str, SizeT strLength, SearchOptions options = FindLastDefaultSearchOptions) const noexcept
        {
            SizeT result;
            IterateT(str, [&](const IConstIteratorT& it)
                {
                    result = this->_FindLastImpl(it, strLength, options);
                });

            return result;
        }

        SizeT FindLast(const IConstCollectionT& str, SearchOptions options = FindLastDefaultSearchOptions) const noexcept
        {
            SizeT result;
            IterateT(str, [&](const IConstIteratorT& it)
                {
                    result = this->_FindLastImpl(it, str.Count(), options);
                });

            return result;
        }

        SizeT FindLast(const IConstCollectionT& str, SizeT strLength, SearchOptions options = FindLastDefaultSearchOptions) const noexcept
        {
            strLength = min(strLength, str.Count());

            SizeT result;
            IterateT(str, [&](const IConstIteratorT& it)
                {
                    result = this->_FindLastImpl(it, strLength, options);
                });

            return result;
        }

    protected:
        virtual SizeT _FindLastImpl(const CharT ch, SizeT chCount, SearchOptions options) const noexcept = 0;

        virtual SizeT _FindLastImpl(const IConstIteratorT& it, SizeT itLength, SearchOptions options) const noexcept = 0;

    #pragma endregion

    /// ----------------------------------------------------------------------------
    #pragma region FindFirstAny

    public:
        static const SearchOptions FindFirstAnyDefaultSearchOptions;

    public:
        SizeT FindFirstAny(const CharT ch, SearchOptions options = FindFirstAnyDefaultSearchOptions) const noexcept
        {
            return _FindFirstAnyImpl(ch, 1, options);
        }

        SizeT FindFirstAny(const CharT* str, SearchOptions options = FindFirstAnyDefaultSearchOptions) const noexcept
        {
            return _FindFirstAnyImpl(ConstStringIteratorT(str), NPOS, options);
        }

        SizeT FindFirstAny(const CharT* str, SizeT strLength, SearchOptions options = FindFirstAnyDefaultSearchOptions) const noexcept
        {
            return _FindFirstAnyImpl(ConstArrayIteratorT(str, strLength), strLength, options);
        }

        SizeT FindFirstAny(const IConstIteratorT& it, SearchOptions options = FindFirstAnyDefaultSearchOptions) const noexcept
        {
            return _FindFirstAnyImpl(it, NPOS, options);
        }

        SizeT FindFirstAny(const IConstIteratorT& it, SizeT itLength, SearchOptions options = FindFirstAnyDefaultSearchOptions) const noexcept
        {
            return _FindFirstAnyImpl(it, itLength, options);
        }

        SizeT FindFirstAny(const IConstIterableT& str, SearchOptions options = FindFirstAnyDefaultSearchOptions) const noexcept
        {
            SizeT result;
            IterateT(str, [&](const IConstIteratorT& it)
                {
                    result = this->_FindFirstAnyImpl(it, NPOS, options);
                });

            return result;
        }

        SizeT FindFirstAny(const IConstIterableT& str, SizeT strLength, SearchOptions options = FindFirstAnyDefaultSearchOptions) const noexcept
        {
            SizeT result;
            IterateT(str, [&](const IConstIteratorT& it)
                {
                    result = this->_FindFirstAnyImpl(it, strLength, options);
                });

            return result;
        }

        SizeT FindFirstAny(const IConstCollectionT& str, SearchOptions options = FindFirstAnyDefaultSearchOptions) const noexcept
        {
            SizeT result;
            IterateT(str, [&](const IConstIteratorT& it)
                {
                    result = this->_FindFirstAnyImpl(it, str.Count(), options);
                });

            return result;
        }

        SizeT FindFirstAny(const IConstCollectionT& str, SizeT strLength, SearchOptions options = FindFirstAnyDefaultSearchOptions) const noexcept
        {
            strLength = min(strLength, str.Count());

            SizeT result;
            IterateT(str, [&](const IConstIteratorT& it)
                {
                    result = this->_FindFirstAnyImpl(it, strLength, options);
                });

            return result;
        }

    protected:
        virtual SizeT _FindFirstAnyImpl(const CharT ch, SearchOptions options) const noexcept = 0;

        virtual SizeT _FindFirstAnyImpl(const IConstIteratorT& it, SizeT itLength, SearchOptions options) const noexcept = 0;

    #pragma endregion

    /// ----------------------------------------------------------------------------
    #pragma region FindFirstNotAny

    public:
        static const SearchOptions FindFirstNotAnyDefaultSearchOptions;

    public:
        SizeT FindFirstNotAny(const CharT ch, SearchOptions options = FindFirstNotAnyDefaultSearchOptions) const noexcept
        {
            return _FindFirstNotAnyImpl(ch, 1, options);
        }

        SizeT FindFirstNotAny(const CharT* str, SearchOptions options = FindFirstNotAnyDefaultSearchOptions) const noexcept
        {
            return _FindFirstNotAnyImpl(ConstStringIteratorT(str), NPOS, options);
        }

        SizeT FindFirstNotAny(const CharT* str, SizeT strLength, SearchOptions options = FindFirstNotAnyDefaultSearchOptions) const noexcept
        {
            return _FindFirstNotAnyImpl(ConstArrayIteratorT(str, strLength), strLength, options);
        }

        SizeT FindFirstNotAny(const IConstIteratorT& it, SearchOptions options = FindFirstNotAnyDefaultSearchOptions) const noexcept
        {
            return _FindFirstNotAnyImpl(it, NPOS, options);
        }

        SizeT FindFirstNotAny(const IConstIteratorT& it, SizeT itLength, SearchOptions options = FindFirstNotAnyDefaultSearchOptions) const noexcept
        {
            return _FindFirstNotAnyImpl(it, itLength, options);
        }

        SizeT FindFirstNotAny(const IConstIterableT& str, SearchOptions options = FindFirstNotAnyDefaultSearchOptions) const noexcept
        {
            SizeT result;
            IterateT(str, [&](const IConstIteratorT& it)
                {
                    result = this->_FindFirstNotAnyImpl(it, NPOS, options);
                });

            return result;
        }

        SizeT FindFirstNotAny(const IConstIterableT& str, SizeT strLength, SearchOptions options = FindFirstNotAnyDefaultSearchOptions) const noexcept
        {
            SizeT result;
            IterateT(str, [&](const IConstIteratorT& it)
                {
                    result = this->_FindFirstNotAnyImpl(it, strLength, options);
                });

            return result;
        }

        SizeT FindFirstNotAny(const IConstCollectionT& str, SearchOptions options = FindFirstNotAnyDefaultSearchOptions) const noexcept
        {
            SizeT result;
            IterateT(str, [&](const IConstIteratorT& it)
                {
                    result = this->_FindFirstNotAnyImpl(it, str.Count(), options);
                });

            return result;
        }

        SizeT FindFirstNotAny(const IConstCollectionT& str, SizeT strLength, SearchOptions options = FindFirstNotAnyDefaultSearchOptions) const noexcept
        {
            strLength = min(strLength, str.Count());

            SizeT result;
            IterateT(str, [&](const IConstIteratorT& it)
                {
                    result = this->_FindFirstNotAnyImpl(it, strLength, options);
                });

            return result;
        }

    protected:
        virtual SizeT _FindFirstNotAnyImpl(const CharT ch, SearchOptions options) const noexcept = 0;

        virtual SizeT _FindFirstNotAnyImpl(const IConstIteratorT& str, SizeT strLength, SearchOptions options) const noexcept = 0;

    #pragma endregion

    /// ----------------------------------------------------------------------------
    #pragma region FindLastAny

    public:
        static const SearchOptions FindLastAnyDefaultSearchOptions;

    public:
        SizeT FindLastAny(const CharT ch, SearchOptions options = FindLastAnyDefaultSearchOptions) const noexcept
        {
            return _FindLastAnyImpl(ch, 1, options);
        }

        SizeT FindLastAny(const CharT* str, SearchOptions options = FindLastAnyDefaultSearchOptions) const noexcept
        {
            return _FindLastAnyImpl(ConstStringIteratorT(str), NPOS, options);
        }

        SizeT FindLastAny(const CharT* str, SizeT strLength, SearchOptions options = FindLastAnyDefaultSearchOptions) const noexcept
        {
            return _FindLastAnyImpl(ConstArrayIteratorT(str, strLength), strLength, options);
        }

        SizeT FindLastAny(const IConstIteratorT& it, SearchOptions options = FindLastAnyDefaultSearchOptions) const noexcept
        {
            return _FindLastAnyImpl(it, NPOS, options);
        }

        SizeT FindLastAny(const IConstIteratorT& it, SizeT itLength, SearchOptions options = FindLastAnyDefaultSearchOptions) const noexcept
        {
            return _FindLastAnyImpl(it, itLength, options);
        }

        SizeT FindLastAny(const IConstIterableT& str, SearchOptions options = FindLastAnyDefaultSearchOptions) const noexcept
        {
            SizeT result;
            IterateT(str, [&](const IConstIteratorT& it)
                {
                    result = this->_FindLastAnyImpl(it, NPOS, options);
                });

            return result;
        }

        SizeT FindLastAny(const IConstIterableT& str, SizeT strLength, SearchOptions options = FindLastAnyDefaultSearchOptions) const noexcept
        {
            SizeT result;
            IterateT(str, [&](const IConstIteratorT& it)
                {
                    result = this->_FindLastAnyImpl(it, strLength, options);
                });

            return result;
        }

        SizeT FindLastAny(const IConstCollectionT& str, SearchOptions options = FindLastAnyDefaultSearchOptions) const noexcept
        {
            SizeT result;
            IterateT(str, [&](const IConstIteratorT& it)
                {
                    result = this->_FindLastAnyImpl(it, str.Count(), options);
                });

            return result;
        }

        SizeT FindLastAny(const IConstCollectionT& str, SizeT strLength, SearchOptions options = FindLastAnyDefaultSearchOptions) const noexcept
        {
            strLength = min(strLength, str.Count());

            SizeT result;
            IterateT(str, [&](const IConstIteratorT& it)
                {
                    result = this->_FindLastAnyImpl(it, strLength, options);
                });

            return result;
        }

    protected:
        virtual SizeT _FindLastAnyImpl(const CharT ch, SearchOptions options) const noexcept = 0;

        virtual SizeT _FindLastAnyImpl(const IConstIteratorT& str, SizeT strLength, SearchOptions options) const noexcept = 0;

    #pragma endregion

    /// ----------------------------------------------------------------------------
    #pragma region FindLastNotAny

    public:
        static const SearchOptions FindLastNotDefaultSearchOptions;

    public:
        SizeT FindLastNotAny(const CharT ch, SearchOptions options = FindLastNotDefaultSearchOptions) const noexcept
        {
            return _FindLastNotAnyImpl(ch, 1, options);
        }

        SizeT FindLastNotAny(const CharT* str, SearchOptions options = FindLastNotDefaultSearchOptions) const noexcept
        {
            return _FindLastNotAnyImpl(ConstStringIteratorT(str), NPOS, options);
        }

        SizeT FindLastNotAny(const CharT* str, SizeT strLength, SearchOptions options = FindLastNotDefaultSearchOptions) const noexcept
        {
            return _FindLastNotAnyImpl(ConstArrayIteratorT(str, strLength), strLength, options);
        }

        SizeT FindLastNotAny(const IConstIteratorT& it, SearchOptions options = FindLastNotDefaultSearchOptions) const noexcept
        {
            return _FindLastNotAnyImpl(it, NPOS, options);
        }

        SizeT FindLastNotAny(const IConstIteratorT& it, SizeT itLength, SearchOptions options = FindLastNotDefaultSearchOptions) const noexcept
        {
            return _FindLastNotAnyImpl(it, itLength, options);
        }

        SizeT FindLastNotAny(const IConstIterableT& str, SearchOptions options = FindLastNotDefaultSearchOptions) const noexcept
        {
            SizeT result;
            IterateT(str, [&](const IConstIteratorT& it)
                {
                    result = this->_FindLastNotAnyImpl(it, NPOS, options);
                });

            return result;
        }

        SizeT FindLastNotAny(const IConstIterableT& str, SizeT strLength, SearchOptions options = FindLastNotDefaultSearchOptions) const noexcept
        {
            SizeT result;
            IterateT(str, [&](const IConstIteratorT& it)
                {
                    result = this->_FindLastNotAnyImpl(it, strLength, options);
                });

            return result;
        }

        SizeT FindLastNotAny(const IConstCollectionT& str, SearchOptions options = FindLastNotDefaultSearchOptions) const noexcept
        {
            SizeT result;
            IterateT(str, [&](const IConstIteratorT& it)
                {
                    result = this->_FindLastNotAnyImpl(it, str.Count(), options);
                });

            return result;
        }

        SizeT FindLastNotAny(const IConstCollectionT& str, SizeT strLength, SearchOptions options = FindLastNotDefaultSearchOptions) const noexcept
        {
            strLength = min(strLength, str.Count());

            SizeT result;
            IterateT(str, [&](const IConstIteratorT& it)
                {
                    result = this->_FindLastNotAnyImpl(it, strLength, options);
                });

            return result;
        }

    protected:
        virtual SizeT _FindLastNotAnyImpl(const CharT ch, SearchOptions options) const noexcept = 0;

        virtual SizeT _FindLastNotAnyImpl(const IConstIteratorT& str, SizeT strLength, SearchOptions options) const noexcept = 0;

    #pragma endregion

    /// ----------------------------------------------------------------------------
    #pragma region Contains

    public:
        static const SearchOptions ContainsDefaultSearchOptions;

    public:
        bool Contains(const CharT ch, SearchOptions options = ContainsDefaultSearchOptions) const noexcept
        {
            return FindFirst(ch, options) != NPOS;
        }
        
        bool Contains(const CharT ch, SizeT chCount, SearchOptions options = ContainsDefaultSearchOptions) const noexcept
        {
            return FindFirst(ch, chCount, options) != NPOS;
        }
        
        bool Contains(const CharT* str, SearchOptions options = ContainsDefaultSearchOptions) const noexcept
        {
            return FindFirst(str, options) != NPOS;
        }
        
        bool Contains(const CharT* str, SizeT strLength, SearchOptions options = ContainsDefaultSearchOptions) const noexcept
        {
            return FindFirst(str, strLength, options) != NPOS;
        }
        
        bool Contains(const IConstIteratorT& it, SearchOptions options = ContainsDefaultSearchOptions) const noexcept
        {
            return FindFirst(it, options) != NPOS;
        }
        
        bool Contains(const IConstIteratorT& it, SizeT itLength, SearchOptions options = ContainsDefaultSearchOptions) const noexcept
        {
            return FindFirst(it, itLength, options) != NPOS;
        }
        
        bool Contains(const IConstIterableT& str, SearchOptions options = ContainsDefaultSearchOptions) const noexcept
        {
            return FindFirst(str, options) != NPOS;
        }
        
        bool Contains(const IConstIterableT& str, SizeT strLength, SearchOptions options = ContainsDefaultSearchOptions) const noexcept
        {
            return FindFirst(str, strLength, options) != NPOS;
        }
        
        bool Contains(const IConstCollectionT& str, SearchOptions options = ContainsDefaultSearchOptions) const noexcept
        {
            return FindFirst(str, options) != NPOS;
        }
        
        bool Contains(const IConstCollectionT& str, SizeT strLength, SearchOptions options = ContainsDefaultSearchOptions) const noexcept
        {
            return FindFirst(str, strLength, options) != NPOS;
        }
        
    #pragma endregion

    protected:
        template <typename Invokable>
        void IterateT(const IConstIterableT& iterable, Invokable&& invokable)
        {
            iterable.Iterate(TInvokableMaker<void(const IConstIteratorT& it)>
                ::Make(forward<Invokable>(invokable)));
        }

        template <typename Invokable>
        void RevIterateT(const IConstBidirectionalIterableT& iterable, Invokable&& invokable)
        {
            iterable.Iterate(TInvokableMaker<void(const IConstBidirectionalIteratorT& it)>
                ::Make(forward<Invokable>(invokable)));
        }
    };

    template <typename CharT>
    inline const CharT IConstString<CharT>::NullChar = '\0';

    template <typename CharT>
    inline const IConstString<CharT>::SimpleCompareOptions
        IConstString<CharT>::StartsWithDefaultOptions = { };

    template <typename CharT>
    inline const IConstString<CharT>::SimpleCompareOptions
        IConstString<CharT>::EndsWithDefaultOptions = { };

    template <typename CharT>
    inline const IConstString<CharT>::SearchOptions
        IConstString<CharT>::FindFirstAnyDefaultSearchOptions = { };

    template <typename CharT>
    inline const IConstString<CharT>::SearchOptions
        IConstString<CharT>::FindLastAnyDefaultSearchOptions = { };

    template <typename CharT>
    inline const IConstString<CharT>::SearchOptions
        IConstString<CharT>::ContainsDefaultSearchOptions = { };
}