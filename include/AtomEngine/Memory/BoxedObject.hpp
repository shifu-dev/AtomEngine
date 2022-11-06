#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Memory/Core.hpp"
#include "AtomEngine/Reflection/Core.hpp"

namespace Atom
{
    template <typename TAllocator, sizet TStackSize>
    class BoxedObject
    {
        mprivate using ThisT = BoxedObject<TAllocator, TStackSize>;
        mprivate using AllocatorT = TAllocator;
        mprivate constexpr static sizet StackSize = TStackSize;

        ////////////////////////////////////////////////////////////////////////////////

        mprotected struct Object
        {
            mpublic memptr object;
            mpublic void (ptr destructor) (const memptr object);
            mpublic sizet size;

            Object() : Object(null) { }

            Object(nullt value)
            {
                object = null;
                destructor = null;
                size = 0;
            }

            mpublic template <typename TObject>
                Object(memptr mem, const TObject ref otherObject)
            {
                mSetObject<TObject>(mem);
                new (object) TObject(otherObject);
            }

            mpublic template <typename TObject>
                Object(memptr mem, TObject rref otherObject)
            {
                mSetObject<TObject>(mem);
                new (object) TObject(move(otherObject));
            }

            mpublic dtor Object()
            {
                if (destructor isnot null)
                {
                    destructor(object);
                }
            }

            mprivate template <typename TObject>
                void mSetObject(memptr mem)
            {
                object = mem;
                size = sizeof(TObject);
                destructor = [](const memptr object)
                {
                    (ptr rcast<const TObject ptr>(object)).
                        TObject::dtor TObject();
                };
            }
        };

        ////////////////////////////////////////////////////////////////////////////////

        mpublic BoxedObject() : mObject(nullptr) { }

        mpublic template <sizet TOtherStackSize>
            BoxedObject(const BoxedObject<TAllocator, TOtherStackSize> ref other) noexcept
        {
            if (other.mObject isnot nullptr)
            {
                mObject = Object(mAllocMem(other.mObject.size), other);
            }
        }

        mpublic template <sizet TOtherStackSize>
            BoxedObject(BoxedObject<TAllocator, TOtherStackSize> rref other) noexcept
        {
            mSwap(other);
        }

        mpublic template <sizet TOtherStackSize>
            ThisT ref operator = (const BoxedObject<TAllocator, TOtherStackSize> ref other) noexcept
        {
            ThisT tmp(other);
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

        mpublic dtor BoxedObject()
        {
            if (mObject.object isnot nullptr)
            {
                mObject.dtor Object();

                if (mObject.object isnot mStackMem)
                {
                    mAllocator.DeallocateRaw(mObject.object, mObject.size);
                }
            }
        }

        ////////////////////////////////////////////////////////////////////////////////

        mpublic template <typename TObject>
            static ThisT Box(const TObject ref object) noexcept
        {
            ThisT boxedObject;
            boxedObject.SetObject(object);
            return boxedObject;
        }

        mpublic template <typename TObject>
            static ThisT Box(TObject rref object) noexcept
        {
            ThisT boxedObject;
            boxedObject.SetObject(move(object));
            return boxedObject;
        }

        mpublic template <typename TObject>
            void SetObject(const TObject ref object) noexcept
        {
            mObject = Object(mAllocMem(sizeof(TObject)), object);
        }

        mpublic template <typename TObject>
            void SetObject(TObject rref object) noexcept
        {
            mObject = Object(mAllocMem(sizeof(TObject)), move(object));
        }

        ////////////////////////////////////////////////////////////////////////////////

        mpublic template <typename TObject>
            const TObject ref GetObject() const noexcept
        {
            return ptr scast<const TObject ptr>(mObject.object);
        }

        mpublic template <typename TObject>
            TObject ref GetObject() noexcept
        {
            return ptr scast<TObject ptr>(mObject.object);
        }

        mpublic const void ptr GetRawObject() const noexcept
        {
            return mObject.object;
        }

        mpublic void ptr GetRawObject() noexcept
        {
            return mObject.object;
        }

        ////////////////////////////////////////////////////////////////////////////////

        mprivate memptr mAllocMem(const sizet size) noexcept
        {
            memptr mem = nullptr;

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

        mprotected template <sizet TOtherStackSize>
            void mSwap(BoxedObject<TAllocator, TOtherStackSize> ref other) noexcept
        {
            byte mStackMemTmp[StackSize];

            // if our object is stored in stack memory, save if before swapping
            if (mObject.object is mStackMem)
            {
                memcpy(mStackMemTmp, mStackMem, mObject.size);
            }

            swap(mAllocator, other.mAllocator);
            swap(mObject, other.mObject);

            if (mObject.object is other.mStackMem)
            {
                mAllocMem(mObject.size);
                memcpy(mObject.object, other.mStackMem, mObject.size);
            }

            if (other.mObject.object is mStackMem)
            {
                other.mAllocMem(other.mObject.size);
                memcpy(other.mObject.object, mStackMemTmp, other.mObject.size);
            }
        }

        ////////////////////////////////////////////////////////////////////////////////

        mprotected byte mStackMem[StackSize];
        mprotected AllocatorT mAllocator;
        mprotected Object mObject;
    };
}