#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Callable/ICallable.hpp"
#include "AtomEngine/Memory/ObjectBox.hpp"
#include "AtomEngine/Memory/DefaultAllocator.hpp"

namespace Atom
{
    template <typename TResult, typename... TArgs> class CallableBox;
    template <typename TResult, typename... TArgs>
    class CallableBox<TResult(TArgs...)> :
        public ICallable<TResult(TArgs...)>,
        public ObjectBox<DefaultAllocator, 50>
    {
        mprivate using ThisT = CallableBox<TResult(TArgs...)>;
        mprotected using CallableT = ICallable<TResult(TArgs...)>;
        mprotected using ObjectBoxT = ObjectBox<DefaultAllocator, 50>;

        /// ----------------------------------------------------------------------------

        mpublic CallableBox() = default;
        mpublic CallableBox(const ThisT ref other) = default;
        mpublic CallableBox(ThisT rref other) = default;
        mpublic ThisT ref operator = (const ThisT ref other) = default;
        mpublic ThisT ref operator = (ThisT rref other) = default;

        mpublic template <typename TCallable>
            CallableBox(const TCallable ref callable) :
            ObjectBoxT(callable)
        {
            StaticAssertSubClass<CallableT, TCallable>();
        }

        mpublic template <typename TCallable>
            CallableBox(TCallable rref callable) :
            ObjectBoxT(move(callable))
        {
            StaticAssertSubClass<CallableT, TCallable>();
        }

        mpublic template <typename TCallable>
            ThisT ref operator = (const TCallable ref callable)
        {
            StaticAssertSubClass<CallableT, TCallable>();
            ObjectBoxT::operator = (callable);

            return ptr this;
        }

        mpublic template <typename TCallable>
            ThisT ref operator = (TCallable rref callable)
        {
            StaticAssertSubClass<CallableT, TCallable>();
            ObjectBoxT::operator = (move(callable));

            return ptr this;
        }

        /// ----------------------------------------------------------------------------

        mpublic CallableT ref GetCallable() noexcept
        {
            return ObjectBoxT::GetObject<CallableT>();
        }

        mpublic const CallableT ref GetCallable() const noexcept
        {
            return ObjectBoxT::GetObject<CallableT>();
        }

        mpublic virtual TResult Invoke(TArgs rref ... args) const override
        {
            return GetCallable().Invoke(forward<TArgs>(args)...);
        }
    };
}