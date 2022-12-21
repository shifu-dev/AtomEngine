#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Memory/Ptr.hpp"
#include "AtomEngine/Memory/IAllocator.hpp"
#include "AtomEngine/Memory/DefaultAllocator.hpp"

namespace Atom
{
    template <typename TypeT>
    struct TUniquePtr: public TPtr<TypeT>
    {
        using ThisT = TUniquePtr<TypeT>;
        using BaseT = TPtr<TypeT>;

    public:
        TUniquePtr() noexcept:
            BaseT(nullptr) { }

        TUniquePtr(const TUniquePtr& other) = delete;
        TUniquePtr& operator = (const TUniquePtr& other) = delete;

        TUniquePtr(TUniquePtr&& other) noexcept
        {
            Swap(other);
        }

        TUniquePtr& operator = (TUniquePtr&& other) noexcept
        {
            TUniquePtr tmp = other;
            Swap(tmp);

            return *this;
        }

        TUniquePtr(TypeT* ptr) noexcept:
            BaseT(ptr), _allocator(DefaultAllocatorInstance) { }

        TUniquePtr(TypeT* ptr, IAllocator& allocator) noexcept:
            BaseT(ptr), _allocator(allocator) { }

        TUniquePtr& operator = (TypeT* ptr) noexcept
        {
            TUniquePtr tmp = move(*this);

            _ptr = ptr;

            return *this;
        }

        ~TUniquePtr()
        {
            if (_ptr != nullptr)
            {
                _allocator.Destruct(_ptr);
            }
        };

    public:
        template <typename... ArgsT>
        static ThisT Create(ArgsT&&... args)
        {
            TypeT* obj = DefaultAllocatorInstance.Construct<TypeT>(forward<ArgsT>(args)...);
            return ThisT(obj, DefaultAllocatorInstance);
        }

    public:
        void Swap(TUniquePtr& other) noexcept
        {
            swap(_ptr, other._ptr);
            swap(_allocator, other._allocator);
        }

    protected:
        using BaseT::_ptr;

        IAllocator& _allocator = DefaultAllocatorInstance;
    };
}