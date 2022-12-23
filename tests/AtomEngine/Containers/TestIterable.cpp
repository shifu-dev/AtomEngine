#include "catch2/catch_all.hpp"
#include "AtomEngine/Containers/StackArray.hpp"
#include "AtomEngine/Containers/ForLoopIterator.hpp"

using namespace Atom;

TEST_CASE("IConstIterable Implementation")
{
    StackArray<int, 10> arr;
    IIterable<int> & collection = arr;

    SECTION("RangeBased ForLoop")
    {
        int i = 0;
        for (auto value : iterate(collection))
        {
            CHECK(value == i);
            i++;
        }
    }

    return;
}