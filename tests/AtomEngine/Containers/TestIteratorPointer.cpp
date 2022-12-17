#include "catch2/catch_all.hpp"
#include "AtomEngine/Containers/IteratorBox.hpp"
#include "AtomEngine/Containers/ArrayIterator.hpp"

using namespace Atom;

TEST_CASE("IteratorBox Implementation")
{
    IteratorBox<int> itPtr1;

    IteratorBox<int> itPtr2 = itPtr1;

    IteratorBox<int> itPtr3;
    itPtr3 = itPtr1;

    ArrayIterator<int> arrIt(nullptr);
    IteratorBox<int> itPtr4 = arrIt;

    return;
}