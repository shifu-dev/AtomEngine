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
        /// @brief type of value stored by this iterable
        using ValueTypeT = TValueType;

        /// @brief type to manage count
        using SizeT = umax;

        /// @brief iterator used by iterable to iterate through data
        /// @note Iterable uses IteratorPointer which holds a pointer to acutal iterable
        /// to provide interface like abilities
        using IteratorPointerT = IteratorPointer<TValueType>;

    public:
        IteratorPointerT begin() noexcept
        {
            return Iterable_begin();
        }

        IteratorPointerT end() noexcept
        {
            return Iterable_end();
        }

    protected:
        virtual IteratorPointerT Iterable_begin() noexcept abstract;
        virtual IteratorPointerT Iterable_end() noexcept abstract;
    };
}

template <typename TValueType>
using SSIterable = SSEngine::Iterable<TValueType>;