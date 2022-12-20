#include "catch2/catch_all.hpp"
#include "AtomEngine/Containers/ArrayView.hpp"

using namespace Atom;

TEST_CASE("IConstIterable Implementation")
{
    const ArrayView<int> arrView = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    const IConstIterable<int> & collection = arrView;

    SECTION("RangeBased ForLoop")
    {
        int i = 0;
        for (auto value : citerate(collection))
        {
            CHECK(value == i);
            i++;
        }
    }

    return;
}