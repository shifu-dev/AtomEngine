#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/Collection.hpp"
#include "AtomEngine/Containers/ConstList.hpp"

namespace Atom
{
    /// List represents an array like structure, where elements 
    /// can be accessed using their index value.
    /// 
    /// @tparam TElement Type of element this container stores.
    template <typename TElement>
    class List : public virtual ConstList<TElement>, public virtual Collection<TElement>
    {
        using ElementT = TElement;                                             ///< ----
        using IterableT = Iterable<ElementT>;                                  ///< ----
        using CollectionT = Collection<ElementT>;                              ///< ----
        using ConstCollectionT = ConstCollection<ElementT>;                    ///< ----
        using ConstListT = ConstList<ElementT>;                                ///< ----
        using EqualityComparerT = EqualityComparer<ElementT>;                  ///< ----
        using DefaultEqualityComparerT = DefaultEqualityComparer<ElementT>;    ///< ----
        using ForwardIteratorT = ForwardIterator<ElementT>;                    ///< ----
        using PredicateT = Predicate<const ElementT ref, sizet>;               ///< ----

        mpublic using ConstListT::FirstIndexOf;
        mpublic using ConstListT::LastIndexOf;
        mpublic using ConstCollectionT::Count;
        mprotected using ConstListT::mAssertIndexIsInBounds;

        /// ----------------------------------------------------------------------------
        /// @copydoc ConstList::operator[](const sizet index)
        mpublic virtual ElementT ref operator[](const sizet index) noexcept abstract;

        /// ----------------------------------------------------------------------------
        /// @copydoc ConstList::ElementAt[](const sizet index)
        mpublic virtual ElementT ref ElementAt(const sizet index)
        {
            mAssertIndexIsInBounds(index);
            return operator [] (index);
        }

        /// ----------------------------------------------------------------------------
        /// @copydoc ConstList::ElementFront()
        mpublic ElementT ref ElementFront()
        {
            return ElementAt(0);
        }

        /// ----------------------------------------------------------------------------
        /// @copydoc ConstList::ElementBack()
        mpublic ElementT ref ElementBack()
        {
            return ElementAt(Count() - 1);
        }

        /// ----------------------------------------------------------------------------
        /// Inserts element at index \p{index}.
        /// 
        /// @param[in] index Index to insert element at.
        /// @param[in] element Element to insert.
        /// 
        /// @throws OutOfBoundsException if index is out of bounds.
        mpublic virtual void InsertAt(const sizet index, const ElementT ref element) abstract;

        /// Inserts element at begining.
        /// 
        /// @param[in] element Element to insert.
        /// 
        /// @note
        /// - Calls InsertAt(sizet index, const ElementT ref element)
        ///   \n with \p{index}: 0, \p{element}: element.
        mpublic virtual void InsertFront(const ElementT ref element)
        {
            InsertAt(0, element);
        }

        /// Inserts element at last.
        /// 
        /// @param[in] element Element to insert.
        /// 
        /// @note
        /// - Calls InsertAt(sizet index, const ElementT ref element)
        ///   \n with \p{index}: Count() - 1, \p{element}: element.
        mpublic virtual void InsertBack(const ElementT ref element)
        {
            InsertAt(Count() - 1, element);
        }

        /// Inserts element at last.
        /// 
        /// @param[in] element Element to insert.
        /// 
        /// @note
        /// - Calls InsertBack(const ElementT ref element)
        ///   \n with \p{element}: element.
        mpublic virtual void Insert(const ElementT ref element) override
        {
            InsertBack(element);
        }

        /// ----------------------------------------------------------------------------
        /// Insert multiple elements at index \p{index}.
        /// 
        /// @param[in] index Index to insert elements at.
        /// @param[in] it ForwardIterator pointing to the begining of elements.
        /// @param[in] count Count of elements to insert.
        mpublic virtual void InsertAt(const sizet index, const ForwardIteratorT ref it, const sizet count) abstract;

