#include "catch2/catch_all.hpp"
#include "AtomEngine/Memory/UniquePtr.hpp"

using namespace Atom;

TEST_CASE("TUniquePtr")
{
    int value = 10;
    TUniquePtr<int> valuePtr = TUniquePtr<int>::Create(value);

    CHECK(*valuePtr == value);
}