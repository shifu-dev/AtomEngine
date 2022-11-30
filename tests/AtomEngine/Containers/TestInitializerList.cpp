#include "catch2/catch_all.hpp"
#include "AtomEngine/Containers/InitializerList.hpp"

using namespace Atom;

TEST_CASE("InitializerList Implementation")
{
    InitializerList<int> initList1({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 });

    int arr[]{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    InitializerList<int> initList2(arr);

    CHECK(initList2.count == 10);
}