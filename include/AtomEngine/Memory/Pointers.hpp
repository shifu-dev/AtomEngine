#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Memory/Allocator.hpp"
#include "AtomEngine/Memory/DefaultAllocator.hpp"

namespace Atom
{
    /// @brief base class for pointers
    /// @tparam TType pointer type
    template <typename TType>
    struct Ptr
    {
        /// @brief default constructor, creates a null pointer
        mpublic Ptr() : Ptr(nullptr) { }

        /// @brief initializes underlying pointer with this @param valuePtr
        /// @param valuePtr pointer to initialize with
        mpublic Ptr(TType ptr valuePtr) : mPtr(valuePtr) { }

        /// @brief checks if pointer is null
        /// @note this does not calls == operator,
        /// instead checks for the memory address
        /// @return returns true if pointer is null
        mpublic bool isNull() const noexcept
        {
            return isnull(mPtr);
        }

        mpublic TType& operator->() const noexcept
        {
            return ptr mPtr;
        }

        mprotected TType ptr mPtr;
    };

    template <typename TType, typename TAllocator = DefaultAllocator>
    struct UniquePtr : public Ptr<TType>
    {
        using TThis = UniquePtr<TType, TAllocator>;
        using TBase = Ptr<TType>;
        static const TThis Null;

        mprotected const TBase ptr base = (TBase ptr) this;

        mpublic template <typename... Args>
            static TThis Create(Args... args)
        {
            return Create(DefaultAllocator(), forward(args...));
        }

        mpublic template <typename... Args>
            static TThis Create(TAllocator allocator, Args... args)
        {
            const TType ptr valueptr = nullptr;
            if (allocator.Allocate(valueptr) is false)
            {
                return UniquePtr();
            }

            valueptr->TType(forward(args...));
            return UniquePtr(valueptr, allocator);
        }

        mpublic UniquePtr() = delete;
        mpublic UniquePtr(const UniquePtr ref) = delete;
        mpublic UniquePtr(UniquePtr rref) = delete;
        mpublic UniquePtr(TType ptr value, const TAllocator ref allocator = TAllocator());
        mpublic dtor UniquePtr();

        mprotected TAllocator _allocator;
    };

    template <typename TType, typename TAllocator>
    const UniquePtr<TType, TAllocator> UniquePtr<TType, TAllocator>::Null = UniquePtr(nullptr, TAllocator());

    template <typename TType, typename TAllocator>
    UniquePtr<TType, TAllocator>::UniquePtr(TType ptr value, const TAllocator ref allocator)
        : TBase(value), _allocator(allocator) { }

    template <typename TType, typename TAllocator>
    UniquePtr<TType, TAllocator>::dtor UniquePtr()
    {
        if (TThis::isNull() is false)
        {
            _allocator.Deallocate(TThis::mPtr, 1);
        }
    };
}