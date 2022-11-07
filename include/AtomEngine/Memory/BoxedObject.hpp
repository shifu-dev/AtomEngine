#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Memory/Core.hpp"
#include "AtomEngine/Reflection/Core.hpp"

namespace Atom
{
    namespace Core
    {
        class BoxedObjectIdentifier { };
    }

    template <typename TAllocator, sizet TStackSize>
    class BoxedObject : public Core::BoxedObjectIdentifier
    {
        mprivate using ThisT = BoxedObject<TAllocator, TStackSize>;
        mprivate using IdentifierT = Core::BoxedObjectIdentifier;
        mprivate using AllocatorT = TAllocator;
        mprivate constexpr static sizet StackSize = TStackSize;

        mprivate template <typename T>
            constexpr static bool IsBoxedObject = IsSubClass<IdentifierT, T>;

        ////////////////////////////////////////////////////////////////////////////////

        mpublic BoxedObject() : ThisT(null) { }

        mpublic BoxedObject(nullt value) :
            mObject(null), mObjectSize(0), mObjectDestructor(null) { }

        mpublic BoxedObject(const ThisT ref other) noexcept
        {
            mCopy(other);
        }

        mpublic template <sizet TOtherStackSize>
            BoxedObject(const BoxedObject<TAllocator, TOtherStackSize> ref other) noexcept
        {
            mCopy(other);
        }

        mpublic BoxedObject(ThisT rref other) noexcept
        {
            mSwap(other);
        }

        mpublic template <sizet TOtherStackSize>
            BoxedObject(BoxedObject<TAllocator, TOtherStackSize> rref other) noexcept
        {
            mSwap(other);
        }

        mpublic ThisT ref operator = (const ThisT ref other) noexcept
        {
            ThisT tmp(other);
            mSwap(tmp);

            return ptr this;
        }

        mpublic template <sizet TOtherStackSize>
            ThisT ref operator = (const BoxedObject<TAllocator, TOtherStackSize> ref other) noexcept
        {
            ThisT tmp(other);
            mSwap(tmp);

            return ptr this;
        }

        mpublic ThisT ref operator = (ThisT rref other) noexcept
        {
            ThisT tmp(move(other));
            mSwap(tmp);

            return ptr this;
        }

        mpublic template <sizet TOtherStackSize>
            ThisT ref operator = (BoxedObject<TAllocator, TOtherStackSize> rref other) noexcept
        {
            ThisT tmp(move(other));
            mSwap(tmp);

            return ptr this;
        }

        mpublic template <typename TObject, EnableIf<not IsBoxedObject<TObject>> = false>
            BoxedObject(const TObject ref object) noexcept
        {
            SetObject(object);
        }

        mpublic template <typename TObject, EnableIf<not IsBoxedObject<TObject>> = false>
            BoxedObject(TObject rref object) noexcept
        {
            SetObject(move(object));
        }

        mpublic dtor BoxedObject()
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

        ////////////////////////////////////////////////////////////////////////////////

        mpublic template <typename TObject>
            void SetObject(const TObject ref object) noexcept
        {
            mSetObject(object);

            new (mObject) TObject(object);
        }

        mpublic template <typename TObject>
            void SetObject(TObject rref object) noexcept
        {
            mSetObject(object);

            new (mObject) TObject(move(object));
        }

        mpublic template <typename TObject>
            TObject ref GetObject() noexcept
        {
            return ptr rcast<TObject ptr>(mObject);
        }

        mpublic template <typename TObject>
            const TObject ref GetObject() const noexcept
        {
            return ptr rcast<const TObject ptr>(mObject);
        }

        mpublic const memptr GetRawObject() const noexcept
        {
            return mObject;
        }

        mpublic memptr GetRawObject() noexcept
        {
            return mObject;
        }

        ////////////////////////////////////////////////////////////////////////////////

        mprotected memptr mAllocMem(const sizet size) noexcept
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

        mprotected void mDestroyObject() noexcept
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

        mprotected template <typename TObject>
            void mSetObject(const TObject ref object) noexcept
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
        mprotected template <sizet TOtherStackSize>
            void mCopy(const BoxedObject<TAllocator, TOtherStackSize> ref other) noexcept
        {
            mObject = mAllocMem(other.mObjectSize);
            mObjectSize = other.mObjectSize;
            mObjectDestructor = other.mObjectDestructor;

            memcpy(mObject, other.mObject, mObjectSize);
        }

        mprotected template <sizet TOtherStackSize>
            void mSwap(BoxedObject<TAllocator, TOtherStackSize> ref other) noexcept
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

        ////////////////////////////////////////////////////////////////////////////////

        mprotected byte mStackMem[StackSize];
        mprotected AllocatorT mAllocator;

        mprotected memptr mObject = null;
        mprotected void (ptr mObjectDestructor) (const memptr object);
        mprotected sizet mObjectSize;
    };
}