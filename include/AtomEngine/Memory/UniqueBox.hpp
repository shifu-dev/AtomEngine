#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Reflection/Core.hpp"
#include "AtomEngine/Memory/UniquePtr.hpp"

namespace Atom
{
    namespace Internal
    {
        class UniqueBoxIdentifier { };
    }

    template <typename TypeT, sizet StackSize>
    class TUniqueBox: public TUniquePtr<TypeT>,
        public Internal::UniqueBoxIdentifier
    {
        using BaseT = TUniquePtr<TypeT>;

        template <typename OtherTypeT>
        constexpr static bool IsUniqueBox =
            IsSubClass<Internal::UniqueBoxIdentifier, OtherTypeT>;

    /// ----------------------------------------------------------------------------
    public:
        TUniqueBox() noexcept:
            TUniqueBox(nullptr) { }

        TUniqueBox(NullT obj) noexcept:
            BaseT(nullptr), _objectSize(0) { }

        TUniqueBox(const TUniqueBox& other) noexcept
        {
            _Copy(other);
        }

        template <sizet OtherStackSize>
        TUniqueBox(const TUniqueBox<TypeT, OtherStackSize>& other) noexcept
        {
            _Copy(other);
        }

        TUniqueBox(TUniqueBox&& other) noexcept
        {
            _Swap(other);
        }

        template <sizet OtherStackSize>
        TUniqueBox(TUniqueBox<TypeT, OtherStackSize>&& other) noexcept
        {
            _Swap(other);
        }

        TUniqueBox& operator = (const TUniqueBox& other) noexcept
        {
            _DestroyObject();
            _Copy(other);

            return *this;
        }

        template <sizet OtherStackSize>
        TUniqueBox& operator = (const TUniqueBox<TypeT, OtherStackSize>& other) noexcept
        {
            _DestroyObject();
            _Copy(other);

            return *this;
        }

        TUniqueBox& operator = (TUniqueBox&& other) noexcept
        {
            _DestroyObject();
            _Swap(other);

            return *this;
        }

        template <sizet OtherStackSize>
        TUniqueBox& operator = (TUniqueBox<TypeT, OtherStackSize>&& other) noexcept
        {
            _DestroyObject();
            _Swap(other);

            return *this;
        }

        template <typename OtherTypeT, EnableIf<!IsUniqueBox<OtherTypeT>> = 0>
        TUniqueBox(const OtherTypeT& obj) noexcept
        {
            _SetObject(obj);
        }

        template <typename OtherTypeT, EnableIf<!IsUniqueBox<OtherTypeT>> = 0>
        TUniqueBox(OtherTypeT&& obj) noexcept
        {
            _SetObject(move(obj));
        }

        template <typename OtherTypeT, EnableIf<!IsUniqueBox<OtherTypeT>> = 0>
        TUniqueBox& operator = (const OtherTypeT& obj) noexcept
        {
            _SetObject(obj);
        }

        template <typename OtherTypeT, EnableIf<!IsUniqueBox<OtherTypeT>> = 0>
        TUniqueBox& operator = (OtherTypeT&& obj) noexcept
        {
            _SetObject(move(obj));
        }

        ~TUniqueBox()
        {
            _DestroyObject();
        }

    /// ----------------------------------------------------------------------------
    protected:

        // does not destroys previous state,
        // assumes to be called from constructor
        template <sizet OtherStackSize>
        void _Copy(const TUniqueBox<TypeT, OtherStackSize>& other) noexcept
        {
            _ptr = _AllocMem(other._objectSize);
            _objectSize = other._objectSize;

            memcpy(_ptr, other._ptr, _objectSize);
        }

        template <sizet OtherStackSize>
        void _Swap(TUniqueBox<TypeT, OtherStackSize>& other) noexcept
        {
            byte tmpStackMem[StackSize];

            // if our obj == stored in stack memory, save if before swapping
            if (_ptr == RCAST(TypeT*, _stackMem))
            {
                memcpy(tmpStackMem, _stackMem, _objectSize);
            }

            swap(_allocator, other._allocator);
            swap(_ptr, other._ptr);
            swap(_objectSize, other._objectSize);

            if (_ptr == RCAST(TypeT*, other._stackMem))
            {
                _ptr = RCAST(TypeT*, _AllocMem(_objectSize));
                memcpy(RCAST(memptr, _ptr), other._stackMem, _objectSize);
            }

            if (other._ptr == RCAST(TypeT*, _stackMem))
            {
                other._ptr = RCAST(TypeT*, other._AllocMem(other._objectSize));
                memcpy(RCAST(memptr, other._ptr), tmpStackMem, other._objectSize);
            }
        }

        memptr _AllocMem(sizet size) noexcept
        {
            memptr mem = nullptr;

            if (size != 0)
            {
                if (size <= StackSize)
                {
                    mem = _stackMem;
                }
                else
                {
                    mem = _allocator.AllocateRaw(size);
                }
            }

            return mem;
        }

        void _DestroyObject() noexcept
        {
            if (_ptr != nullptr)
            {
                _ptr->TypeT::~TypeT();
                // ::DestructAt(_ptr);

                if (_ptr != RCAST(TypeT*, _stackMem))
                {
                    _allocator.DeallocateRaw(RCAST(memptr, _ptr), _objectSize);
                }

                _objectSize = 0;
                _ptr = nullptr;
            }
        }

        template <typename OtherTypeT>
        void __SetObject(const OtherTypeT& obj) noexcept
        {
            StaticAssertSubClass<TypeT, OtherTypeT>();

            _DestroyObject();

            _objectSize = sizeof(OtherTypeT);
            _ptr = RCAST(TypeT*, _AllocMem(_objectSize));
        }

        template <typename OtherTypeT>
        void _SetObject(const OtherTypeT& obj) noexcept
        {
            __SetObject(obj);

            new (_ptr) OtherTypeT(obj);
        }

        template <typename OtherTypeT>
        void _SetObject(OtherTypeT&& obj) noexcept
        {
            __SetObject(obj);

            new (_ptr) OtherTypeT(move(obj));
        }

    /// ----------------------------------------------------------------------------
    protected:
        using BaseT::_allocator;
        using BaseT::_ptr;

        byte _stackMem[StackSize];
        sizet _objectSize = 0;
    };
}