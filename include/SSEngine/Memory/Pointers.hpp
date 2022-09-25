#pragma once
#include "SSEngine/Core.hpp"

namespace SSEngine
{
    /// @brief base class for pointers
    /// @tparam T pointer type
    template <typename T>
    struct Ptr
    {
    public:

        /// @brief checks if pointer is null
        /// @note this does not calls == operator,
        /// instead checks for the memory address
        /// @return returns true if pointer is null
        bool is_null()
        {
            return isnull(_ptr);
        }

        T& operator->()
        {
            return (*_ptr);
        }

    protected:
        T* _ptr;
    };

    template <typename T>
    struct UniquePtr : Ptr<T> {};
}