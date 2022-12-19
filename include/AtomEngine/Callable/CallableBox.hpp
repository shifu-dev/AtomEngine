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
        public TObjectBox<DefaultAllocator, 50>
    {
        mprivate using ThisT = CallableBox<TResult(TArgs...)>;
        mprotected using BaseT = TObjectBox<DefaultAllocator, 50>;
        mprotected using CallableT = ICallable<TResult(TArgs...)>;

        /// ----------------------------------------------------------------------------

        mpublic CallableBox() = default;
        mpublic CallableBox(const ThisT ref other) = default;
        mpublic CallableBox(ThisT rref other) = default;
        mpublic ThisT ref operator = (const ThisT ref other) = default;
        mpublic ThisT ref operator = (ThisT rref other) = default;

        mpublic template <typename TCallable>
            CallableBox(const TCallable ref callable) :
            BaseT(callable)
        {
            StaticAssertSubClass<CallableT, TCallable>();
        }

        mpublic template <typename TCallable>
            CallableBox(TCallable rref callable) :
            BaseT(move(callable))
        {
            StaticAssertSubClass<CallableT, TCallable>();
        }

        mpublic template <typename TCallable>
            ThisT ref operator = (const TCallable ref callable)
        {
            StaticAssertSubClass<CallableT, TCallable>();
            BaseT::operator = (callable);

            return ptr this;
        }

        mpublic template <typename TCallable>
            ThisT ref operator = (TCallable rref callable)
        {
            StaticAssertSubClass<CallableT, TCallable>();
            BaseT::operator = (move(callable));

            return ptr this;
        }

        /// ----------------------------------------------------------------------------

        mpublic CallableT ref GetCallable() noexcept
        {
            return BaseT::GetObject<CallableT>();
        }

        mpublic const CallableT ref GetCallable() const noexcept
        {
            return BaseT::GetObject<CallableT>();
        }

        mpublic virtual TResult Invoke(TArgs rref ... args) const override
        {
            return GetCallable().Invoke(forward<TArgs>(args)...);
        }
    };
}