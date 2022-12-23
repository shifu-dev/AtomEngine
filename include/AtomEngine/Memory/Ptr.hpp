#pragma once
#include "AtomEngine/Core.hpp"
#include "AtomEngine/Memory/IAllocator.hpp"
#include "AtomEngine/Memory/DefaultAllocator.hpp"

namespace Atom
{
    /// Base class for pointers.
    /// 
    /// @tparam TypeT Pointer type.
    template <typename TypeT>
    struct TPtr
    {
    public:
        /// Default constructor, creates a nullptr pointer.
        /// 
        TPtr(): TPtr(nullptr) { }

        /// Initializes underlying pointer with \p{inPtr}
        /// 
        /// @param inPtr Pointer to initialize with.
        TPtr(TypeT* inPtr) noexcept:
            _ptr(inPtr) { }

        TypeT& operator * () noexcept
        {
            return *_ptr;
        }

        const TypeT& operator * () const noexcept
        {
            return *_ptr;
        }

        TypeT* operator -> () noexcept
        {
            return _ptr;
        }

        const TypeT* operator -> () const noexcept
        {
            return _ptr;
        }

    protected:
        TypeT* _ptr;
    };
}