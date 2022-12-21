#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Callable/ICallable.hpp"
#include "AtomEngine/Memory/UniqueBox.hpp"
#include "AtomEngine/Memory/DefaultAllocator.hpp"

namespace Atom
{
    template <typename ResultT, typename... ArgsT> class CallableBox;
    template <typename ResultT, typename... ArgsT>
    class CallableBox<ResultT(ArgsT...)>: public TUniqueBox<ICallable<ResultT(ArgsT...)>, 50>,
        public virtual ICallable<ResultT(ArgsT...)>
    {
        using ThisT = CallableBox<ResultT(ArgsT...)>;
        using BaseT = TUniqueBox<ICallable<ResultT(ArgsT...)>, 50>;
        using CallableT = ICallable<ResultT(ArgsT...)>;

    /// ----------------------------------------------------------------------------
    public:
        CallableBox() = default;

        CallableBox(const ThisT& other) = default;
        CallableBox(ThisT&& other) = default;

        ThisT& operator = (const ThisT& other) = default;
        ThisT& operator = (ThisT&& other) = default;

        template <typename CallableT>
        CallableBox(const CallableT& callable):
            BaseT(callable)
        {
            StaticAssertSubClass<CallableT, CallableT>();
        }

        template <typename CallableT>
        CallableBox(CallableT&& callable):
            BaseT(move(callable))
        {
            StaticAssertSubClass<CallableT, CallableT>();
        }

        template <typename CallableT>
        ThisT& operator = (const CallableT& callable)
        {
            StaticAssertSubClass<CallableT, CallableT>();
            BaseT::operator = (callable);

            return *this;
        }

        template <typename CallableT>
        ThisT& operator = (CallableT&& callable)
        {
            StaticAssertSubClass<CallableT, CallableT>();
            BaseT::operator = (move(callable));

            return *this;
        }

        ~CallableBox() = default;

    /// ----------------------------------------------------------------------------
    public:
        CallableT& GetCallable() noexcept
        {
            return BaseT::operator * ();
        }

        const CallableT& GetCallable() const noexcept
        {
            return BaseT::operator * ();
        }

        ResultT Invoke(ArgsT && ... args) const final
        {
            return GetCallable().Invoke(forward<ArgsT>(args)...);
        }
    };
}