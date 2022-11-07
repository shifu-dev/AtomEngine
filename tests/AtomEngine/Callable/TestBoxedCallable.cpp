#pragma once
#include "catch2/catch_all.hpp"
#include "AtomEngine/Callable/BoxedCallable.hpp"

using namespace Atom;

class Functor
{
    mpublic int operator()(int a, char b, uint c) const
    {
        return 1;
    }
};

static int testFunc(int a, char b, uint c)
{
    return 0;
}

TEST_CASE("BoxedCallable", "[Implementation]")
{
    using CallableT = Callable<int(int, char, uint)>;
    using BoxedCallableT = BoxedCallable<int(int, char, uint)>;

    BoxedCallableT function = CallableT::Create(ref testFunc);
    BoxedCallableT functor = CallableT::Create(Functor());
    BoxedCallableT lambda = CallableT::Create(
        [](int a, char b, uint c)
        {
            return 2;
        });

    BoxedCallableT capturedLambda = CallableT::Create(
        [&](int a, char b, uint c)
        {
            return 3;
        });

    BoxedCallableT functionCopy = function;

    BoxedCallableT functionCopyByOperator;
    functionCopyByOperator = function;

    CHECK(function(0, 'a', 0) == 0);
    CHECK(functor(0, 'a', 0) == 1);
    CHECK(lambda(0, 'a', 0) == 2);
    CHECK(capturedLambda(0, 'a', 0) == 3);
}