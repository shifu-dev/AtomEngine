#include "catch2/catch_all.hpp"
#include "AtomEngine/Memory/SharedPtr.hpp"

using namespace Atom;

TEST_CASE("TSharedPtr")
{
    int value = 10;
    TSharedPtr<int> valuePtr = &value;
    TSharedPtr<int> valuePtr1 = valuePtr;
    TSharedPtr<int> valuePtr2 = valuePtr;
    TSharedPtr<int> valuePtr3 = valuePtr;
    TSharedPtr<int> valuePtr4 = valuePtr;

    CHECK(valuePtr.RefCount() == 5);
    CHECK(*valuePtr == value);
}