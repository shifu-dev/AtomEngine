#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/IIterator.hpp"

namespace Atom
{
    namespace Internal
    {
        class ForLoopIteratorEnd { };
        
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

            bool operator == (const ForLoopIteratorEnd& other) const noexcept
            {
                return it.IsEnd();
            }

            bool operator != (const ForLoopIteratorEnd& other) const noexcept
            {
                return !it.IsEnd();
            }

        public:
            IteratorT& it;
        };

        template <typename IteratorT>
        class ForLoopIterable
        {
            using ForLoopIteratorT = Internal::ForLoopIterator<IteratorT>;
            using ConstForLoopIteratorT = Internal::ForLoopIterator<IteratorT>;

        public:
            ForLoopIterable(IteratorT&& begin) noexcept:
                _it(forward<IteratorT>(begin)) { }

        public:
            ForLoopIteratorT begin() noexcept
            {
                return ForLoopIteratorT(_it);
            }

            ConstForLoopIteratorT begin() const noexcept
            {
                return ConstForLoopIteratorT(_it);
            }

            ForLoopIteratorEnd end() const noexcept
            {
                return ForLoopIteratorEnd();
            }

        protected:
            IteratorT _it;
        };
    }

    template <typename IteratorT>
    auto ITERATE(IteratorT&& it) noexcept
    {
        return Internal::ForLoopIterable<IteratorT>(forward<IteratorT>(it));
    }

    template <typename BidirectionalIteratorT>
    auto RITERATE(BidirectionalIteratorT&& it) noexcept
    {
        return Internal::ForLoopIterable<BidirectionalIteratorT>(
            forward<BidirectionalIteratorT>(it));
    }
}