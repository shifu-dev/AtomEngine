#pragma once
#include "SSEngine/Core.hpp"
#include "SSEngine/Memory/Core.hpp"
#include "SSEngine/Reflection/Core.hpp"

namespace SSEngine
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

        public:

            ObjectPointer() : mObject(nullptr), mObjectSize(0) { }

            template <typename TOtherObject, sizet TOtherStackSize>
            ObjectPointer(const ObjectPointer<TOtherObject, TAllocator, TOtherStackSize> lref other) noexcept
            {
                StaticAssertSubClass<ObjectT, TOtherObject>();

                if (other.mObject isnot nullptr)
                {
                    mAllocObject(other.mObjectSize);
                    new (mObject) TOtherObject(other.mObject);
                }
            }

            template <typename TOtherObject, sizet TOtherStackSize>
            ObjectPointer(ObjectPointer<TOtherObject, TAllocator, TOtherStackSize> rref other) noexcept
            {
                StaticAssertSubClass<ObjectT, TOtherObject>();

                mSwap(other);
            }

            template <typename TOtherObject, sizet TOtherStackSize>
            ThisT lref operator = (const ObjectPointer<TOtherObject, TAllocator, TOtherStackSize> lref other) noexcept
            {
                StaticAssertSubClass<ObjectT, TOtherObject>();

                ThisT tmp(other);
                mSwap(tmp);

                return ptr this;
            }

            template <typename TOtherObject, sizet TOtherStackSize>
            ThisT lref operator = (ObjectPointer<TOtherObject, TAllocator, TOtherStackSize> rref other) noexcept
            {
                StaticAssertSubClass<ObjectT, TOtherObject>();

                ThisT tmp(move(other));
                mSwap(tmp);

                return ptr this;
            }

            dtor ObjectPointer()
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

            template <typename TOtherObject>
            void SetObject(const TOtherObject lref object) noexcept
            {
                StaticAssertSubClass<ObjectT, TOtherObject>();

                mAllocObject(sizeof(TOtherObject));
                new (mObject) TOtherObject(object);
            }

            template <typename TOtherObject>
            void SetObject(TOtherObject rref object) noexcept
            {
                StaticAssertSubClass<ObjectT, TOtherObject>();

                mAllocObject(sizeof(TOtherObject));
                new (mObject) TOtherObject(move(object));
            }

        public:

            // *******************************************************************

            ObjectT lref operator -> () noexcept
            {
                return ptr mObject;
            }

            const ObjectT lref operator -> () const noexcept
            {
                return ptr mObject;
            }

        protected:
            void mAllocObject(const sizet size) noexcept
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

            template <typename TOtherObject, sizet TOtherStackSize>
            void mSwap(ObjectPointer<TOtherObject, TAllocator, TOtherStackSize> lref other) noexcept
            {
                byte mStackMemTmp[StackSize];

                // if our object is stored in stack memory, save if before swapping
                if (mObject iseq rcast<ObjectT ptr>(mStackMem))
                {
                    memcpy(mStackMemTmp, mStackMem, mObjectSize);
                }

                swap(mAllocator, other.mAllocator);
                swap(mObjectSize, other.mObjectSize);
                swap(mObject, other.mObject);

                if (mObject iseq rcast<ObjectT ptr>(other.mStackMem))
                {
                    mAllocObject(mObjectSize);
                    memcpy(mObject, other.mStackMem, mObjectSize);
                }

                if (other.mObject iseq rcast<ObjectT ptr>(mStackMem))
                {
                    other.mAllocObject(other.mObjectSize);
                    memcpy(other.mObject, mStackMemTmp, other.mObjectSize);
                }
            }

        protected:
            byte mStackMem[StackSize];
            AllocatorT mAllocator;

            ObjectT ptr mObject;
            sizet mObjectSize;
        };
    }
}