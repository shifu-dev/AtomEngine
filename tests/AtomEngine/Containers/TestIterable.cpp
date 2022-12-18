#include "catch2/catch_all.hpp"
#include "AtomEngine/Containers/StackArray.hpp"

using namespace Atom;

TEST_CASE("IConstIterable Implementation")
{
    StackArray<int, 10> arr;
    IIterable<int> ref collection = arr;

    SECTION("RangeBased ForLoop")
    {
        int i = 0;
        for (auto value : citerate(collection))
        {
            CHECK(value == i);
            i++;
        }
    }

    SECTION("ForEachT")
    {
        int i = 0;
        collection.ForEach
        (
            [&i] (int& value)
            {
                CHECK(value == i);
                i++;

                return CONTINUE_LOOP;
            }
        );
    }

    return;
}