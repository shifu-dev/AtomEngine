#include "catch2/catch_all.hpp"
#include "AtomEngine/Containers/ArrayView.hpp"

using namespace Atom;

TEST_CASE("IConstIterable Implementation")
{
    const ArrayView<int> arrView = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    const IConstIterable<int>& collection = arrView;

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