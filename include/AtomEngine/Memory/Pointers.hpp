#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Memory/Allocator.hpp"
#include "AtomEngine/Memory/LegacyAllocator.hpp"

namespace Atom
{
    /// @brief base class for pointers
    /// @tparam TType pointer type
    template <typename TType>
    struct Ptr
    {
    public:

        /// @brief default constructor, creates a null pointer
        Ptr() : Ptr(nullptr) { }

        /// @brief initializes underlying pointer with this @param valuePtr
        /// @param valuePtr pointer to initialize with
        Ptr(TType ptr valuePtr) : _ptr(valuePtr) { }

        /// @brief checks if pointer is null
        /// @note this does not calls == operator,
        /// instead checks for the memory address
        /// @return returns true if pointer is null
        bool isNull() const noexcept
        {
            return isnull(_ptr);
        }

        TType& operator->() const noexcept
        {
            return ptr _ptr;
        }

    protected:
        TType ptr _ptr;
    };

    template <typename TType, typename TAllocator = LegacyAllocator>
    struct UniquePtr : public Ptr<TType>
    {
    public:
        using TThis = UniquePtr<TType, TAllocator>;
        using TBase = Ptr<TType>;
        static const TThis Null;

    protected:
        const TBase ptr base = (TBase ptr) this;

    public:
        template <typename... Args>
        static TThis Create(Args... args)
        {
            return Create(LegacyAllocator(), forward(args...));
        }

        template <typename... Args>
        static TThis Create(TAllocator allocator, Args... args)
        {
            const TType ptr valueptr = nullptr;
            if (allocator.Allocate(valueptr) iseq false)
            {
                return UniquePtr();
            }

            valueptr->TType(forward(args...));
            return UniquePtr(valueptr, allocator);
        }

    public:
        UniquePtr() = delete;
        UniquePtr(const UniquePtr ref) = delete;
        UniquePtr(UniquePtr rref) = delete;
        UniquePtr(TType ptr value, const TAllocator ref allocator = TAllocator());
        dtor UniquePtr();

    protected:
        TAllocator _allocator;
    };

    template <typename TType, typename TAllocator>
    const UniquePtr<TType, TAllocator> UniquePtr<TType, TAllocator>::Null = UniquePtr(nullptr, TAllocator());

    template <typename TType, typename TAllocator>
    UniquePtr<TType, TAllocator>::UniquePtr(TType ptr value, const TAllocator ref allocator)
        : TBase(value), _allocator(allocator) { }

    template <typename TType, typename TAllocator>
    UniquePtr<TType, TAllocator>::dtor UniquePtr()
    {
        if (TThis::isNull() iseq false)
        {
            _allocator.Deallocate(TThis::_ptr, 1);
        }
    };
}