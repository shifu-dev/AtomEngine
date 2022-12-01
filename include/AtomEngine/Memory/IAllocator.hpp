#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Memory/Core.hpp"

namespace Atom
{
    /// Base type used to allocate and deallocate memory.
    interface IAllocator
    {
        mpublic constexpr IAllocator() = default;
        mpublic constexpr IAllocator(const IAllocator ref other) = default;
        mpublic constexpr IAllocator(IAllocator rref other) = default;
        mpublic constexpr IAllocator ref operator =(const IAllocator ref other) = default;
        mpublic constexpr IAllocator ref operator =(IAllocator rref other) = default;

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
        mpublic template <typename TType, typename... TArgs>
            TType ptr ConstructMultiple(const sizet count, TArgs ref... args);

        /// ----------------------------------------------------------------------------
        /// Destructs object and deallocates memory.
        /// 
        /// @tparam TType Type of object to destruct.
        /// @param mem Ptr to the object to destruct.
        /// @param count Count of objects to destruct if ptr is an array.
        mpublic template <typename TType>
            void Destruct(TType ptr mem, const sizet count = 1);

        /// ----------------------------------------------------------------------------
        /// Allocates memory according to the sizeof(TType)
        /// @tparam TType Type of object to allocate memory for.
        /// @param count Count of objects to allocate memory for.
        /// @return Ptr to first block of allocated memory.
        /// 
        /// @note
        /// - This function does not counstruct's the object,
        /// - TType is used only as a reference for size.
        mpublic template <typename TType>
            TType ptr Allocate(const sizet count = 1);

        /// ----------------------------------------------------------------------------
        /// Reallocates memory according to the sizeof(TType)
        /// @tparam TType Type of object to reallocate memory for.
        /// @param count Count of objects to reallocate memory for.
        /// @return Ptr to first block of reallocated memory.
        /// 
        /// @note
        /// - This function does not counstruct's the object,
        /// - TType is used only as a reference for size.
        mpublic template <typename TType>
            TType ptr Reallocate(TType ptr mem, const sizet count);

        /// ----------------------------------------------------------------------------
        /// Deallocates memory according to the sizeof(TType)
        /// @tparam TType Type of object to deallocate memory.
        /// @param mem Ptr to the memory block.
        /// @param count Count of objects to deallocate memory for.
        /// 
        /// @note
        /// - Does not destructs the object.
        /// - TType is only used as a reference for size.
        mpublic template <typename TType>
            void Deallocate(TType ptr mem, const sizet count = 1);

        /// ----------------------------------------------------------------------------
        /// Base abstract function used to allocate memory.
        /// @param count Count of memory units to allocate.
        /// @param clear If true, initializes memory with 0.
        /// @return Ptr to the memory block.
        /// 
        /// @note
        /// - This is the base underlying function used to allocate memory.
        mpublic virtual memptr AllocateRaw(const sizet count, bool clear = true) abstract;

        /// ----------------------------------------------------------------------------
        /// Base abstract function used to reallocate memory.
        /// 
        /// @param count Count of memory units to allocate.
        /// @param clear If true, initializes memory with 0.
        ///              If base memory address is same, then clears only the new portion of memory.
        /// @param clearAll If true and \p{clear} is also true, initializes complete memory portion with 0.
        /// @return Ptr to the memory block.
        mpublic virtual memptr ReallocateRaw(const memptr mem, const sizet count, bool clear = true, bool clearAll = false) abstract;

        /// ----------------------------------------------------------------------------
        /// Base abstract function used to deallocate memory.
        /// @param mem Ptr to memory to deallocate.
        /// @param count Count of memory to deallcate.
        /// 
        /// @note
        /// - Support for partial memory deallocation is implementation dependent.
        ///   <b>Example of Partial memory deallocation,</b>
        ///   Allocate 5 blocks memory and deallocate any 2 blocks,
        ///   the rest 3 blocks of memory are still usable.
        mpublic virtual void DeallocateRaw(memptr mem, const sizet count) abstract;
    };

    template <typename TType, typename... TArgs>
    inline TType ptr IAllocator::Construct(TArgs ref... args)
    {
        return ConstructMultiple<TType>(1, forward<TArgs>(args)...);
    }

    template <typename TType, typename... TArgs>
    inline TType ptr IAllocator::ConstructMultiple(const sizet count, TArgs ref... args)
    {
        TType ptr mem = Allocate<TType>(count);

        if (mem isnot null)
        {
            for (sizet i = 0; i < count; i++)
            {
                new(mem + i) TType(forward<TArgs>(args)...);
            }
        }

        return mem;
    }

    template <typename TType>
    inline void IAllocator::Destruct(TType ptr mem, const sizet count)
    {
        if (mem isnot null)
        {
            for (sizet i = 0; i < count; i++)
            {
                try
                {
                    (mem + i)->TType::dtor TType();
                }
                catch (const std::exception ref)
                {
                }
            }

            Deallocate(mem, count);
        }
    }

    template <typename TType>
    inline TType ptr IAllocator::Allocate(const sizet count)
    {
        return RCAST(TType ptr, AllocateRaw(count * sizeof(TType)));
    }

    template <>
    inline void ptr IAllocator::Allocate<void>(const sizet count)
    {
        // explicit specialization for void type,
        // to avoid call to sizeof() operator on void type

        return AllocateRaw(count);
    }

    template <typename TType>
    inline TType ptr IAllocator::Reallocate(TType ptr mem, const sizet count)
    {
        return RCAST(TType ptr, ReallocateRaw(
            RCAST(memptr, mem), count * sizeof(TType)));
    }

    template <>
    inline void ptr IAllocator::Reallocate<void>(void ptr mem, const sizet count)
    {
        // explicit specialization for void type,
        // to avoid call to sizeof() operator on void type

        return ReallocateRaw(RCAST(memptr, mem), count);
    }

    template <typename TType>
    inline void IAllocator::Deallocate(TType ptr mem, const sizet count)
    {
        DeallocateRaw(RCAST(memptr, mem), sizeof(TType) * count);
    }

    template <>
    inline void IAllocator::Deallocate(void ptr mem, const sizet count)
    {
        // explicit specialization for void type,
        // to avoid call to sizeof() operator on void type

        DeallocateRaw(RCAST(memptr, mem), count);
    }
}