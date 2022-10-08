#pragma once
#include "SSEngine/Core.hpp"
#include "SSEngine/Memory.hpp"
#include "SSEngine/Collections/IteratorPointer.hpp"

namespace SSEngine
{
    /// @brief base abstract class to implement basic iterable functionality
    /// just by implementing from this class, 
    /// extended class will be able to be used in range based for loop
    /// and funtions expecting an iterable type
    ///
    /// @tparam TValueType type of value hold by this iterable
    ///
    /// @example
    /// void GetMeListOfNames(const Iterable<string> ref names)
    /// {
    ///     for (const auto ref name : names)
    ///     {
    ///         cout << "Hi " + name << endl;
    ///     }
    /// }
    ///
    template <typename TValueType>
    class Iterable
    {
    public:
        /// @brief type to manage count
        using SizeT = sizet;

        /// @brief type of value stored by this iterable
        using ValueTypeT = TValueType;

        /// @brief type used to compare elements, typically during sort
        using ComparerT = Comparer<ValueTypeT>;

        /// @brief type used to compare elements, typically during find
        using EqualityComparerT = EqualityComparer<ValueTypeT>;

        using DefaultEqualityComparerT = DefaultEqualityComparer<ValueTypeT>;

        /// @brief iterator used by iterable to iterate through data
        /// @note Iterable uses IteratorPointer which holds a pointer to acutal iterable
        /// to provide interface like abilities
        using IteratorPointerT = ForwardIteratorPointer<TValueType>;

        static constexpr SizeT NPOS = -1;

    public:
        IteratorPointerT Begin() noexcept
        {
            return Iterable_begin();
        }

        const IteratorPointerT Begin() const noexcept
        {
            return Iterable_begin();
        }

        IteratorPointerT End() noexcept
        {
            return Iterable_end();
        }

        const IteratorPointerT End() const noexcept
        {
            return Iterable_end();
        }

        IteratorPointerT begin() noexcept
        {
            return Iterable_begin();
        }

        const IteratorPointerT begin() const noexcept
        {
            return Iterable_begin();
        }

        IteratorPointerT end() noexcept
        {
            return Iterable_end();
        }

        const IteratorPointerT end() const noexcept
        {
            return Iterable_end();
        }

    protected:
        virtual IteratorPointerT Iterable_begin() noexcept abstract;
        virtual IteratorPointerT Iterable_end() noexcept abstract;

        virtual const IteratorPointerT Iterable_begin() const noexcept abstract;
        virtual const IteratorPointerT Iterable_end() const noexcept abstract;
    };

    /// @brief Iterable helper class
    /// @tparam TIterator 
    template <typename TIterator>
    class IteratorIterable : public virtual Iterable<typename TIterator::ValueTypeT>
    {
    public:
        using IteratorT = TIterator;
        using AllocatorT = Allocator;
        using ValueTypeT = typename IteratorT::ValueTypeT;
        using IterableT = Iterable<ValueTypeT>;
        using IteratorPointerT = typename IterableT::IteratorPointerT;

    public:
        virtual IteratorT Begin() noexcept abstract;
        virtual const IteratorT Begin() const noexcept abstract;

        virtual IteratorT End() noexcept abstract;
        virtual const IteratorT End() const noexcept abstract;

        IteratorT begin() noexcept { return Begin(); }
        const IteratorT begin() const noexcept { return Begin(); }

        IteratorT end() noexcept { return End(); }
        const IteratorT end() const noexcept { return End(); }

    protected:
        virtual const IteratorPointerT Iterable_begin() const noexcept override
        {
            return IteratorPointerT:: template Create<IteratorT>(Begin());
        }

        virtual IteratorPointerT Iterable_begin() noexcept override
        {
            return IteratorPointerT:: template Create<IteratorT>(Begin());
        }

        virtual const IteratorPointerT Iterable_end() const noexcept override
        {
            return IteratorPointerT:: template Create<IteratorT>(End());
        }

        virtual IteratorPointerT Iterable_end() noexcept override
        {
            return IteratorPointerT:: template Create<IteratorT>(End());
        }
    };
}

template <typename TValueType>
using SSIterable = SSEngine::Iterable<TValueType>;