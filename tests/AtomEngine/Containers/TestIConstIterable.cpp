#include "catch2/catch_all.hpp"
#include "AtomEngine/Containers/IConstArray.hpp"
#include "AtomEngine/Containers/ArrayView.hpp"

using namespace Atom;

TEST_CASE("IConstIterable Implementation")
{
    const IConstIterable<int> ref collection = 
        ArrayView<int>({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 });

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
        collection.ForEachT
        (
            [ref i] (const int ref value)
            {
                CHECK(value == i);
                i++;
            }
        );
    }

    return;
}