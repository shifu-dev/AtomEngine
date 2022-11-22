#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Callable/Callable.hpp"
#include "AtomEngine/Memory/BoxedObject.hpp"
#include "AtomEngine/Memory/DefaultAllocator.hpp"

namespace Atom
{
    template <typename TResult, typename... TArgs> class BoxedCallable;
    template <typename TResult, typename... TArgs>
    class BoxedCallable<TResult(TArgs...)> :
        public Callable<TResult(TArgs...)>,
        public BoxedObject<DefaultAllocator, 50>
    {
        mprivate using ThisT = BoxedCallable<TResult(TArgs...)>;
        mprotected using CallableT = Callable<TResult(TArgs...)>;
        mprotected using BoxedObjectT = BoxedObject<DefaultAllocator, 50>;

        /// ----------------------------------------------------------------------------

        mpublic BoxedCallable() = default;
        mpublic BoxedCallable(const ThisT ref other) = default;
        mpublic BoxedCallable(ThisT rref other) = default;
        mpublic ThisT ref operator = (const ThisT ref other) = default;
        mpublic ThisT ref operator = (ThisT rref other) = default;

        mpublic template <typename TCallable>
            BoxedCallable(const TCallable ref callable) :
            BoxedObjectT(callable)
        {
            StaticAssertSubClass<CallableT, TCallable>();
        }

        mpublic template <typename TCallable>
            BoxedCallable(TCallable rref callable) :
            BoxedObjectT(move(callable))
        {
            StaticAssertSubClass<CallableT, TCallable>();
        }

        mpublic template <typename TCallable>
            ThisT ref operator = (const TCallable ref callable)
        {
            StaticAssertSubClass<CallableT, TCallable>();
            BoxedObjectT::operator = (callable);

            return ptr this;
        }

        mpublic template <typename TCallable>
            ThisT ref operator = (TCallable rref callable)
        {
            StaticAssertSubClass<CallableT, TCallable>();
            BoxedObjectT::operator = (move(callable));

            return ptr this;
        }

        /// ----------------------------------------------------------------------------

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