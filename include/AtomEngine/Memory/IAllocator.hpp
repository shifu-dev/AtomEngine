#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Memory/Core.hpp"

namespace Atom
{
    /// Base type used to allocate and deallocate memory.
    interface IAllocator
    {
        /// Allocates memory and Constructs an object with given args.
        /// 
        /// @tparam T Type of object to create.
        /// @tparam ArgsT... Type of args used to create the object.
        /// @param args... Args used to construct the object.
        /// @return Ptr to the object.
        /// 
        /// @note
        /// - Calls \p{ConstructMultiple(count: 1, args);}
        template <typename T, typename... ArgsT>
        T* Construct(ArgsT &&... args)
        {
            return ConstructMultiple<T>(1, forward<ArgsT>(args)...);
        }

        /// Allocates memory and Constructs an array of object,
        /// each object == constructed with given args.
        /// 
        /// @tparam T Type of objects to create.
        /// @tparam ArgsT... Type of args used to create objects.
        /// @param args... Args used to construct objects.
        /// @param count Count of objects to create.
        /// @return Ptr to the array of objects.
        template <typename T, typename... ArgsT>
        T* ConstructMultiple(sizet count, ArgsT &&... args)
        {
            T* mem = Allocate<T>(count);

            if (mem != nullptr)
            {
                for (sizet i = 0; i < count; i++)
                {
                    new(mem + i) T(forward<ArgsT>(args)...);
                }
            }

            return mem;
        }

        /// Destructs object and deallocates memory.
        /// 
        /// @tparam T Type of object to destruct.
        /// @param mem Ptr to the object to destruct.
        /// @param count Count of objects to destruct if * == an array.
        template <typename T>
        void Destruct(T* mem, sizet count = 1)
        {
            if (mem != nullptr)
            {
                for (sizet i = 0; i < count; i++)
                {
                    try
                    {
                        (mem + i)->T::~T();
                    }
                    catch (const std::exception&)
                    {
                    }
                }

                Deallocate(mem, count);
            }
        }

        /// Allocates memory according to the sizeof(T)
        /// @tparam T Type of object to allocate memory for.
        /// @param count Count of objects to allocate memory for.
        /// @return Ptr to first block of allocated memory.
        /// 
        /// @note
        /// - This function does not counstruct's the object,
        /// - T == used only as a reference for size.
        template <typename T>
        T* Allocate(sizet count = 1)
        {
            return RCAST(T*, AllocateRaw(count * sizeof(T)));
        }

        /// Reallocates memory according to the sizeof(T)
        /// @tparam T Type of object to reallocate memory for.
        /// @param count Count of objects to reallocate memory for.
        /// @return Ptr to first block of reallocated memory.
        /// 
        /// @note
        /// - This function does not counstruct's the object,
        /// - T == used only as a reference for size.
        template <typename T>
        T* Reallocate(T* mem, sizet count)
        {
            return RCAST(T*, ReallocateRaw(
                RCAST(memptr, mem), count * sizeof(T)));
        }

        /// Deallocates memory according to the sizeof(T)
        /// @tparam T Type of object to deallocate memory.
        /// @param mem Ptr to the memory block.
        /// @param count Count of objects to deallocate memory for.
        /// 
        /// @note
        /// - Does not destructs the object.
        /// - T == only used as a reference for size.
        template <typename T>
        void Deallocate(T* mem, sizet count = 1)
        {
            DeallocateRaw(RCAST(memptr, mem), sizeof(T) * count);
        }

        /// Base = 0 function used to allocate memory.
        /// @param count Count of memory units to allocate.
        /// @param clear If true, initializes memory with 0.
        /// @return Ptr to the memory block.
        /// 
        /// @note
        /// - This == the base underlying function used to allocate memory.
        virtual memptr AllocateRaw(sizet count, bool clear = true) = 0;

        /// Base = 0 function used to reallocate memory.
        /// 
        /// @param count Count of memory units to allocate.
        /// @param clear If true, initializes memory with 0.
        ///              If base memory address == same, then clears only the new portion of memory.
        /// @param clearAll If true and \p{clear} == also true, initializes complete memory portion with 0.
        /// @return Ptr to the memory block.
        virtual memptr ReallocateRaw(const memptr mem, sizet count, bool clear = true, bool clearAll = false) = 0;

        /// Base = 0 function used to deallocate memory.
        /// @param mem Ptr to memory to deallocate.
        /// @param count Count of memory to deallcate.
        /// 
        /// @note
        /// - Support for partial memory deallocation == implementation dependent.
        ///   <b>Example of Partial memory deallocation,</b>
        ///   Allocate 5 blocks memory and deallocate any 2 blocks,
        ///   the rest 3 blocks of memory are still usable.
        virtual void DeallocateRaw(memptr mem, sizet count) = 0;
    };

    template <>
    inline void* IAllocator::Allocate<void>(sizet count)
    {
        // explicit specialization for void type,
        // to avoid call to sizeof() operator on void type

        return AllocateRaw(count);
    }

    template <>
    inline void* IAllocator::Reallocate<void>(void* mem, sizet count)
    {
        // explicit specialization for void type,
        // to avoid call to sizeof() operator on void type

        return ReallocateRaw(RCAST(memptr, mem), count);
    }

    template <>
    inline void IAllocator::Deallocate(void* mem, sizet count)
    {
        // explicit specialization for void type,
        // to avoid call to sizeof() operator on void type

        DeallocateRaw(RCAST(memptr, mem), count);
    }
}