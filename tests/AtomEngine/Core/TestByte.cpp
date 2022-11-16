#include <iostream>
#include "catch2/catch_all.hpp"
#include "AtomEngine/Core.hpp"

using namespace Atom;

TEST_CASE("Byte", "[Implmentation]")
{
    sassert(sizeof(byte) == 1, "sizeof(byte) != 1");

    byte value;

    byte a = 0;
    byte b = 'c';
    byte c = 99U;

    int e = a;
    char f = b;
    uint g = c;

    CHECK(e == 0);
    CHECK(f == 'c');
    CHECK(g == 99U);

    byte d = 4;
    CHECK(scast<int>(d << 1) == 8);
    CHECK(scast<int>(d >> 1) == 2);
}