        /// ----------------------------------------------------------------------------
        /// Insert multiple elements at index \p{index}.
        /// 
        /// Counts the number of elements first, using iterators.
        /// 
        /// @param index Index to insert elements at.
        /// @param begin ForwardIterator pointing to the begining of elements.
        /// @param end ForwardIterator pointing to the end of elements.
        mpublic virtual void InsertAt(const sizet index, const ForwardIteratorT ref begin, const ForwardIteratorT ref end)
        {
            sizet count = 0;
            for (auto ref it = begin; it isnot end; ++it)
            {
                count++;
            }

            InsertAt(index, begin, count);
        }

        /// ----------------------------------------------------------------------------
        /// Inserts \p{count} elements from Iterable \p{elements} at index \p{index}.
        /// 
        /// @param index Index to insert elements at.
        /// @param elements Iterable to insert elements from.
        /// @param count Count of elements to insert.
        /// 
        /// @note
        /// - Calls InsertAt(const sizet index, const ForwardIteratorT ref begin, const sizet count)
        ///   with begin: elements.Begin(), count: count.
        mpublic virtual void InsertAt(const sizet index, const IterableT ref elements, const sizet count)
        {
            InsertAt(index, elements.Begin(), count);
        }

        /// ----------------------------------------------------------------------------
        /// Inserts all elements from Iterable \p{elements} at index \p{index}.
        /// 
        /// @param[in] index Index to insert elements at.
        /// @param[in] elements Iterable to insert elements from.
        /// 
        /// @note
        /// - Calls InsertAt(const sizet index, const ForwardIteratorT ref begin, const ForwardIteratorT ref end)
        ///   with begin: elements.Begin(), end: elements.End().
        mpublic virtual void InsertAt(const sizet index, const IterableT ref elements)
        {
            InsertAt(index, elements.Begin(), elements.End());
        }

        /// ----------------------------------------------------------------------------
        /// Inserts all elements from Collection \p{elements}.
        /// 
        /// This function is preferred over InsertAt(const sizet index, const IterableT ref elements)
        /// becuase Collection provides function Collection::Count() 
        /// which specifies the count of elements to insert. This helps to preallocate 
        /// memory instead of checking on each iteration.
        /// 
        /// @param[in] index Index to insert elements at.
        /// @param[in] elements Collection reference to insert elements from.
        /// 
        /// @exceptsafe
        /// \p{Strong Exception Safety}
        /// 
        /// @note
        /// - Calls InsertAt(const sizet index, const IterableT ref elements, const sizet count)
        ///   with index: index, elements: SCAST(const IterableT ref, elements), count: elements.Count().
        mpublic virtual void InsertAt(const sizet index, const CollectionT ref elements)
        {
            InsertAt(index, SCAST(const IterableT ref, elements), elements.Count());
        }

        /// ----------------------------------------------------------------------------
        /// Inserts multiple elements at index \p{index}.
        /// 
        /// @tparam TElements ... Elements to insert.
        /// @param index Index to insert elements at.
        /// 
        /// @note
        /// - Calls InsertAt(const sizet index, const ForwardIteratorT ref it, const sizet count).
        ///   with index: index, it: ArrayIterator(elements), count: "count of elements";
        mpublic template <ElementT... TElements>
            void InsertAt(const sizet index)
        {
            constexpr ElementT elements{ TElements... };
            InsertAt(index, ArrayIterator(elements), sizeof...(TElements));
        }

        /// ----------------------------------------------------------------------------
        /// - Calls InsertAt(const sizet index, const ForwardIteratorT ref it, const sizet count).
        ///   with index: 0, it: it, count: count.
        mpublic virtual void InsertFront(const ForwardIteratorT ref it, const sizet count)
        {
            InsertAt(0, it, count);
        }

        /// ----------------------------------------------------------------------------
        /// - Calls InsertAt(const sizet index, const ForwardIteratorT ref begin, const ForwardIteratorT ref end).
        ///   with index: 0, begin: begin, end: end.
        mpublic virtual void InsertFront(const ForwardIteratorT ref begin, const ForwardIteratorT ref end)
        {
            InsertAt(0, begin, end);
        }

