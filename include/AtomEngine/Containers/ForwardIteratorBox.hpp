#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/IteratorBox.hpp"
#include "AtomEngine/Containers/IForwardIterator.hpp"

namespace Atom
{
    template <typename ElementT>
    class ForwardIteratorBox: public IteratorBox<ElementT>,
        public virtual IForwardIterator<ElementT>
    {
        using ThisT = ForwardIteratorBox<ElementT>;
        using BaseT = IteratorBox<ElementT>;
        using ForwardIteratorT = IForwardIterator<ElementT>;

    /// ----------------------------------------------------------------------------
    public:
        ForwardIteratorBox():
            BaseT(nullptr) { }

        ForwardIteratorBox(const ThisT& other) noexcept:
            BaseT(other) { }

        ForwardIteratorBox(ThisT&& other) noexcept:
            BaseT(move(other)) { }

        ThisT& operator = (const ThisT& other) noexcept
        {
            BaseT::operator = (other);
            return *this;
        }

        ThisT& operator = (ThisT&& other) noexcept
        {
            BaseT::operator = (move(other));
            return *this;
        }

        template <typename ParamFwdIteratorT>
        ForwardIteratorBox(const ParamFwdIteratorT& iterator) noexcept:
            BaseT(iterator)
        {
            StaticAssertSubClass<ForwardIteratorT, ParamFwdIteratorT>();
        }

        template <typename ParamFwdIteratorT>
        ForwardIteratorBox(ParamFwdIteratorT&& iterator) noexcept:
            BaseT(move(iterator))
        {
            StaticAssertSubClass<ForwardIteratorT, ParamFwdIteratorT>();
        }

    /// ----------------------------------------------------------------------------
    public:
        ForwardIteratorT& GetIterator() noexcept
        {
            return RCAST(ForwardIteratorT&, BaseT::GetIterator());
        }

        const ForwardIteratorT& GetIterator() const noexcept
        {
            return RCAST(const ForwardIteratorT&, BaseT::GetIterator());
        }

        virtual void MoveFwd() const noexcept override
        {
            GetIterator().MoveFwd();
        }

    /// ----------------------------------------------------------------------------

        operator BaseT () const noexcept
        {
            return BaseT(*this);
        }
    };
}