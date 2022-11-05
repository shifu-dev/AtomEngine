#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Memory/Core.hpp"

namespace Atom
{
    /// @brief base allocator type to allocate memory,
    /// allocates on heap using new() and delete()
    ///
    /// @note we allocate using legacy c functions,
    /// because virtual functions (to keep allocator extensible)
    /// like AllocateRaw and DeallocateRaw uses custom type to manage memory
    struct Allocator
    {
        mpublic constexpr Allocator() = default;
        mpublic constexpr Allocator(const Allocator ref other) = default;
        mpublic constexpr Allocator(Allocator rref other) = default;
        mpublic constexpr Allocator ref operator =(const Allocator ref other) = default;
        mpublic constexpr Allocator ref operator =(Allocator rref other) = default;

        /// @brief calls ConstructMultiple with count = 1
        mpublic template <typename Type, typename... Args>
            Type ptr Construct(Args&&... args);

        /// @brief creates object of type @tparam Type -> allocates memory and calls constructor
        /// @tparam Type type of object to create
        /// @tparam ...Args type of arguments to pass to @tparam Type constructor
        /// @param ...args arguments to pass to @tparam Type constructor
        /// @param count count of objects to allocate
        /// @return ptr to created object
        ///
        /// @note calls underlying AllocateRaw to allocate memory
        /// @note if count == 0, this function does nothing
        mpublic template <typename Type, typename... Args>
            Type ptr ConstructMultiple(const sizet count, Args&&... args);

        /// @brief destroys object of type @tparam Type -> calls destructor and deallocates memory
        /// @tparam Type type of object to destruct
        /// @param objectPtr ptr to object to destruct
        /// @param count count of objects to destruct
        ///
        /// @note calls underlying DeallocateRaw to deallocate memory
        mpublic template <typename Type>
            void Destruct(Type ptr objectPtr, const sizet count = 1);

        /// @brief allocates memory to specified type
        /// @tparam Type type for which to allocate memory
        /// @param count count of memory blocks to allocate for type Type
        /// @return ptr to allocated memory
        ///
        /// @note if count == 0, does not allocates memory.
        /// @note total memory allocated in bytes is equal to sizeof(Type) * count
        mpublic template <typename Type>
            Type ptr Allocate(const sizet count = 1);

        /// @brief dellocates memory for @tparam Type
        /// @tparam Type type of object to deallocate memory for
        /// @param src ptr to memory to deallocate
        /// @param count count of memory blocks to deallocate
        mpublic template <typename Type>
            void Deallocate(Type ptr src, const sizet count = 1);

        /// @brief allocates memory in bytes
        /// @param count count in bytes to allocate memory
        /// @param clear if true, writes memory with zeros
        /// @return ptr to allocated memory
        mpublic virtual memptr AllocateRaw(const sizet count, bool clear = true) abstract;

        /// @brief dellocates allocated memory
        /// @param src pointer to the memory space to dellocate
        /// @param count count of memory
        mpublic virtual void DeallocateRaw(memptr src, const sizet count) abstract;
    };

    template <typename Type, typename... Args>
    inline Type ptr Allocator::Construct(Args&&... args)
    {
        return ConstructMultiple<Type>(1, forward<Args>(args)...);
    }

    template <typename Type, typename... Args>
    inline Type ptr Allocator::ConstructMultiple(const sizet count, Args&&... args)
    {
        Type ptr objectPtr = Allocate<Type>(count);

        if (objectPtr isnot null)
        {
            for (sizet i = 0; i < count; i++)
            {
                new(objectPtr + i) Type(forward<Args>(args)...);
            }
        }

        return objectPtr;
    }

    template <typename Type>
    inline void Allocator::Destruct(Type ptr objectPtr, const sizet count)
    {
        if (objectPtr isnot null)
        {
            for (sizet i = 0; i < count; i++)
            {
                objectPtr->Type::~Type();
            }

            Deallocate(objectPtr, count);
        }
    }

    template <typename Type>
    inline Type ptr Allocator::Allocate(const sizet count)
    {
        return (Type ptr) AllocateRaw(count * sizeof(Type));
    }

    template <>
    inline void ptr Allocator::Allocate<void>(const sizet count)
    {
        // explicit specialization for void type,
        // to avoid call to sizeof() operator on void type

        return AllocateRaw(count);
    }

    template <typename Type>
    inline void Allocator::Deallocate(Type ptr src, const sizet count)
    {
        DeallocateRaw(src, sizeof(Type) * count);
    }

    template <>
    inline void Allocator::Deallocate(void ptr src, const sizet count)
    {
        // explicit specialization for void type,
        // to avoid call to sizeof() operator on void type

        DeallocateRaw(src, count);
    }
}