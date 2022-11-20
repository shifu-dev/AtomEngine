#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Memory/Core.hpp"

namespace Atom
{
    /// Base type used to allocate and deallocate memory.
    class Allocator
    {
        mpublic constexpr Allocator() = default;
        mpublic constexpr Allocator(const Allocator ref other) = default;
        mpublic constexpr Allocator(Allocator rref other) = default;
        mpublic constexpr Allocator ref operator =(const Allocator ref other) = default;
        mpublic constexpr Allocator ref operator =(Allocator rref other) = default;

        /// ----------------------------------------------------------------------------
        /// Allocates memory and Constructs an object with given args.
        /// 
        /// @tparam TType Type of object to create.
        /// @tparam TArgs... Type of args used to create the object.
        /// @param args... Args used to construct the object.
        /// @return Ptr to the object.
        /// 
        /// @note
        /// - Calls \p{ConstructMultiple(count: 1, args);}
        /// 
        /// @todo
        /// - Add exception specifications.
        mpublic template <typename TType, typename... TArgs>
            TType ptr Construct(TArgs ref... args);

        /// ----------------------------------------------------------------------------
        /// Allocates memory and Constructs an array of object,
        /// each object is constructed with given args.
        /// 
        /// @tparam TType Type of objects to create.
        /// @tparam TArgs... Type of args used to create objects.
        /// @param args... Args used to construct objects.
        /// @param count Count of objects to create.
        /// @return Ptr to the array of objects.
        /// 
        /// @todo
        /// - Add exception specifications.
        mpublic template <typename TType, typename... TArgs>
            TType ptr ConstructMultiple(const sizet count, TArgs ref... args);

        /// ----------------------------------------------------------------------------
        /// Destructs object and deallocates memory.
        /// 
        /// @tparam TType Type of object to destruct.
        /// @param src Ptr to the object to destruct.
        /// @param count Count of objects to destruct if ptr is an array.
        /// 
        /// @todo
        /// - Add exception specifications.
        mpublic template <typename TType>
            void Destruct(TType ptr src, const sizet count = 1);

        /// ----------------------------------------------------------------------------
        /// Allocates memory according to the sizeof(TType)
        /// @tparam TType Type of object to allocate memory.
        /// @param count Count of objects to allocate memory for.
        /// @return Ptr to first block of allocated memory.
        /// 
        /// @note
        /// - This function does not counstruct's the object,
        /// - TType is used only as a reference for size.
        /// 
        /// @todo
        /// - Add exception specifications.
        mpublic template <typename TType>
            TType ptr Allocate(const sizet count = 1);

        /// ----------------------------------------------------------------------------
        /// Deallocates memory according to the sizeof(TType)
        /// @tparam TType Type of object to deallocate memory.
        /// @param src Ptr to the memory block.
        /// @param count Count of objects to deallocate memory for.
        /// 
        /// @note
        /// - Does not destructs the object.
        /// - TType is only used as a reference for size.
        /// 
        /// @todo
        /// - Add exception specifications.
        mpublic template <typename TType>
            void Deallocate(TType ptr src, const sizet count = 1);

        /// ----------------------------------------------------------------------------
        /// Base abstract function used to allocate memory.
        /// @param count Count of memory ( @ref memt objects ) to allocate.
        /// @param clear If true, initializes memory with 0.
        /// @return Ptr to the memory block.
        /// 
        /// @note
        /// - This is the base underlying function used to allocate memory.
        /// 
        /// @todo
        /// - Add exception specifications.
        mpublic virtual memptr AllocateRaw(const sizet count, bool clear = true) abstract;

        /// ----------------------------------------------------------------------------
        /// Base abstract function used to deallocate memory.
        /// @param src Ptr to memory to deallocate.
        /// @param count Count of memory to deallcate.
        /// 
        /// @note
        /// - Support for partial memory deallocation is implementation dependent.
        /// <b>Example of Partial memory deallocation,</b>
        /// Allocate 5 blocks memory and deallocate any 2 blocks,
        /// the rest 3 blocks of memory are still usable.
        /// 
        /// @todo
        /// - Add exception specifications.
        /// - Move Partial Deallocation Concept to concepts section.
        mpublic virtual void DeallocateRaw(memptr src, const sizet count) abstract;
    };

    template <typename TType, typename... TArgs>
    inline TType ptr Allocator::Construct(TArgs ref... args)
    {
        return ConstructMultiple<TType>(1, forward<TArgs>(args)...);
    }

    template <typename TType, typename... TArgs>
    inline TType ptr Allocator::ConstructMultiple(const sizet count, TArgs ref... args)
    {
        TType ptr src = Allocate<TType>(count);

        if (src isnot null)
        {
            for (sizet i = 0; i < count; i++)
            {
                new(src + i) TType(forward<TArgs>(args)...);
            }
        }

        return src;
    }

    template <typename TType>
    inline void Allocator::Destruct(TType ptr src, const sizet count)
    {
        if (src isnot null)
        {
            for (sizet i = 0; i < count; i++)
            {
                try
                {
                    (src + i)->TType::dtor TType();
                }
                catch (const std::exception ref ex)
                {
                }
            }

            Deallocate(src, count);
        }
    }

    template <typename TType>
    inline TType ptr Allocator::Allocate(const sizet count)
    {
        return (TType ptr) AllocateRaw(count * sizeof(TType));
    }

    template <>
    inline void ptr Allocator::Allocate<void>(const sizet count)
    {
        // explicit specialization for void type,
        // to avoid call to sizeof() operator on void type

        return AllocateRaw(count);
    }

    template <typename TType>
    inline void Allocator::Deallocate(TType ptr src, const sizet count)
    {
        DeallocateRaw(rcast<memptr>(src), sizeof(TType) * count);
    }

    template <>
    inline void Allocator::Deallocate(void ptr src, const sizet count)
    {
        // explicit specialization for void type,
        // to avoid call to sizeof() operator on void type

        DeallocateRaw(rcast<memptr>(src), count);
    }
}