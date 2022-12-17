#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Memory/Core.hpp"
#include "AtomEngine/Reflection/Core.hpp"

namespace Atom
{
    namespace Internal
    {
        class ObjectBoxIdentifier { };
    }

    template <typename AllocatorT, sizet StackSize>
    class ObjectBox: public Internal::ObjectBoxIdentifier
    {
        using ThisT = ObjectBox<AllocatorT, StackSize>;

        template <typename Type>
        constexpr static bool IsObjectBox =
            IsSubClass<Internal::ObjectBoxIdentifier, Type>;

    /// ----------------------------------------------------------------------------
    public:
        ObjectBox(): ThisT(null) { }

        ObjectBox(nullt value):
            mObject(null), mObjectSize(0), mObjectDestructor(null) { }

        ObjectBox(const ThisT& other) noexcept
        {
            mCopy(other);
        }

        template <sizet OtherStackSizeT>
        ObjectBox(const ObjectBox<AllocatorT, OtherStackSizeT>& other) noexcept
        {
            mCopy(other);
        }

        ObjectBox(ThisT&& other) noexcept
        {
            mSwap(other);
        }

        template <sizet OtherStackSizeT>
        ObjectBox(ObjectBox<AllocatorT, OtherStackSizeT>&& other) noexcept
        {
            mSwap(other);
        }

        ThisT& operator = (const ThisT& other) noexcept
        {
            ThisT tmp(other);
            mSwap(tmp);

            return *this;
        }

        template <sizet OtherStackSizeT>
        ThisT& operator = (const ObjectBox<AllocatorT, OtherStackSizeT>& other) noexcept
        {
            ThisT tmp(other);
            mSwap(tmp);

            return *this;
        }

        ThisT& operator = (ThisT&& other) noexcept
        {
            ThisT tmp(move(other));
            mSwap(tmp);

            return *this;
        }

        template <sizet OtherStackSizeT>
        ThisT& operator = (ObjectBox<AllocatorT, OtherStackSizeT>&& other) noexcept
        {
            ThisT tmp(move(other));
            mSwap(tmp);

            return *this;
        }

        template <typename TObject, EnableIf<not IsObjectBox<TObject>> = false>
        ObjectBox(const TObject& object) noexcept
        {
            SetObject(object);
        }

        template <typename TObject, EnableIf<not IsObjectBox<TObject>> = false>
        ObjectBox(TObject&& object) noexcept
        {
            SetObject(move(object));
        }

        template <typename TObject, EnableIf<not IsObjectBox<TObject>> = false>
        ThisT& operator = (const TObject& object) noexcept
        {
            SetObject(object);
        }

        template <typename TObject, EnableIf<not IsObjectBox<TObject>> = false>
        ThisT& operator = (TObject&& object) noexcept
        {
            SetObject(move(object));
        }

        dtor ObjectBox()
        {
            if (mObject isnot null)
            {
                mObjectDestructor(mObject);

                if (mObject isnot mStackMem)
                {
                    mAllocator.DeallocateRaw(mObject, mObjectSize);
                }
            }
        }

    public:
        template <typename TObject>
        void SetObject(const TObject& object) noexcept
        {
            mSetObject(object);

            new (mObject) TObject(object);
        }

        template <typename TObject>
        void SetObject(TObject&& object) noexcept
        {
            mSetObject(object);

            new (mObject) TObject(move(object));
        }

        template <typename TObject>
        TObject& GetObject() noexcept
        {
            return *RCAST(TObject*, mObject);
        }

        template <typename TObject>
        const TObject& GetObject() const noexcept
        {
            return *RCAST(const TObject*, mObject);
        }

        const memptr GetRawObject() const noexcept
        {
            return mObject;
        }

        memptr GetRawObject() noexcept
        {
            return mObject;
        }

    /// ----------------------------------------------------------------------------
    protected:
        memptr mAllocMem(const sizet size) noexcept
        {
            memptr mem = null;

            if (size isnot 0)
            {
                if (size <= StackSize)
                {
                    mem = mStackMem;
                }
                else
                {
                    mem = mAllocator.AllocateRaw(size);
                }
            }

            return mem;
        }

        void mDestroyObject() noexcept
        {
            if (mObject isnot null)
            {
                mObjectDestructor(mObject);

                if (mObject isnot mStackMem)
                {
                    mAllocator.DeallocateRaw(mObject, mObjectSize);
                }
            }

            mObjectSize = 0;
            mObject = null;
            mObjectDestructor = null;
        }

        template <typename TObject>
        void mSetObject(const TObject& object) noexcept
        {
            if (mObject isnot null)
            {
                mObjectDestructor(mObject);

                if (mObject isnot mStackMem)
                {
                    mAllocator.DeallocateRaw(mObject, mObjectSize);
                }
            }

            mObjectSize = sizeof(TObject);
            mObject = mAllocMem(mObjectSize);
            mObjectDestructor = null;
        }

        // does not destroys previous state,
        // assumes to be called from constructor
        template <sizet OtherStackSizeT>
        void mCopy(const ObjectBox<AllocatorT, OtherStackSizeT>& other) noexcept
        {
            mObject = mAllocMem(other.mObjectSize);
            mObjectSize = other.mObjectSize;
            mObjectDestructor = other.mObjectDestructor;

            memcpy(mObject, other.mObject, mObjectSize);
        }

        template <sizet OtherStackSizeT>
        void mSwap(ObjectBox<AllocatorT, OtherStackSizeT>& other) noexcept
        {
            byte mStackMemTmp[StackSize];

            // if our object is stored in stack memory, save if before swapping
            if (mObject is mStackMem)
            {
                memcpy(mStackMemTmp, mStackMem, mObjectSize);
            }

            swap(mAllocator, other.mAllocator);
            swap(mObject, other.mObject);
            swap(mObjectSize, other.mObjectSize);
            swap(mObjectDestructor, other.mObjectDestructor);

            if (mObject is other.mStackMem)
            {
                mObject = mAllocMem(mObjectSize);
                memcpy(mObject, other.mStackMem, mObjectSize);
            }

            if (other.mObject is mStackMem)
            {
                other.mObject = other.mAllocMem(other.mObjectSize);
                memcpy(other.mObject, mStackMemTmp, other.mObjectSize);
            }
        }

    /// ----------------------------------------------------------------------------
    protected:
        byte mStackMem[StackSize];
        AllocatorT mAllocator;

        memptr mObject = null;
        void (*mObjectDestructor) (const memptr object);
        sizet mObjectSize;
    };
}