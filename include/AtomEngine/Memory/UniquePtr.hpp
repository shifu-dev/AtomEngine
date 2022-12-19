#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Memory/Ptr.hpp"
#include "AtomEngine/Memory/IAllocator.hpp"

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

        TUniquePtr(TUniquePtr&& other) = default;
        ThisT& operator = (ThisT&& other) = default;

        TUniquePtr(const TUniquePtr& other) = delete;
        ThisT& operator = (const ThisT& other) = delete;

        TUniquePtr(TypeT* inPtr) noexcept:
            BaseT(inPtr), _allocator(DefaultAllocatorInstance) { }

        TUniquePtr(TypeT* inPtr, IAllocator& allocator) noexcept:
            BaseT(inPtr), _allocator(allocator) { }

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

    protected:
        using BaseT::_ptr;

        IAllocator& _allocator;
    };
}