#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/ICollection.hpp"
#include "AtomEngine/Containers/IConstList.hpp"
#include "AtomEngine/Containers/InitializerList.hpp"

namespace Atom
{
    /// IList represents an array like structure, where elements 
    /// can be accessed using their index value.
    /// 
    /// @tparam ElementT Type of element this container stores.
    template <typename ElementT>
    interface IList:
        public virtual IConstList<ElementT>,
        public virtual ICollection<ElementT>
    {
        using ConstElementT = const ElementT;
        using ConstIterableT = IConstIterable<ElementT>;
        using ConstCollectionT = IConstCollection<ElementT>;
        using ConstListT = IConstList<ElementT>;
        using ForwardIteratorT = IForwardIterator<ElementT>;
        using EqualityComparerT = IEqualityComparer<ElementT>;
        using DefaultEqualityComparerT = DefaultEqualityComparer<ElementT>;
        using PredicateT = IPredicate<ConstElementT&, sizet>;

    /// ----------------------------------------------------------------------------
    public:

        /// @copydoc IConstList::operator[](sizet index)
        virtual ElementT& operator[](sizet index) noexcept abstract;

        /// @copydoc IConstList::ElementAt[](sizet index)
        virtual ElementT& ElementAt(sizet index)
        {
            _AssertIndexIsInBounds(index);
            return operator [] (index);
        }

        /// @copydoc IConstList::ElementFront()
        ElementT& ElementFront()
        {
            return ElementAt(0);
        }

        /// @copydoc IConstList::ElementBack()
        ElementT& ElementBack()
        {
            return ElementAt(Count() - 1);
        }

    /// ----------------------------------------------------------------------------

        /// Inserts element at index \p{index}.
        /// 
        /// @param[in] index Index to insert element at.
        /// @param[in] element Element to insert.
        /// 
        /// @throws OutOfBoundsException if index == out of bounds.
        virtual void InsertAt(sizet index, ConstElementT& element) abstract;

        /// Insert multiple elements at index \p{index}.
        /// 
        /// @param[in] index Index to insert elements at.
        /// @param[in] it IForwardIterator pointing to the begining of elements.
        /// @param[in] count Count of elements to insert.
        virtual void InsertAt(sizet index, const ForwardIteratorT& it, sizet count) abstract;

        /// Insert multiple elements at index \p{index}.
        /// 
        /// Counts the number of elements first, using iterators.
        /// 
        /// @param index Index to insert elements at.
        /// @param begin IForwardIterator pointing to the begining of elements.
        /// @param end IForwardIterator pointing to the end of elements.
        virtual void InsertAt(sizet index, const ForwardIteratorT& begin, const ForwardIteratorT& end)
        {
            sizet count = 0;
            for (auto& it = begin; it != end; ++it)
            {
                count++;
            }

            InsertAt(index, begin, count);
        }

        /// Inserts \p{count} elements from IConstIterable \p{elements} at index \p{index}.
        /// 
        /// @param index Index to insert elements at.
        /// @param elements IConstIterable to insert elements from.
        /// @param count Count of elements to insert.
        /// 
        /// @note
        /// - Calls InsertAt(sizet index, const ForwardIteratorT & begin, sizet count)
        ///   with begin: elements.Begin(), count: count.
        virtual void InsertAt(sizet index, const ConstIterableT& elements, sizet count)
        {
            InsertAt(index, elements.Begin(), count);
        }

        /// Inserts all elements from IConstIterable \p{elements} at index \p{index}.
        /// 
        /// @param[in] index Index to insert elements at.
        /// @param[in] elements IConstIterable to insert elements from.
        /// 
        /// @note
        /// - Calls InsertAt(sizet index, const ForwardIteratorT & begin, const ForwardIteratorT & end)
        ///   with begin: elements.Begin(), end: elements.End().
        virtual void InsertAt(sizet index, const ConstIterableT& elements)
        {
            InsertAt(index, elements.Begin(), elements.End());
        }

        /// Inserts all elements from IConstCollection \p{elements}.
        /// 
        /// This function == preferred over InsertAt(sizet index, const ConstIterableT & elements)
        /// becuase IConstCollection provides function IConstCollection::Count() 
        /// which specifies the count of elements to insert. This helps to preallocate 
        /// memory instead of checking on each iteration.
        /// 
        /// @param[in] index Index to insert elements at.
        /// @param[in] elements IConstCollection reference to insert elements from.
        /// 
        /// @exceptsafe
        /// \p{Strong Exception Safety}
        /// 
        /// @note
        /// - Calls InsertAt(sizet index, const ConstIterableT & elements, sizet count)
        ///   with index: index, elements: SCAST(const ConstIterableT &, elements), count: elements.Count().
        virtual void InsertAt(sizet index, const ConstCollectionT& elements)
        {
            InsertAt(index, SCAST(const ConstIterableT&, elements), elements.Count());
        }

        /// Inserts multiple elements at index \p{index}.
        /// 
        /// @tparam ElementTs ... Elements to insert.
        /// @param index Index to insert elements at.
        /// 
        /// @note
        /// - Calls InsertAt(sizet index, const ForwardIteratorT & it, sizet count).
        ///   with index: index, it: ArrayIterator(elements), count: "count of elements";
        template <ElementT... ElementTs>
        void InsertAt(sizet index)
        {
            constexpr ElementT elements{ ElementTs... };
            InsertAt(index, ArrayIterator(elements), sizeof...(ElementTs));
        }

        /// Inserts element at begining.
        /// 
        /// @param[in] element Element to insert.
        /// 
        /// @note
        /// - Calls InsertAt(sizet index, ConstElementT & element)
        ///   \n with \p{index}: 0, \p{element}: element.
        virtual void InsertFront(ConstElementT& element)
        {
            InsertAt(0, element);
        }

        /// - Calls InsertAt(sizet index, const ForwardIteratorT & it, sizet count).
        ///   with index: 0, it: it, count: count.
        virtual void InsertFront(const ForwardIteratorT& it, sizet count)
        {
            InsertAt(0, it, count);
        }

        /// - Calls InsertAt(sizet index, const ForwardIteratorT & begin, const ForwardIteratorT & end).
        ///   with index: 0, begin: begin, end: end.
        virtual void InsertFront(const ForwardIteratorT& begin, const ForwardIteratorT& end)
        {
            InsertAt(0, begin, end);
        }

        /// - Calls InsertAt(sizet index, const ConstIterableT & elements, sizet count).
        ///   with index: 0, elements: elements, count: count.
        virtual void InsertFront(const ConstIterableT& elements, sizet count)
        {
            InsertAt(0, elements, count);
        }

        /// - Calls InsertAt(sizet index, const ConstIterableT & elements, sizet count).
        ///   with index: 0, elements: elements, count: count.
        virtual void InsertFront(const ConstIterableT& elements)
        {
            InsertAt(0, elements);
        }

        /// - Calls InsertAt(sizet index, const ConstCollectionT & elements).
        ///   with index: 0, elements: elements.
        virtual void InsertFront(const ConstCollectionT& elements)
        {
            InsertAt(0, elements);
        }

        /// - Calls InsertAt<ElementTs...>(sizet index).
        ///   with ElementTs...: ElementTs... \n
        ///   with index: 0.
        template <ElementT... ElementTs>
        void InsertFront(sizet index)
        {
            InsertAt<ElementTs...>(0);
        }

        /// Inserts element at last.
        /// 
        /// @param[in] element Element to insert.
        /// 
        /// @note
        /// - Calls InsertAt(sizet index, ConstElementT & element)
        ///   \n with \p{index}: Count() - 1, \p{element}: element.
        virtual void InsertBack(ConstElementT& element)
        {
            InsertAt(Count() - 1, element);
        }

        /// - Calls InsertAt(sizet index, const ForwardIteratorT & it, sizet count).
        ///   with index: Count() - 1, it: it, count: count.
        virtual void InsertBack(const ForwardIteratorT& it, sizet count)
        {
            InsertAt(Count() - 1, it, count);
        }

        /// - Calls InsertAt(sizet index, const ForwardIteratorT & begin, const ForwardIteratorT & end).
        ///   with index: Count() - 1, begin: begin, end: end.
        virtual void InsertBack(const ForwardIteratorT& begin, const ForwardIteratorT& end)
        {
            InsertAt(Count() - 1, begin, end);
        }

        /// - Calls InsertAt(sizet index, const ConstIterableT & elements, sizet count).
        ///   with index: Count() - 1, elements: elements, count: count.
        virtual void InsertBack(const ConstIterableT& elements, sizet count)
        {
            InsertAt(Count() - 1, elements, count);
        }

        /// - Calls InsertAt(sizet index, const ConstIterableT & elements, sizet count).
        ///   with index: Count() - 1, elements: elements, count: count.
        virtual void InsertBack(const ConstIterableT& elements)
        {
            InsertAt(Count() - 1, elements);
        }

        /// - Calls InsertAt(sizet index, const ConstCollectionT & elements).
        ///   with index: Count() - 1, elements: elements.
        virtual void InsertBack(const ConstCollectionT& elements)
        {
            InsertAt(Count() - 1, elements);
        }

        /// - Calls InsertAt<ElementTs...>(sizet index).
        ///   with ElementTs...: ElementTs... \n
        ///   with index: Count() - 1.
        template <ElementT... ElementTs>
        void InsertBack(sizet index)
        {
            InsertAt<ElementTs...>(Count() - 1);
        }

    /// ----------------------------------------------------------------------------

        /// Removes the element at index.
        /// 
        /// @param[in] index Index of the element to remove.
        virtual void RemoveAt(sizet index) abstract;

        /// Removes the element at begining.
        /// 
        /// @note
        /// - Calls RemoveAt(sizet index)
        ///   with index: 0.
        virtual void RemoveFront()
        {
            RemoveAt(0);
        }

        /// Removes the element at end.
        /// 
        /// @note
        /// - Calls RemoveAt(sizet index)
        ///   with index: Count() - 1.
        virtual void RemoveBack()
        {
            RemoveAt(Count() - 1);
        }

        /// Removes the first element matching element \p{element}.
        /// 
        /// @note
        /// - Calls FirstIndexOf(ConstElementT & element, const EqualityComparerT comparer)
        ///   with element: element, comparer: comparer
        ///   to find the element to remove.
        /// 
        /// - Calls RemoveAt(sizet index)
        ///   with index: FindFirstOf(element, comparer) if \p{index != NPOS}.
        virtual void RemoveFront(ConstElementT& element, const EqualityComparerT& comparer)
        {
            if (sizet index = FirstIndexOf(element, comparer) != NPOS)
            {
                RemoveAt(index);
            }
        }

        /// @note 
        /// - Calls RemoveFront(ConstElementT & element, const EqualityComparerT & comparer)
        ///   with element: element, comparer: DefaultEqualityComparerT().
        virtual void RemoveFront(ConstElementT& element)
        {
            RemoveFront(element, DefaultEqualityComparerT());
        }

        /// Removes the last element matching element \p{element}.
        /// 
        /// @note
        /// - Calls LastIndexOf(ConstElementT & element, const EqualityComparerT comparer)
        ///   with element: element, comparer: comparer
        ///   to find the element to remove.
        /// 
        /// - Calls RemoveAt(sizet index)
        ///   with index: FindFirstOf(element, comparer) if \p{index != NPOS}.
        virtual void RemoveBack(ConstElementT& element, const EqualityComparerT& comparer)
        {
            if (sizet index = LastIndexOf(element, comparer) != NPOS)
            {
                RemoveAt(index);
            }
        }

        /// @note 
        /// - Calls RemoveBack(ConstElementT & element, const EqualityComparerT & comparer)
        ///   with element: element, comparer: DefaultEqualityComparerT().
        virtual void RemoveBack(ConstElementT& element)
        {
            RemoveBack(element, DefaultEqualityComparerT());
        }

        /// Removes elements from index \p{from} to index \p{to}.
        /// 
        /// @param from Starting index of the section to remove.
        /// @param to Last index of the section to remove.
        virtual void RemoveFrom(sizet from, sizet to) abstract;

        /// Removes elements from index \p{from} to the end of container.
        /// 
        /// @param from Starting index of the section to remove.
        /// 
        /// @note
        /// - Calls RemoveFrom(sizet from, sizet to)
        ///   with from: from, to: Count() - 1.
        virtual void RemoveFrom(sizet from)
        {
            RemoveFrom(from, Count() - 1);
        }

        /// Removes single element if IPredicate \p{pred} returns true.
        /// 
        /// @param pred IPredicate to check whether to remove element or not.
        virtual void RemoveIfCallable(const PredicateT& pred) noexcept abstract;

        /// Helper function for RemoveIfCallable(const PredicateT & pred).
        /// 
        /// @tparam FunctorT Type of functor object. This object == wrapped using ICallable.
        /// @param func Functor object.
        /// 
        /// @note
        /// - Wraps functor object \p{func} using PredicateT::Create(func) and 
        ///   Calls RemoveIfCallable(const PredicateT & pred)
        ///   with pred: PredicateT::Create(func).
        template <typename FunctorT>
        void RemoveIf(const FunctorT& func) noexcept
        {
            RemoveIfCallable(PredicateT::Create(func));
        }

    /// ----------------------------------------------------------------------------
    /// ICollection

        void Clear() final
        {
            RemoveFrom(0);
        }

        /// Inserts element at last.
        /// 
        /// @param[in] element Element to insert.
        /// 
        /// @note
        /// - Calls InsertBack(ConstElementT & element)
        ///   \n with \p{element}: element.
        void Insert(ConstElementT& element) final
        {
            InsertBack(element);
        }

        /// Removes element from last.
        /// 
        /// @note 
        /// - Calls RemoveBack(ConstElementT & element)
        ///   with element: element.
        void Remove(ConstElementT& element) final
        {
            RemoveBack(element);
        }

    /// ----------------------------------------------------------------------------
    public:
        using ConstListT::FirstIndexOf;
        using ConstListT::LastIndexOf;
        using ConstListT::Count;

    protected:
        using ConstListT::_AssertIndexIsInBounds;
    };
}