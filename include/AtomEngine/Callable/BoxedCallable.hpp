#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Memory/BoxedObject.hpp"
#include "AtomEngine/Memory/LegacyAllocator.hpp"
#include "AtomEngine/Callable/Callable.hpp"

namespace Atom
{
    template <typename TResult, typename... TArgs> class BoxedCallable;
    template <typename TResult, typename... TArgs>
    class BoxedCallable<TResult(TArgs...)> :
        public Callable<TResult(TArgs...)>,
        protected Core::BoxedObject<LegacyAllocator, 1000>
    {
        mprivate using ThisT = BoxedCallable<TResult(TArgs...)>;
        mprotected using CallableT = Callable<TResult(TArgs...)>;
        mprotected using BoxedObjectT = Core::BoxedObject<LegacyAllocator, 1000>;

        mpublic BoxedCallable() = default;
        mpublic BoxedCallable(const ThisT ref other) = default;
        mpublic BoxedCallable(ThisT rref other) = default;
        mpublic ThisT ref operator = (const ThisT ref other) = default;
        mpublic ThisT ref operator = (ThisT rref other) = default;

        mpublic template <typename TCallable>
            BoxedCallable(const TCallable ref callable)
        {
            StaticAssertSubClass<CallableT, TCallable>();
            BoxedObjectT::SetObject(callable);
        }

        mpublic template <typename TCallable>
            BoxedCallable(TCallable rref callable)
        {
            StaticAssertSubClass<CallableT, TCallable>();
            BoxedObjectT::SetObject(move(callable));
        }

        mpublic CallableT ref GetCallable() noexcept
        {
            return BoxedObjectT::GetObject<CallableT>();
        }

        mpublic const CallableT ref GetCallable() const noexcept
        {
            return BoxedObjectT::GetObject<CallableT>();
        }

        mpublic virtual TResult Invoke(TArgs rref ... args) const override
        {
            return GetCallable().Invoke(forward<TArgs>(args)...);
        }
    };
}