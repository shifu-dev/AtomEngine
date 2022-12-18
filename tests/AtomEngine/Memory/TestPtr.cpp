#include "catch2/catch_all.hpp"
#include "AtomEngine/Memory/Ptr.hpp"

using namespace Atom;

TEST_CASE("TPtr")
{
    int value = 10;
    TPtr<int> valuePtr = &value;

    CHECK(*valuePtr == value);
}