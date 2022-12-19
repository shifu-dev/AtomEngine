#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Memory/Ptr.hpp"
#include "AtomEngine/Memory/IAllocator.hpp"

namespace Atom
{
    template <typename TypeT>
    struct TSharedPtr: public TPtr<TypeT>
    {
        using ThisT = TSharedPtr<TypeT>;
        using BaseT = TPtr<TypeT>;

    protected:
        struct SharedData
        {
            SizeT count = 0;
            IAllocator& allocator = DefaultAllocatorInstance;
        };

    public:
        TSharedPtr() noexcept:
            BaseT(nullptr) { }

        TSharedPtr(const TSharedPtr& other) noexcept:
            BaseT(other)
        {
            _Copy(other);

            if (_sharedData != nullptr)
            {
                _sharedData->count++;
            }
        }

        TSharedPtr(TSharedPtr&& other) noexcept:
            BaseT(move(other))
        {
            _Swap(other);
        }

        ThisT& operator = (const ThisT& other) noexcept
        {
            ThisT tmp = other;
            _Swap(tmp);

            return *this;
        }

        ThisT& operator = (ThisT&& other) noexcept
        {
            ThisT tmp = other;
            _Swap(tmp);

            return *this;
        }

        TSharedPtr(TypeT* inPtr) noexcept:
            ThisT(inPtr, DefaultAllocatorInstance) { }

        TSharedPtr(TypeT* inPtr, IAllocator& allocator) noexcept:
            BaseT(inPtr)
        {
            if (inPtr != nullptr)
            {
                _sharedData = allocator.Construct<SharedData>();
                _sharedData->allocator = allocator;
                _sharedData->count = 0;
            }
        }

        ~TSharedPtr()
        {
            if (_ptr != nullptr)
            {
                DEBUG_ASSERT(_sharedData != nullptr, "TSharedPtr: _ptr == not nullptr, \
                    but _sharedData == nullptr.");

                DEBUG_ASSERT(_sharedData->count != 0, "TSharedPtr: _sharedData->count == 0, \
                    but this SharedPtr references it.");

                _sharedData->count--;

                if (_sharedData->count == 0)
                {
                    _sharedData->allocator.Destruct(_ptr);
                    _sharedData->allocator.Destruct(_sharedData);
                }
            }
        };

    protected:
        void _Copy(const ThisT& other) noexcept
        {
            _sharedData = other._sharedData;
        }

        void _Swap(ThisT& other) noexcept
        {
            swap(_ptr, other._ptr);
            swap(_sharedData, other._sharedData);
        }

    public:
        template <typename... ArgsT>
        static ThisT Create(ArgsT... args)
        {
            TypeT* obj = DefaultAllocatorInstance.Construct(forward<ArgsT>(args)...);
            return ThisT(obj, DefaultAllocatorInstance);
        }

    public:
        SizeT RefCount() const noexcept
        {
            if (_sharedData == nullptr)
                return 0;

            return _sharedData->count;
        }

    protected:
        using BaseT::_ptr;

        SharedData* _sharedData;
    };
}