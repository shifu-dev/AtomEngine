#include "catch2/catch_all.hpp"
#include "AtomEngine/String/StringIterator.hpp"

using namespace Atom;

TEST_CASE("TStringIterator")
{
    TConstStringIterator<char> it("hello bro");
}