#include "catch2/catch_all.hpp"
#include "AtomEngine/Containers/ArrayIterator.hpp"

using namespace Atom;

TEST_CASE("ArrayIterator")
{
    const int arr[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    const SizeT IT_lENGTH = 10;
    TConstArrayIterator<int> it(arr, IT_lENGTH);

    SECTION("Iteration")
    {
        SizeT i = 0;
        while (it.IsEnd() == false)
        {
            CHECK(it.Value() == arr[i]);

            it++;
            i++;
        }
    }

    SECTION("Reset()")
    {
        it.Reset();
        CHECK(it.Value() == arr[0]);
    }

    SECTION("IsEnd()")
    {
        it.Reset();
        CHECK(it.IsEnd() == false);

        it.MoveFwdBy(20);
        CHECK(it.IsEnd() == true);
        CHECK_THROWS(it.Value());

        // ArrayIterator stops at end

        it.MoveBwd();
        CHECK(it.IsEnd() == false);
        CHECK(it.Value() == arr[IT_lENGTH - 1]);
    }

    SECTION("Move()")
    {
    }
}