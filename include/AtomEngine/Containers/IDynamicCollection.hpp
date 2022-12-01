#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Containers/ICollection.hpp"

namespace Atom
{
    /// @brief base class for collections which can manage memory dynamically
    /// @tparam TElement type of element to store
    template <typename TElement>
    interface IDynamicCollection : public virtual ICollection<TElement>
    {
        /// @brief resizes the underlying memory
        /// @param count count of objects to allocate memor for
        /// @note this does not change element count
        mpublic virtual void Resize(const sizet count) abstract;

        /// @brief asks the collection to reserve memory for count elements
        /// @param count minimum count of elements to reserve memory for
        /// @return count of reserved memory for element
        mpublic virtual sizet Reserve(const sizet count) abstract;

        /// @brief resizes capacity equal to count
        /// @return count of memory for element currently allocated
        mpublic virtual sizet ShrinkToFit() abstract;
    };
}