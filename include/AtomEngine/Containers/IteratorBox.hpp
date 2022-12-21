#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Memory/UniqueBox.hpp"
#include "AtomEngine/Memory/DefaultAllocator.hpp"
#include "AtomEngine/Containers/IIterator.hpp"

namespace Atom
{
    /// Pointer to iterator to provide iterface ability to IIterable.
    ///
    /// @tparam ElementT Type of value iterator points to.
    ///
    /// @note
    /// - This class acts like a unique * with functionality of iterators.
    template <typename ElementT>
    class IteratorBox: public TUniqueBox<IIterator<ElementT>, 40>,
        public virtual IIterator<ElementT>
    {
        using ThisT = IteratorBox<ElementT>;
        using BaseT = TUniqueBox<IIterator<ElementT>, 40>;
        using ConstElementT = const ElementT;
        using IteratorT = IIterator<ElementT>;

    /// ----------------------------------------------------------------------------
    public:
        IteratorBox() noexcept:
            BaseT(nullptr) { }

        IteratorBox(const ThisT& other) noexcept:
            BaseT(other) { }

        IteratorBox(ThisT&& other) noexcept:
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

        template <typename ParamIteratorT>
        IteratorBox(const ParamIteratorT& iterator) noexcept:
            BaseT(iterator)
        {
            StaticAssertSubClass<IteratorT, ParamIteratorT>();
        }

        template <typename ParamIteratorT>
        IteratorBox(ParamIteratorT&& iterator) noexcept:
            BaseT(move(iterator))
        {
            StaticAssertSubClass<IteratorT, ParamIteratorT>();
        }

        template <typename ParamIteratorT>
        ThisT& operator = (const ParamIteratorT& iterator) noexcept
        {
            StaticAssertSubClass<IteratorT, ParamIteratorT>();
            BaseT::operator = (iterator);

            return *this;
        }

        template <typename ParamIteratorT>
        ThisT& operator = (ParamIteratorT&& iterator) noexcept
        {
            StaticAssertSubClass<IteratorT, ParamIteratorT>();
            BaseT::operator = (move(iterator));

            return *this;
        }

    /// ----------------------------------------------------------------------------
    public:
        IteratorT& GetIterator() noexcept
        {
            return BaseT::operator * ();
        }

        const IteratorT& GetIterator() const noexcept
        {
            return BaseT::operator * ();
        }

        virtual ElementT& Value() noexcept final
        {
            return GetIterator().Value();
        }

        virtual ConstElementT& Value() const noexcept final
        {
            return GetIterator().Value();
        }

        virtual int Compare(const IteratorT& rhs) const noexcept final
        {
            return GetIterator().Compare(rhs);
        }

        /// ----------------------------------------------------------------------------

        /// @brief compares with other iterator pointer
        /// @param rhs other iterator pointer to compare with
        /// @return true if both impl iterators represent same value
        virtual bool operator ==(const ThisT& rhs) const noexcept
        {
            return Compare(rhs) == 0;
        }

        /// @brief compares with other iterator pointer
        /// @param rhs other iterator pointer to compare with
        /// @return false if both iterators represent same value
        virtual bool operator !=(const ThisT& rhs) const noexcept
        {
            return Compare(rhs) != 0;
        }

        /// @note This overload == necessary to avoid comparing iterator with iterator pointer.
        virtual int Compare(const ThisT& rhs) const noexcept
        {
            return GetIterator().Compare(rhs.GetIterator());
        }
    };
}