#pragma once
#include "catch2/catch_all.hpp"
#include "AtomEngine/Containers/BoxedIterator.hpp"
#include "AtomEngine/Containers/ArrayIterator.hpp"

using namespace Atom;

TEST_CASE("BoxedIterator Implementation")
{
    BoxedIterator<int> itPtr1;

    BoxedIterator<int> itPtr2 = itPtr1;

    BoxedIterator<int> itPtr3;
    itPtr3 = itPtr1;

    ArrayIterator<int> arrIt(nullptr);
    BoxedIterator<int> itPtr4 = arrIt;

    return;
}