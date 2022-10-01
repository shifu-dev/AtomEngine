#pragma once
#include "SSEngine/Core.hpp"
#include <cstdlib>
#include <cstring>

namespace SSEngine
{
    /// @brief base allocator type to allocate memory,
    /// allocates on heap using new() and delete()
    ///
    /// @note we allocate using legacy c functions,
    /// because virtual functions (to keep allocator extensible)
    /// like AllocateRaw and DeallocateRaw uses custom type to manage memory
    struct Allocator
    {
    public:
        /// @brief type used to represent memory unit
        /// generally, void or byte
        using memt = void;

        /// @brief ptr to memt
        using memptr = memt ptr;

        /// @brief value type to represent count
        using sizet = umax;

    public:
        constexpr Allocator() = default;
        constexpr Allocator(const Allocator lref other) = default;
        constexpr Allocator(Allocator rref other) = default;
        constexpr Allocator lref operator =(const Allocator lref other) = default;
        constexpr Allocator lref operator =(Allocator rref other) = default;

        /// @brief calls ConstructMultiple with count = 1
        template <typename Type, typename... Args>
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
        template <typename Type, typename... Args>
        Type ptr ConstructMultiple(const sizet count, Args&&... args);

        /// @brief destroys object of type @tparam Type -> calls destructor and deallocates memory
        /// @tparam Type type of object to destruct
        /// @param objectPtr ptr to object to destruct
        /// @param count count of objects to destruct
        ///
        /// @note calls underlying DeallocateRaw to deallocate memory
        template <typename Type>
        void Destruct(Type ptr objectPtr, const sizet count = 1);

        /// @brief allocates memory to specified type
        /// @tparam Type type for which to allocate memory
        /// @param count count of memory blocks to allocate for type Type
        /// @return ptr to allocated memory
        ///
        /// @note if count == 0, does not allocates memory.
        /// @note total memory allocated in bytes is equal to sizeof(Type) * count
        template <typename Type>
        Type ptr Allocate(const sizet count = 1);

        /// @brief dellocates memory for @tparam Type
        /// @tparam Type type of object to deallocate memory for
        /// @param src ptr to memory to deallocate
        /// @param count count of memory blocks to deallocate
        template <typename Type>
        void Deallocate(Type ptr src, const sizet count = 1);

        /// @brief allocates memory in bytes
        /// @param count count in bytes to allocate memory
        /// @param clear if true, writes memory with zeros
        /// @return ptr to allocated memory
        virtual memptr AllocateRaw(const sizet count, bool clear = true);

        /// @brief dellocates allocated memory
        /// @param src pointer to the memory space to dellocate
        /// @param count count of memory
        virtual void DeallocateRaw(memptr src, const sizet count);
    };

    template <typename Type, typename... Args>
    Type ptr Allocator::Construct(Args&&... args)
    {
        return ConstructMultiple<Type>(1, forward<Args>(args)...);
    }

    template <typename Type, typename... Args>
    Type ptr Allocator::ConstructMultiple(const sizet count, Args&&... args)
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
    void Allocator::Destruct(Type ptr objectPtr, const sizet count)
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
    Type ptr Allocator::Allocate(const sizet count)
    {
        return (Type ptr) AllocateRaw(count * sizeof(Type));
    }

    template <>
    void ptr Allocator::Allocate<void>(const sizet count)
    {
        // explicit specialization for void type,
        // to avoid call to sizeof() operator on void type

        return AllocateRaw(count);
    }

    template <typename Type>
    void Allocator::Deallocate(Type ptr src, const sizet count)
    {
        DeallocateRaw(src, sizeof(Type) * count);
    }

    template <>
    void Allocator::Deallocate(void ptr src, const sizet count)
    {
        // explicit specialization for void type,
        // to avoid call to sizeof() operator on void type

        DeallocateRaw(src, count);
    }

    Allocator::memptr Allocator::AllocateRaw(sizet count, bool clear)
    {
        count = std::max<sizet>(0, count);
        memptr dest = null;

        if (count > 0)
        {
            dest = malloc(count);

            if (dest isnot null)
            {
                if (clear)
                {
                    std::memset(dest, 0, count);
                }
            }
        }

        return dest;
    }

    void Allocator::DeallocateRaw(memptr src, const sizet count)
    {
        if (isnotnull(src))
        {
            free(src);
        }
    }

    using DefaultAllocator = SSEngine::Allocator;
    Allocator defaultAllocator = Allocator();
}

SS_CREATE_NAME_ALIAS(Allocator) = SSEngine::Allocator;
SS_CREATE_NAME_ALIAS(DefaultAllocator) = SSEngine::DefaultAllocator;