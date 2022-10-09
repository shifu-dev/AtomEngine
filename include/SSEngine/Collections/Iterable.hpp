#pragma once
#include "SSEngine/Core.hpp"
#include "SSEngine/Core/Callable.hpp"
#include "SSEngine/Memory.hpp"
#include "SSEngine/Collections/IteratorPointer.hpp"

namespace SSEngine
{
    /// @brief base abstract class to implement basic iterable functionality
    /// just by implementing from this class, 
    /// extended class will be able to be used in range based for loop
    /// and funtions expecting an iterable type
    ///
    /// @tparam TElement type of value hold by this iterable
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
    template <typename TElement>
    class Iterable
    {
    public:
        /// @brief type to manage count
        using SizeType = sizet;

        /// @brief type of value stored by this iterable
        using ElementType = TElement;

        /// @brief type used to compare elements, typically during sort
        using ComparerT = Comparer<ElementType>;

        /// @brief type used to compare elements, typically during find
        using EqualityComparerT = EqualityComparer<ElementType>;

        using DefaultEqualityComparerT = DefaultEqualityComparer<ElementType>;

        /// @brief iterator used by iterable to iterate through data
        /// @note Iterable uses IteratorPointer which holds a pointer to acutal iterable
        /// to provide interface like abilities
        using IteratorPointerT = ForwardIteratorPointer<TElement>;

        static constexpr SizeType NPOS = -1;

    public:

        template <typename TCallable>
        void ForEachT(const TCallable lref callable) const
        {
            ForEach(Callable<void(const ElementType lref)>::Create(callable));
        }

        template <typename TCallable>
        void ForEachT(const TCallable lref callable)
        {
            ForEach(Callable<void(ElementType lref)>::Create(callable));
        }

        virtual void ForEach(const Callable<void(const ElementType lref)> lref callback) const abstract;
        virtual void ForEach(const Callable<void(ElementType lref)> lref callback) abstract;

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
    class IteratorIterable : public virtual Iterable<typename TIterator::ElementType>
    {
    public:
        using IteratorT = TIterator;
        using AllocatorT = Allocator;
        using ElementType = typename IteratorT::ElementType;
        using IterableT = Iterable<ElementType>;
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
            return IteratorPointerT(Begin());
        }

        virtual IteratorPointerT Iterable_begin() noexcept override
        {
            return IteratorPointerT(Begin());
        }

        virtual const IteratorPointerT Iterable_end() const noexcept override
        {
            return IteratorPointerT(End());
        }

        virtual IteratorPointerT Iterable_end() noexcept override
        {
            return IteratorPointerT(End());
        }
    };
}

template <typename TElement>
using SSIterable = SSEngine::Iterable<TElement>;