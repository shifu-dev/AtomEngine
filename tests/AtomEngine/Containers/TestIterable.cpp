#include "catch2/catch_all.hpp"
#include "AtomEngine/Containers/StackArray.hpp"

using namespace Atom;

TEST_CASE("IConstIterable Implementation")
{
    StackArray<int, 10> arr;
    IIterable<int>& collection = arr;

    SECTION("ForEach")
    {
        int i = 0;
        ForEach(collection, [&](int value)
        {
            CHECK(value == i);
            i++;

            return CONTINUE_LOOP;
        });
    }

    return;
}