        /// ----------------------------------------------------------------------------
        /// - Calls InsertAt(const sizet index, const IterableT ref elements, const sizet count).
        ///   with index: 0, elements: elements, count: count.
        mpublic virtual void InsertFront(const IterableT ref elements, const sizet count)
        {
            InsertAt(0, elements, count);
        }

        /// ----------------------------------------------------------------------------
        /// - Calls InsertAt(const sizet index, const IterableT ref elements, const sizet count).
        ///   with index: 0, elements: elements, count: count.
        mpublic virtual void InsertFront(const IterableT ref elements)
        {
            InsertAt(0, elements);
        }

        /// ----------------------------------------------------------------------------
        /// - Calls InsertAt(const sizet index, const CollectionT ref elements).
        ///   with index: 0, elements: elements.
        mpublic virtual void InsertFront(const CollectionT ref elements)
        {
            InsertAt(0, elements);
        }

        /// ----------------------------------------------------------------------------
        /// - Calls InsertAt<TElements...>(const sizet index).
        ///   with TElements...: TElements... \n
        ///   with index: 0.
        mpublic template <ElementT... TElements>
            void InsertFront(const sizet index)
        {
            InsertAt<TElements...>(0);
        }

        /// ----------------------------------------------------------------------------
        /// - Calls InsertAt(const sizet index, const ForwardIteratorT ref it, const sizet count).
        ///   with index: Count() - 1, it: it, count: count.
        mpublic virtual void InsertBack(const ForwardIteratorT ref it, const sizet count)
        {
            InsertAt(Count() - 1, it, count);
        }

        /// ----------------------------------------------------------------------------
        /// - Calls InsertAt(const sizet index, const ForwardIteratorT ref begin, const ForwardIteratorT ref end).
        ///   with index: Count() - 1, begin: begin, end: end.
        mpublic virtual void InsertBack(const ForwardIteratorT ref begin, const ForwardIteratorT ref end)
        {
            InsertAt(Count() - 1, begin, end);
        }

        /// ----------------------------------------------------------------------------
        /// - Calls InsertAt(const sizet index, const IterableT ref elements, const sizet count).
        ///   with index: Count() - 1, elements: elements, count: count.
        mpublic virtual void InsertBack(const IterableT ref elements, const sizet count)
        {
            InsertAt(Count() - 1, elements, count);
        }

        /// ----------------------------------------------------------------------------
        /// - Calls InsertAt(const sizet index, const IterableT ref elements, const sizet count).
        ///   with index: Count() - 1, elements: elements, count: count.
        mpublic virtual void InsertBack(const IterableT ref elements)
        {
            InsertAt(Count() - 1, elements);
        }

        /// ----------------------------------------------------------------------------
        /// - Calls InsertAt(const sizet index, const CollectionT ref elements).
        ///   with index: Count() - 1, elements: elements.
        mpublic virtual void InsertBack(const CollectionT ref elements)
        {
            InsertAt(Count() - 1, elements);
        }

        /// ----------------------------------------------------------------------------
        /// - Calls InsertAt<TElements...>(const sizet index).
        ///   with TElements...: TElements... \n
        ///   with index: Count() - 1.
        mpublic template <ElementT... TElements>
            void InsertBack(const sizet index)
        {
            InsertAt<TElements...>(Count() - 1);
        }

        // **********************************************************************

        /// ----------------------------------------------------------------------------
        /// Removes the element at index.
        /// 
        /// @param[in] index Index of the element to remove.
        mpublic virtual void RemoveAt(const sizet index) abstract;

        /// ----------------------------------------------------------------------------
        /// Removes the element at begining.
        /// 
        /// @note
        /// - Calls RemoveAt(const sizet index)
        ///   with index: 0.
        mpublic virtual void RemoveFront()
        {
            RemoveAt(0);
        }

        /// ----------------------------------------------------------------------------
        /// Removes the element at end.
        /// 
        /// @note
        /// - Calls RemoveAt(const sizet index)
        ///   with index: Count() - 1.
        mpublic virtual void RemoveBack()
        {
            RemoveAt(Count() - 1);
        }

