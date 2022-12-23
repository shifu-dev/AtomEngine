#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/IForwardIterator.hpp"

namespace Atom
{
    namespace Internal
    {
        template <typename IteratorT>
        class ForLoopIterator
        {
            using ThisT = ForLoopIterator<IteratorT>;

        public:
            ForLoopIterator(IteratorT& it) noexcept:
                it(it) { }

        public:
            auto& operator * () noexcept
            {
                return *it;
            }

            const auto& operator * () const noexcept
            {
                return *it;
            }

            auto* operator -> () noexcept
            {
                return it.operator -> ();
            }

            const auto* operator -> () const noexcept
            {
                return it.operator -> ();
            }

            ThisT& operator ++ () noexcept
            {
                ++it;
                return *this;
            }

            ThisT& operator ++ (int) noexcept
            {
                ++it;
                return *this;
            }

            bool operator == (const IteratorT& other) const noexcept
            {
                return it == other;
            }

            bool operator != (const IteratorT& other) const noexcept
            {
                return it != other;
            }

            bool operator == (const ThisT& other) const noexcept
            {
                return it == other.it;
            }

            bool operator != (const ThisT& other) const noexcept
            {
                return it != other.it;
            }

        public:
            IteratorT& it;
        };

        template <typename IteratorT>
        class ForLoopIterable
        {
            constexpr static bool IsIteratorBox = IsSubClass<
                Internal::UniqueBoxIdentifier, IteratorT>;

            using ActualIteratorT = std::conditional_t<IsIteratorBox,
                decltype(((IteratorT*)nullptr)->operator * ()), IteratorT>;

            using StdIteratorT = Internal::ForLoopIterator<ActualIteratorT>;
            using ConstStdIteratorT = Internal::ForLoopIterator<ActualIteratorT>;

        public:
            ForLoopIterable(IteratorT& begin, IteratorT& end) noexcept:
                _begin(begin), _end(end) { }

            ForLoopIterable(IteratorT&& begin, IteratorT&& end) noexcept:
                _begin(move(begin)), _end(move(end)) { }

        public:
            // template <typename EnableIf<> = 0>
            // StdIteratorT begin() noexcept
            // {
            //     return _ToStdIterator(_begin);
            // }

            ConstStdIteratorT begin() const noexcept
            {
                return _ToStdIterator(_begin);
            }

            // template <typename EnableIf<> = 0>
            // StdIteratorT end() noexcept
            // {
            //     return _ToStdIterator(_end);
            // }

            ConstStdIteratorT end() const noexcept
            {
                return _ToStdIterator(_end);
            }

        protected:
            StdIteratorT _ToStdIterator(IteratorT& it) const noexcept
            {
                if constexpr (IsIteratorBox)
                {
                    return StdIteratorT(*it);
                }
                else
                {
                    return StdIteratorT(it);
                }
            }

        protected:
            IteratorT _begin;
            IteratorT _end;
        };
    }

    template <typename IteratorT>
    auto iterate(IteratorT& begin, IteratorT& end) noexcept
    {
        return Internal::ForLoopIterable<IteratorT>(begin, end);
    }

    template <typename IteratorT>
    auto iterate(IteratorT&& begin, IteratorT&& end) noexcept
    {
        return Internal::ForLoopIterable<IteratorT>(move(begin), move(end));
    }

    template <typename IterableT>
    auto iterate(const IterableT& iterable) noexcept
    {
        return iterate(iterable.Begin(), iterable.End());
    }
}