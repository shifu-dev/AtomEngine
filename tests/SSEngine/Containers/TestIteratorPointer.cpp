#pragma once
#include "catch2/catch_all.hpp"
#include "SSEngine/Containers/IteratorPointer.hpp"
#include "SSEngine/Containers/ArrayIterator.hpp"

using namespace SSEngine;

TEST_CASE("IteratorPointer Implementation")
{
    IteratorPointer<int> itPtr1;

    IteratorPointer<int> itPtr2 = itPtr1;

    IteratorPointer<int> itPtr3;
    itPtr3 = itPtr1;

    ArrayIterator<int> arrIt(nullptr);
    IteratorPointer<int> itPtr4 = arrIt;

    return;
}