        /// ----------------------------------------------------------------------------
        /// Removes the first element matching element \p{element}.
        /// 
        /// @note
        /// - Calls FirstIndexOf(const ElementT ref element, const EqualityComparerT comparer)
        ///   with element: element, comparer: comparer
        ///   to find the element to remove.
        /// 
        /// - Calls RemoveAt(const sizet index)
        ///   with index: FindFirstOf(element, comparer) if \p{index isnot NPOS}.
        mpublic virtual void RemoveFront(const ElementT ref element, const EqualityComparerT ref comparer)
        {
            if (sizet index = FirstIndexOf(element, comparer) isnot NPOS)
            {
                RemoveAt(index);
            }
        }

        /// ----------------------------------------------------------------------------
        /// @note 
        /// - Calls RemoveFront(const ElementT ref element, const EqualityComparerT ref comparer)
        ///   with element: element, comparer: DefaultEqualityComparerT().
        mpublic virtual void RemoveFront(const ElementT ref element)
        {
            RemoveFront(element, DefaultEqualityComparerT());
        }

        /// ----------------------------------------------------------------------------
        /// Removes the last element matching element \p{element}.
        /// 
        /// @note
        /// - Calls LastIndexOf(const ElementT ref element, const EqualityComparerT comparer)
        ///   with element: element, comparer: comparer
        ///   to find the element to remove.
        /// 
        /// - Calls RemoveAt(const sizet index)
        ///   with index: FindFirstOf(element, comparer) if \p{index isnot NPOS}.
        mpublic virtual void RemoveBack(const ElementT ref element, const EqualityComparerT ref comparer)
        {
            if (sizet index = LastIndexOf(element, comparer) isnot NPOS)
            {
                RemoveAt(index);
            }
        }

        /// ----------------------------------------------------------------------------
        /// @note 
        /// - Calls RemoveBack(const ElementT ref element, const EqualityComparerT ref comparer)
        ///   with element: element, comparer: DefaultEqualityComparerT().
        mpublic virtual void RemoveBack(const ElementT ref element)
        {
            RemoveBack(element, DefaultEqualityComparerT());
        }

        /// ----------------------------------------------------------------------------
        /// @note 
        /// - Calls RemoveBack(const ElementT ref element)
        ///   with element: element.
        mpublic virtual void Remove(const ElementT ref element) override
        {
            RemoveFront(element);
        }

        /// ----------------------------------------------------------------------------
        /// Removes elements from index \p{from} to index \p{to}.
        /// 
        /// @param from Starting index of the section to remove.
        /// @param to Last index of the section to remove.
        mpublic virtual void RemoveFrom(const sizet from, const sizet to) abstract;

        /// ----------------------------------------------------------------------------
        /// Removes elements from index \p{from} to the end of container.
        /// 
        /// @param from Starting index of the section to remove.
        /// 
        /// @note
        /// - Calls RemoveFrom(const sizet from, const sizet to)
        ///   with from: from, to: Count() - 1.
        mpublic virtual void RemoveFrom(const sizet from)
        {
            RemoveFrom(from, Count() - 1);
        }

        /// ----------------------------------------------------------------------------
        /// Removes single element if Predicate \p{pred} returns true.
        /// 
        /// @param pred Predicate to check whether to remove element or not.
        mpublic virtual void RemoveIfCallable(const PredicateT ref pred) noexcept abstract;

        /// ----------------------------------------------------------------------------
        /// Helper function for RemoveIfCallable(const PredicateT ref pred).
        /// 
        /// @tparam TFunctor Type of functor object. This object is wrapped using Callable.
        /// @param func Functor object.
        /// 
        /// @note
        /// - Wraps functor object \p{func} using PredicateT::Create(func) and 
        ///   Calls RemoveIfCallable(const PredicateT ref pred)
        ///   with pred: PredicateT::Create(func).
        mpublic template <typename TFunctor>
            void RemoveIf(const TFunctor ref func) noexcept
        {
            RemoveIfCallable(PredicateT::Create(func));
        }
    };
}