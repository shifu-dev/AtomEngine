#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Reflection/Core.hpp"
#include "AtomEngine/Memory/Core.hpp"

namespace Atom
{
    namespace Internal
    {
        class ObjectBoxIdentifier { };
    }

    template <typename AllocatorT, sizet StackSize>
    class TObjectBox: public Internal::ObjectBoxIdentifier
    {
        using ThisT = TObjectBox<AllocatorT, StackSize>;

        template <typename TypeT>
        constexpr static bool IsObjectBox =
            IsSubClass<Internal::ObjectBoxIdentifier, TypeT>;

    /// ----------------------------------------------------------------------------
    public:
        TObjectBox() noexcept:
            ThisT(nullptr) { }

        TObjectBox(NullT value) noexcept:
            _object(nullptr), _objectSize(0), _objectDestructor(nullptr) { }

        TObjectBox(const ThisT& other) noexcept
        {
            _Copy(other);
        }

        template <sizet OtherStackSizeT>
        TObjectBox(const TObjectBox<AllocatorT, OtherStackSizeT>& other) noexcept
        {
            _Copy(other);
        }

        TObjectBox(ThisT&& other) noexcept
        {
            _Swap(other);
        }

        template <sizet OtherStackSizeT>
        TObjectBox(TObjectBox<AllocatorT, OtherStackSizeT>&& other) noexcept
        {
            _Swap(other);
        }

        ThisT& operator = (const ThisT& other) noexcept
        {
            ThisT tmp(other);
            _Swap(tmp);

            return *this;
        }

        template <sizet OtherStackSizeT>
        ThisT& operator = (const TObjectBox<AllocatorT, OtherStackSizeT>& other) noexcept
        {
            ThisT tmp(other);
            _Swap(tmp);

            return *this;
        }

        ThisT& operator = (ThisT&& other) noexcept
        {
            ThisT tmp(move(other));
            _Swap(tmp);

            return *this;
        }

        template <sizet OtherStackSizeT>
        ThisT& operator = (TObjectBox<AllocatorT, OtherStackSizeT>&& other) noexcept
        {
            ThisT tmp(move(other));
            _Swap(tmp);

            return *this;
        }

        template <typename ObjectT, EnableIf<!IsObjectBox<ObjectT>> = 0>
        TObjectBox(const ObjectT& object) noexcept
        {
            SetObject(object);
        }

        template <typename ObjectT, EnableIf<!IsObjectBox<ObjectT>> = 0>
        TObjectBox(ObjectT&& object) noexcept
        {
            SetObject(move(object));
        }

        template <typename ObjectT, EnableIf<!IsObjectBox<ObjectT>> = 0>
        ThisT& operator = (const ObjectT& object) noexcept
        {
            SetObject(object);
        }

        template <typename ObjectT, EnableIf<!IsObjectBox<ObjectT>> = 0>
        ThisT& operator = (ObjectT&& object) noexcept
        {
            SetObject(move(object));
        }

        ~TObjectBox()
        {
            if (_object != nullptr)
            {
                _objectDestructor(_object);

                if (_object != _stackMem)
                {
                    _allocator.DeallocateRaw(_object, _objectSize);
                }
            }
        }

    public:
        template <typename ObjectT>
        void SetObject(const ObjectT& object) noexcept
        {
            _SetObject(object);

            new (_object) ObjectT(object);
        }

        template <typename ObjectT>
        void SetObject(ObjectT&& object) noexcept
        {
            _SetObject(object);

            new (_object) ObjectT(move(object));
        }

        template <typename ObjectT>
        ObjectT& GetObject() noexcept
        {
            return *RCAST(ObjectT*, _object);
        }

        template <typename ObjectT>
        const ObjectT& GetObject() const noexcept
        {
            return *RCAST(const ObjectT*, _object);
        }

        const memptr GetRawObject() const noexcept
        {
            return _object;
        }

        memptr GetRawObject() noexcept
        {
            return _object;
        }

    /// ----------------------------------------------------------------------------
    protected:
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
            if (_object != nullptr)
            {
                _objectDestructor(_object);

                if (_object != _stackMem)
                {
                    _allocator.DeallocateRaw(_object, _objectSize);
                }
            }

            _objectSize = 0;
            _object = nullptr;
            _objectDestructor = nullptr;
        }

        template <typename ObjectT>
        void _SetObject(const ObjectT& object) noexcept
        {
            if (_object != nullptr)
            {
                _objectDestructor(_object);

                if (_object != _stackMem)
                {
                    _allocator.DeallocateRaw(_object, _objectSize);
                }
            }

            _objectSize = sizeof(ObjectT);
            _object = _AllocMem(_objectSize);
            _objectDestructor = nullptr;
        }

        // does ! destroys previous state,
        // assumes to be called from constructor
        template <sizet OtherStackSizeT>
        void _Copy(const TObjectBox<AllocatorT, OtherStackSizeT>& other) noexcept
        {
            _object = _AllocMem(other._objectSize);
            _objectSize = other._objectSize;
            _objectDestructor = other._objectDestructor;

            memcpy(_object, other._object, _objectSize);
        }

        template <sizet OtherStackSizeT>
        void _Swap(TObjectBox<AllocatorT, OtherStackSizeT>& other) noexcept
        {
            byte tmpStackMem[StackSize];

            // if our object == stored in stack memory, save if before swapping
            if (_object == _stackMem)
            {
                memcpy(tmpStackMem, _stackMem, _objectSize);
            }

            swap(_allocator, other._allocator);
            swap(_object, other._object);
            swap(_objectSize, other._objectSize);
            swap(_objectDestructor, other._objectDestructor);

            if (_object == other._stackMem)
            {
                _object = _AllocMem(_objectSize);
                memcpy(_object, other._stackMem, _objectSize);
            }

            if (other._object == _stackMem)
            {
                other._object = other._AllocMem(other._objectSize);
                memcpy(other._object, tmpStackMem, other._objectSize);
            }
        }

    /// ----------------------------------------------------------------------------
    protected:
        byte _stackMem[StackSize];
        AllocatorT _allocator;

        memptr _object = nullptr;
        void (*_objectDestructor) (const memptr object);
        sizet _objectSize;
    };
}