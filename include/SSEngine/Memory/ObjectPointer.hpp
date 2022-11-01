#pragma once
#include "SSEngine/Core.hpp"
#include "SSEngine/Memory/Core.hpp"

namespace SSEngine
{
    template <typename TObject, typename TAllocator, sizet TStackSize>
    class ObjectPointer
    {
        using ThisT = ObjectPointer<TObject, TAllocator, TStackSize>;
        using ObjectT = TObject;
        using AllocatorT = TAllocator;
        constexpr static sizet StackSize = TStackSize;

    public:

        template <typename TOtherObject>
        ObjectPointer(const TOtherObject lref object) noexcept
        {
            mSetObject(lref object, sizeof(TOtherObject));
            new (mObject) TOtherObject(object);
        }

        template <typename TOtherObject>
        ObjectPointer(TOtherObject rref object) noexcept
        {
            mSetObject(lref object, sizeof(TOtherObject));
            new (mObject) TOtherObject(move(object));
        }

        template <typename TOtherObject, sizet TOtherStackSize>
        ObjectPointer(const ObjectPointer<TOtherObject, TAllocator, TOtherStackSize> lref objPointer) noexcept
        {
            mSetObject(objPointer.mObject, objPointer.mObjectSize);
            new (mObject) TOtherObject(objPointer.mObject);
        }

        template <typename TOtherObject, sizet TOtherStackSize>
        ObjectPointer(ObjectPointer<TOtherObject, TAllocator, TOtherStackSize> rref objPointer) noexcept
        {
            swap(mObjectSize, objPointer.mObjectSize);
            swap(mAllocator, objPointer.mAllocator);

            // if obj is allocated on stack memory
            if (objPointer.mObject iseq objPointer.mStackMemory)
            {
                mObject = dcast<ObjectT ptr>(mStackMemory);
                new (mObject) TOtherObject(move(objPointer.mObject));
            }
            else
            {
                mObject = objPointer.mObject;
            }
        }

        template <typename TOtherObject, sizet TOtherStackSize>
        ThisT lref operator = (const ObjectPointer<TOtherObject, TAllocator, TOtherStackSize> lref objPointer) noexcept
        {
            mSetObject(objPointer.mObject, objPointer.mObjectSize);
            new (mObject) TOtherObject(objPointer.mObject);

            return ptr this;
        }

        template <typename TOtherObject, sizet TOtherStackSize>
        ThisT lref operator = (ObjectPointer<TOtherObject, TAllocator, TOtherStackSize> rref objPointer) noexcept
        {
            swap(mObjectSize, objPointer.mObjectSize);
            swap(mAllocator, objPointer.mAllocator);

            // if obj is allocated on stack memory
            if (objPointer.mObject iseq objPointer.mStackMemory)
            {
                mObject = dcast<ObjectT ptr>(mStackMemory);
                new (mObject) TOtherObject(move(objPointer.mObject));
            }
            else
            {
                mObject = objPointer.mObject;
            }

            return ptr this;
        }

        dtor ObjectPointer()
        {
            if (mObject isnot nullptr)
            {
                object->ObjecT::dtor ObjecT();

                if (mObject isnot mStackMemory)
                {
                    mAllocator.DeallocateRaw(mObject, mObjectSize);
                }
            }
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
        void mSetObject(const ObjectT ptr object, const sizet size) noexcept
        {
            mObjectSize = size;
            if (mObjectSize <= StackSize)
            {
                object = dcast<ObjectT ptr>(mStackMemory);
                return;
            }

            object = dcast<ObjectT ptr>(mAllocator.AllocateRaw(mObjectSize));
        }

    protected:
        byte mStackMemory[StackSize];
        AllocatorT mAllocator;

        ObjectT ptr mObject;
        sizet mObjectSize;
    };
}