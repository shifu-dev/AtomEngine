#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Memory/Core.hpp"
#include "AtomEngine/Reflection/Core.hpp"

namespace Atom
{
    namespace Core
    {
        template <typename TObject, typename TAllocator, sizet TStackSize>
        class ObjectPointer
        {
            using ThisT = ObjectPointer<TObject, TAllocator, TStackSize>;
            using ObjectT = TObject;
            using AllocatorT = TAllocator;
            constexpr static sizet StackSize = TStackSize;

            mpublic ObjectPointer() : mObject(nullptr), mObjectSize(0) { }

            mpublic template <typename TOtherObject, sizet TOtherStackSize>
                ObjectPointer(const ObjectPointer<TOtherObject, TAllocator, TOtherStackSize> ref other) noexcept
            {
                StaticAssertSubClass<ObjectT, TOtherObject>();

                if (other.mObject isnot nullptr)
                {
                    mAllocObject(other.mObjectSize);
                    new (mObject) TOtherObject(other.mObject);
                }
            }

            mpublic template <typename TOtherObject, sizet TOtherStackSize>
                ObjectPointer(ObjectPointer<TOtherObject, TAllocator, TOtherStackSize> rref other) noexcept
            {
                StaticAssertSubClass<ObjectT, TOtherObject>();

                mSwap(other);
            }

            mpublic template <typename TOtherObject, sizet TOtherStackSize>
                ThisT ref operator = (const ObjectPointer<TOtherObject, TAllocator, TOtherStackSize> ref other) noexcept
            {
                StaticAssertSubClass<ObjectT, TOtherObject>();

                ThisT tmp(other);
                mSwap(tmp);

                return ptr this;
            }

            mpublic template <typename TOtherObject, sizet TOtherStackSize>
                ThisT ref operator = (ObjectPointer<TOtherObject, TAllocator, TOtherStackSize> rref other) noexcept
            {
                StaticAssertSubClass<ObjectT, TOtherObject>();

                ThisT tmp(move(other));
                mSwap(tmp);

                return ptr this;
            }

            mpublic dtor ObjectPointer()
            {
                if (mObject isnot nullptr)
                {
                    mObject->ObjectT::dtor ObjectT();

                    if (mObject isnot rcast<ObjectT ptr>(mStackMem))
                    {
                        mAllocator.DeallocateRaw(mObject, mObjectSize);
                    }
                }
            }

            mpublic template <typename TOtherObject>
                void SetObject(const TOtherObject ref object) noexcept
            {
                StaticAssertSubClass<ObjectT, TOtherObject>();

                mAllocObject(sizeof(TOtherObject));
                new (mObject) TOtherObject(object);
            }

            mpublic template <typename TOtherObject>
                void SetObject(TOtherObject rref object) noexcept
            {
                StaticAssertSubClass<ObjectT, TOtherObject>();

                mAllocObject(sizeof(TOtherObject));
                new (mObject) TOtherObject(move(object));
            }

            // *******************************************************************

            mpublic ObjectT ref operator -> () noexcept
            {
                return ptr mObject;
            }

            mpublic const ObjectT ref operator -> () const noexcept
            {
                return ptr mObject;
            }

            mprotected void mAllocObject(const sizet size) noexcept
            {
                mObjectSize = size;
                if (mObjectSize <= StackSize)
                {
                    mObject = rcast<ObjectT ptr>(mStackMem);
                    return;
                }

                memptr mem = mAllocator.AllocateRaw(mObjectSize);
                mObject = rcast<ObjectT ptr>(mem);
            }

            mprotected template <typename TOtherObject, sizet TOtherStackSize>
                void mSwap(ObjectPointer<TOtherObject, TAllocator, TOtherStackSize> ref other) noexcept
            {
                byte mStackMemTmp[StackSize];

                // if our object is stored in stack memory, save if before swapping
                if (mObject is rcast<ObjectT ptr>(mStackMem))
                {
                    memcpy(mStackMemTmp, mStackMem, mObjectSize);
                }

                swap(mAllocator, other.mAllocator);
                swap(mObjectSize, other.mObjectSize);
                swap(mObject, other.mObject);

                if (mObject is rcast<ObjectT ptr>(other.mStackMem))
                {
                    mAllocObject(mObjectSize);
                    memcpy(mObject, other.mStackMem, mObjectSize);
                }

                if (other.mObject is rcast<ObjectT ptr>(mStackMem))
                {
                    other.mAllocObject(other.mObjectSize);
                    memcpy(other.mObject, mStackMemTmp, other.mObjectSize);
                }
            }

            mprotected byte mStackMem[StackSize];
            mprotected AllocatorT mAllocator;

            mprotected ObjectT ptr mObject;
            mprotected sizet mObjectSize;
        };
    }
}