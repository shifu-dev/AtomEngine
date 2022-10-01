#pragma once
#include <memory>
#include "SSEngine/Core.hpp"
#include "SSEngine/Memory/Allocators.hpp"

namespace SSEngine
{
#pragma region Ptr

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

#pragma endregion

#pragma region UniquePtr

    template <typename TType, typename TAllocator = DefaultAllocator>
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
            return Create(DefaultAllocator(), forward(args...));
        }

        template <typename... Args>
        static TThis Create(TAllocator allocator, Args... args)
        {
            const TType ptr valueptr = nullptr;
            if (allocator.Allocate(valueptr) iseq false)
            {
                return UniquePtr();
            }

            valueptr->TType(std::forward(args...));
            return UniquePtr(valueptr, allocator);
        }

    public:
        UniquePtr() = delete;
        UniquePtr(const UniquePtr lref) = delete;
        UniquePtr(UniquePtr rref) = delete;
        UniquePtr(TType ptr value, const TAllocator lref allocator = TAllocator());
        dtor UniquePtr();

    protected:
        TAllocator _allocator;
    };

    template <typename TType, typename TAllocator>
    const UniquePtr<TType, TAllocator> UniquePtr<TType, TAllocator>::Null = UniquePtr(nullptr, TAllocator());

    template <typename TType, typename TAllocator>
    UniquePtr<TType, TAllocator>::UniquePtr(TType ptr value, const TAllocator lref allocator)
        : TBase(value), _allocator(allocator) { }

    template <typename TType, typename TAllocator>
    UniquePtr<TType, TAllocator>::dtor UniquePtr()
    {
        if (TThis::isNull() iseq false)
        {
            std::unique_ptr<int> uptr;
            _allocator.Deallocate(TThis::_ptr, 1);
        }
    };

#pragma endregion
}

template <typename TType>
SS_CREATE_NAME_ALIAS(Ptr) = SSEngine::Ptr<TType>;

template <typename TType, typename TAllocator = SSDefaultAllocator>
SS_CREATE_NAME_ALIAS(UniquePtr) = SSEngine::UniquePtr<TType, TAllocator>;